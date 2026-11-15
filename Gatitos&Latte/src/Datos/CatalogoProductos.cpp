#include "CatalogoProductos.h"
#include <stdexcept>

namespace gatitos::datos
{
void CatalogoProductos::agregar(const dominio::Producto& producto)
{
    if (buscarPorCodigo(producto.codigo())) {
        throw std::invalid_argument("Ya existe un producto con ese codigo.");
    }
    productos_.agregar(producto);
}

std::size_t CatalogoProductos::cantidad() const noexcept { return productos_.tamano(); }

const dominio::Producto& CatalogoProductos::en(std::size_t indice) const
{
    return productos_.en(indice);
}

std::optional<dominio::Producto> CatalogoProductos::buscarPorCodigo(int codigo) const
{
    // Busqueda secuencial: recorre solo los elementos registrados, en O(n).
    for (std::size_t i = 0; i < productos_.tamano(); ++i) {
        if (productos_.en(i).codigo() == codigo) { return productos_.en(i); }
    }
    return std::nullopt;
}
}
