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
    pendientes_.encolar(pedido);
    ++proximoNumero_; // Solo avanza cuando el nodo se ha creado correctamente.
}

std::size_t RegistroPedidos::cantidadPendientes() const noexcept { return pendientes_.cantidad(); }

std::optional<dominio::Pedido> RegistroPedidos::buscar(int numero) const
{
    const auto* pedido = pendientes_.buscar(numero);
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
}
