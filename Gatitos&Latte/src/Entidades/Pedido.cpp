#include "Pedido.h"
#include <limits>
#include <stdexcept>
#include <utility>

namespace gatitos::entidades
{
Pedido::Pedido(int numero, std::string cliente, const Producto& producto, int cantidad)
    : numero_(numero), cliente_(std::move(cliente)), producto_(producto),
      cantidad_(cantidad), totalCentimos_(0)
{
    if (numero_ <= 0) { throw std::invalid_argument("El numero de pedido debe ser positivo."); }
    if (cliente_.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
        throw std::invalid_argument("El nombre del cliente no puede estar vacio.");
    }
    if (!producto_.disponible()) { throw std::invalid_argument("El producto no esta disponible."); }
    if (cantidad_ <= 0) { throw std::invalid_argument("La cantidad debe ser mayor que cero."); }
    const auto maximo = (std::numeric_limits<std::int64_t>::max)();
    if (producto_.precioCentimos() > maximo / cantidad_) {
        throw std::overflow_error("El total del pedido supera el importe permitido.");
    }
    totalCentimos_ = producto_.precioCentimos() * cantidad_;
}

int Pedido::numero() const noexcept { return numero_; }
const std::string& Pedido::cliente() const noexcept { return cliente_; }
const Producto& Pedido::producto() const noexcept { return producto_; }
int Pedido::cantidad() const noexcept { return cantidad_; }
std::int64_t Pedido::precioUnitarioCentimos() const noexcept { return producto_.precioCentimos(); }
std::int64_t Pedido::totalCentimos() const noexcept { return totalCentimos_; }
EstadoPedido Pedido::estado() const noexcept { return estado_; }
void Pedido::marcarEntregado() noexcept { estado_ = EstadoPedido::Entregado; }
}
