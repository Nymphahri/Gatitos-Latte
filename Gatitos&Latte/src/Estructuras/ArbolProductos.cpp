#include "ArbolProductos.h"
#include <stdexcept>

namespace gatitos::estructuras
{
ArbolProductos::~ArbolProductos() { liberar(raiz_); }

void ArbolProductos::insertar(const entidades::Producto& producto)
{
    insertarNodo(raiz_, producto);
}

void ArbolProductos::insertarNodo(Nodo*& nodo, const entidades::Producto& producto)
{
    if (nodo == nullptr) {
        // Solo enlaza el nodo cuando la reserva se completa correctamente.
        nodo = new Nodo(producto);
        return;
    }
    if (producto.codigo() < nodo->producto->codigo()) { insertarNodo(nodo->izquierdo, producto); }
    else if (producto.codigo() > nodo->producto->codigo()) { insertarNodo(nodo->derecho, producto); }
    else { throw std::invalid_argument("Ya existe un producto con ese codigo en el arbol."); }
}

const entidades::Producto* ArbolProductos::buscar(int codigo) const noexcept
{
    const Nodo* actual = raiz_;
    while (actual != nullptr) {
        if (codigo == actual->producto->codigo()) { return actual->producto; }
        actual = codigo < actual->producto->codigo() ? actual->izquierdo : actual->derecho;
    }
    return nullptr;
}

ArregloProductos ArbolProductos::inorden() const
{
    ArregloProductos resultado;
    recorrerInorden(raiz_, resultado);
    return resultado;
}

void ArbolProductos::recorrerInorden(const Nodo* nodo, ArregloProductos& resultado)
{
    if (nodo == nullptr) { return; }
    recorrerInorden(nodo->izquierdo, resultado);
    resultado.agregar(*nodo->producto);
    recorrerInorden(nodo->derecho, resultado);
}

void ArbolProductos::liberar(Nodo* nodo) noexcept
{
    if (nodo == nullptr) { return; }
    liberar(nodo->izquierdo);
    liberar(nodo->derecho);
    delete nodo;
}
}
