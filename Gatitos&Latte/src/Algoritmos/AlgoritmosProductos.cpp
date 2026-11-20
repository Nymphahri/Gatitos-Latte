#include "AlgoritmosProductos.h"
#include <stdexcept>

namespace
{
bool vaAntes(const gatitos::entidades::Producto& primero,
             const gatitos::entidades::Producto& segundo,
             gatitos::algoritmos::CriterioOrden criterio)
{
    using gatitos::algoritmos::CriterioOrden;
    if (criterio == CriterioOrden::Nombre && primero.nombre() != segundo.nombre())
    {
        return primero.nombre() < segundo.nombre();
    }
    if (criterio == CriterioOrden::Precio && primero.precioCentimos() != segundo.precioCentimos())
    {
        return primero.precioCentimos() < segundo.precioCentimos();
    }
    return primero.codigo() < segundo.codigo();
}
}

namespace gatitos::algoritmos
{
void ordenarPorInsercion(estructuras::ArregloProductos& productos, CriterioOrden criterio)
{
    if (criterio != CriterioOrden::Codigo && criterio != CriterioOrden::Nombre && criterio != CriterioOrden::Precio)
    {
        throw std::invalid_argument("Criterio de ordenamiento invalido.");
    }
    for (std::size_t i = 1; i < productos.tamano(); ++i) {
        std::size_t posicion = i;

        // Inserta el elemento en la parte izquierda, que ya esta ordenada.
        while (posicion > 0 && vaAntes(productos.en(posicion), productos.en(posicion - 1), criterio))
        {
            productos.intercambiar(posicion, posicion - 1);
            --posicion;
        }
    }
}

const entidades::Producto* buscarSecuencialPorCodigo(const estructuras::ArregloProductos& productos, int codigo)
{
    for (std::size_t i = 0; i < productos.tamano(); ++i) {
        if (productos.en(i).codigo() == codigo) { return &productos.en(i); }
    }
    return nullptr;
}
const entidades::Producto* buscarBinariaPorCodigo(const estructuras::ArregloProductos& productos, int codigo)
{
    std::size_t inicio = 0;
    std::size_t fin = productos.tamano(); // Limite exclusivo: también funciona con arreglo vacío.
    while (inicio < fin) {
        const std::size_t medio = inicio + (fin - inicio) / 2;
        const auto& producto = productos.en(medio);
        if (producto.codigo() == codigo) { return &producto; }
        if (producto.codigo() < codigo) { inicio = medio + 1; }
        else { fin = medio; }
    }
    return nullptr;
}
}
