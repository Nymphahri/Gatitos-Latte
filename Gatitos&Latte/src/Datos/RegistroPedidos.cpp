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

void RegistroPedidos::agregar(const dominio::Pedido& pedido)
{
    if (pedido.numero() != siguienteNumero()) { throw std::invalid_argument("Numero de pedido fuera de secuencia."); }
    if (pedido.estado() != dominio::EstadoPedido::Pendiente) {
        throw std::invalid_argument("Solo se pueden registrar pedidos pendientes.");
    }
    pendientes_.encolar(pedido);
    ++proximoNumero_; // Solo avanza cuando el nodo se ha creado correctamente.
}

std::size_t RegistroPedidos::cantidadPendientes() const noexcept { return pendientes_.cantidad(); }

std::optional<dominio::Pedido> RegistroPedidos::buscar(int numero) const
{
    const auto* pedido = pendientes_.buscar(numero);
    if (pedido == nullptr) { pedido = procesados_.buscar(numero); }
    if (pedido != nullptr) { return *pedido; }
    return std::nullopt;
}

std::optional<dominio::Pedido> RegistroPedidos::siguiente() const
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
    dominio::Pedido entregado = *primero;
    entregado.marcarEntregado();
    const int numero = entregado.numero();
    // Guardar primero: si falla la reserva de memoria, el pendiente no se pierde.
    procesados_.agregar(entregado);
    pendientes_.desencolar();
    return numero;
}

std::size_t RegistroPedidos::cantidadProcesados() const noexcept { return procesados_.cantidad(); }
estructuras::ListaPedidos RegistroPedidos::procesados() const { return procesados_; }
}
