#include "RegistroPedidos.h"
#include <limits>
#include <stdexcept>

namespace gatitos::datos
{
int RegistroPedidos::siguienteNumero() const
{
    if (proximoNumero_ > (std::numeric_limits<int>::max)()) {
        throw std::overflow_error("Se agotaron los numeros de pedido disponibles.");
    }
    return static_cast<int>(proximoNumero_);
}

void RegistroPedidos::agregar(const entidades::Pedido& pedido)
{
    if (pedido.numero() != siguienteNumero()) { throw std::invalid_argument("Numero de pedido fuera de secuencia."); }
    if (pedido.estado() != entidades::EstadoPedido::Pendiente) {
        throw std::invalid_argument("Solo se pueden registrar pedidos pendientes.");
    }
    historial_.apilar(entidades::OperacionPedido(pedido.numero(), entidades::TipoOperacionPedido::Registro));
    try {
        pendientes_.encolar(pedido);
    } catch (...) {
        historial_.desapilar(); // La operacion fallida no debe quedar en el historial.
        throw;
    }
    ++proximoNumero_; // Solo avanza cuando el nodo se ha creado correctamente.
}

std::size_t RegistroPedidos::cantidadPendientes() const noexcept { return pendientes_.cantidad(); }

std::optional<entidades::Pedido> RegistroPedidos::buscar(int numero) const
{
    const auto* pedido = pendientes_.buscar(numero);
    if (pedido == nullptr) { pedido = procesados_.buscar(numero); }
    if (pedido != nullptr) { return *pedido; }
    return std::nullopt;
}

std::optional<entidades::Pedido> RegistroPedidos::siguiente() const
{
    const auto* pedido = pendientes_.frente();
    if (pedido != nullptr) { return *pedido; }
    return std::nullopt;
}

estructuras::ColaPedidos RegistroPedidos::pendientes() const { return pendientes_; }

int RegistroPedidos::atenderSiguiente()
{
    const auto* primero = pendientes_.frente();
    if (primero == nullptr) { return 0; }
    entidades::Pedido entregado = *primero;
    entregado.marcarEntregado();
    const int numero = entregado.numero();
    // Preparar historial y lista antes de retirar el pendiente.
    historial_.apilar(entidades::OperacionPedido(numero, entidades::TipoOperacionPedido::Entrega));
    try {
        procesados_.agregar(entregado);
    } catch (...) {
        historial_.desapilar();
        throw;
    }
    pendientes_.desencolar();
    return numero;
}

std::size_t RegistroPedidos::cantidadProcesados() const noexcept { return procesados_.cantidad(); }
estructuras::ListaPedidos RegistroPedidos::procesados() const { return procesados_; }
estructuras::PilaOperaciones RegistroPedidos::historial() const { return historial_; }

bool RegistroPedidos::eliminarProcesado(int numero)
{
    if (procesados_.buscar(numero) == nullptr) { return false; }
    // Si no se puede guardar la operacion, el pedido permanece en la lista.
    historial_.apilar(entidades::OperacionPedido(numero, entidades::TipoOperacionPedido::Eliminacion));
    procesados_.eliminar(numero); // No reserva memoria ni lanza excepciones.
    return true;
}
std::size_t RegistroPedidos::cantidadHistorial() const noexcept { return historial_.cantidad(); }
}
