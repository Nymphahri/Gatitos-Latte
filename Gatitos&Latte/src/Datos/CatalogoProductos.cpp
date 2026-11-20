#include "CatalogoProductos.h"
#include <stdexcept>

namespace gatitos::datos
{
void CatalogoProductos::agregar(const entidades::Producto& producto)
{
    if (arbol_.buscar(producto.codigo()) != nullptr) { throw std::invalid_argument("Ya existe un producto con ese codigo."); }
    productos_.agregar(producto);
    try {
        arbol_.insertar(productos_.en(productos_.tamano() - 1));
    } catch (...) {
        // Mantiene ambos registros consistentes si no se puede crear el nodo.
        productos_.eliminarUltimo();
        throw;
    }
    ordenadoPorCodigo_ = false;
}

std::size_t CatalogoProductos::cantidad() const noexcept { return productos_.tamano(); }

const entidades::Producto& CatalogoProductos::en(std::size_t indice) const { return productos_.en(indice); }

std::optional<entidades::Producto> CatalogoProductos::buscarPorCodigo(int codigo) const
{
    const auto* producto = algoritmos::buscarSecuencialPorCodigo(productos_, codigo);
    if (producto != nullptr) { return *producto; }
    return std::nullopt;
}

void CatalogoProductos::ordenar(algoritmos::CriterioOrden criterio)
{
    algoritmos::ordenarPorInsercion(productos_, criterio);
    ordenadoPorCodigo_ = criterio == algoritmos::CriterioOrden::Codigo;
}

std::optional<entidades::Producto> CatalogoProductos::buscarBinaria(int codigo)
{
    if (!ordenadoPorCodigo_) { ordenar(algoritmos::CriterioOrden::Codigo); }
    const auto* producto = algoritmos::buscarBinariaPorCodigo(productos_, codigo);
    if (producto != nullptr) { return *producto; }
    return std::nullopt;
}
std::optional<entidades::Producto> CatalogoProductos::buscarEnArbol(int codigo) const
{
    const auto* producto = arbol_.buscar(codigo);
    if (producto != nullptr) { return *producto; }
    return std::nullopt;
}

estructuras::ArregloProductos CatalogoProductos::productosInorden() const
{
    return arbol_.inorden();
}
}
