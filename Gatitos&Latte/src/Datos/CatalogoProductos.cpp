#include "CatalogoProductos.h"
#include <stdexcept>

namespace gatitos::datos
{
void CatalogoProductos::agregar(const dominio::Producto& producto)
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

const dominio::Producto& CatalogoProductos::en(std::size_t indice) const { return productos_.en(indice); }

std::optional<dominio::Producto> CatalogoProductos::buscarPorCodigo(int codigo) const
{
    // Busqueda secuencial: no requiere orden previo.
    for (std::size_t i = 0; i < productos_.tamano(); ++i) {
        if (productos_.en(i).codigo() == codigo) { return productos_.en(i); }
    }
    return std::nullopt;
}

void CatalogoProductos::ordenar(algoritmos::CriterioOrden criterio)
{
    algoritmos::ordenarPorInsercion(productos_, criterio);
    ordenadoPorCodigo_ = criterio == algoritmos::CriterioOrden::Codigo;
}

std::optional<dominio::Producto> CatalogoProductos::buscarBinaria(int codigo)
{
    if (!ordenadoPorCodigo_) { ordenar(algoritmos::CriterioOrden::Codigo); }
    const auto* producto = algoritmos::buscarBinariaPorCodigo(productos_, codigo);
    if (producto != nullptr) { return *producto; }
    return std::nullopt;
}
std::optional<dominio::Producto> CatalogoProductos::buscarEnArbol(int codigo) const
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
