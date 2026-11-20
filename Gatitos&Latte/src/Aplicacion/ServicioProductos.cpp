#include "ServicioProductos.h"
#include <utility>

namespace gatitos::aplicacion
{
ServicioProductos::ServicioProductos(datos::CatalogoProductos& catalogo) noexcept
    : catalogo_(catalogo) {}

void ServicioProductos::registrar(int codigo, std::string nombre, std::string categoria,
                                std::int64_t precioCentimos, bool disponible)
{
    // Se construye y valida antes de modificar el catalogo.
    const entidades::Producto producto(codigo, std::move(nombre), std::move(categoria),
                                    precioCentimos, disponible);
    catalogo_.agregar(producto);
}

std::size_t ServicioProductos::cantidad() const noexcept { return catalogo_.cantidad(); }

const entidades::Producto& ServicioProductos::productoEn(std::size_t indice) const
{
    return catalogo_.en(indice);
}

std::optional<entidades::Producto> ServicioProductos::buscarPorCodigo(int codigo) const
{
    return catalogo_.buscarPorCodigo(codigo);
}
void ServicioProductos::ordenar(algoritmos::CriterioOrden criterio)
{
    catalogo_.ordenar(criterio);
}

std::optional<entidades::Producto> ServicioProductos::buscarBinaria(int codigo)
{
    return catalogo_.buscarBinaria(codigo);
}
std::optional<entidades::Producto> ServicioProductos::buscarEnArbol(int codigo) const
{
    return catalogo_.buscarEnArbol(codigo);
}

estructuras::ArregloProductos ServicioProductos::productosInorden() const
{
    return catalogo_.productosInorden();
}
}
