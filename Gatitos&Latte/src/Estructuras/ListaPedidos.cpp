#include "ListaPedidos.h"

namespace gatitos::estructuras
{
ListaPedidos::~ListaPedidos() { limpiar(); }

ListaPedidos::ListaPedidos(const ListaPedidos& otra)
{
    try {
        for (const Nodo* nodo = otra.primero_; nodo != nullptr; nodo = nodo->siguiente) {
            agregar(nodo->pedido);
        }
    } catch (...) {
        limpiar();
        throw;
    }
}

ListaPedidos& ListaPedidos::operator=(const ListaPedidos& otra)
{
    if (this == &otra) { return *this; }
    ListaPedidos copia(otra);
    limpiar();
    primero_ = copia.primero_;
    ultimo_ = copia.ultimo_;
    cantidad_ = copia.cantidad_;
    copia.primero_ = nullptr;
    copia.ultimo_ = nullptr;
    copia.cantidad_ = 0;
    return *this;
}

void ListaPedidos::agregar(const entidades::Pedido& pedido)
{
    Nodo* nuevo = new Nodo(pedido);
    if (ultimo_ != nullptr) { ultimo_->siguiente = nuevo; }
    else { primero_ = nuevo; }
    ultimo_ = nuevo;
    ++cantidad_;
}

bool ListaPedidos::eliminar(int numero) noexcept
{
    Nodo* anterior = nullptr;
    Nodo* actual = primero_;
    while (actual != nullptr && actual->pedido.numero() != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) { return false; }
    if (anterior != nullptr) { anterior->siguiente = actual->siguiente; }
    else { primero_ = actual->siguiente; }
    if (actual == ultimo_) { ultimo_ = anterior; }
    delete actual;
    --cantidad_;
    return true;
}

void ListaPedidos::limpiar() noexcept
{
    while (primero_ != nullptr) {
        Nodo* retirado = primero_;
        primero_ = primero_->siguiente;
        delete retirado;
    }
    ultimo_ = nullptr;
    cantidad_ = 0;
}

const entidades::Pedido* ListaPedidos::primero() const noexcept
{
    return primero_ != nullptr ? &primero_->pedido : nullptr;
}

const entidades::Pedido* ListaPedidos::buscar(int numero) const noexcept
{
    for (const Nodo* nodo = primero_; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->pedido.numero() == numero) { return &nodo->pedido; }
    }
    return nullptr;
}

std::size_t ListaPedidos::cantidad() const noexcept { return cantidad_; }
bool ListaPedidos::vacia() const noexcept { return primero_ == nullptr; }
}
