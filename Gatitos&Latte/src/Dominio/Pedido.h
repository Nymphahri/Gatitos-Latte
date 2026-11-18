#pragma once

#include "Producto.h"

namespace gatitos::dominio
{
enum class EstadoPedido { Pendiente, Entregado };

class Pedido
{
public:
    Pedido(int numero, std::string cliente, const Producto& producto, int cantidad);
    [[nodiscard]] int numero() const noexcept;
    [[nodiscard]] const std::string& cliente() const noexcept;
    [[nodiscard]] const Producto& producto() const noexcept;
    [[nodiscard]] int cantidad() const noexcept;
    [[nodiscard]] std::int64_t precioUnitarioCentimos() const noexcept;
    [[nodiscard]] std::int64_t totalCentimos() const noexcept;
    [[nodiscard]] EstadoPedido estado() const noexcept;
    void marcarEntregado() noexcept;

private:
    int numero_;
    std::string cliente_;
    Producto producto_; // Copia de los datos y el precio al momento de la venta.
    int cantidad_;
    std::int64_t totalCentimos_;
    EstadoPedido estado_ = EstadoPedido::Pendiente;
};
}
