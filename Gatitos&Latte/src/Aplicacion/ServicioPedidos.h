#pragma once

#include "../Datos/CatalogoProductos.h"
#include "../Datos/RegistroPedidos.h"

namespace gatitos::aplicacion
{
class ServicioPedidos
{
public:
    ServicioPedidos(const datos::CatalogoProductos& productos, datos::RegistroPedidos& pedidos) noexcept;
    int registrar(std::string cliente, int codigoProducto, int cantidad);
    [[nodiscard]] std::size_t cantidadPendientes() const noexcept;
    [[nodiscard]] std::optional<dominio::Pedido> buscar(int numero) const;
    [[nodiscard]] std::optional<dominio::Pedido> siguiente() const;
    [[nodiscard]] estructuras::ColaPedidos pendientes() const;

private:
    const datos::CatalogoProductos& productos_;
    datos::RegistroPedidos& pedidos_;
};
}
