#include "ColaPedidos.h"

namespace gatitos::estructuras
{
ColaPedidos::~ColaPedidos()
{
    while (desencolar()) {}
}

ColaPedidos::ColaPedidos(const ColaPedidos& otra)
{
    try {
        for (const Nodo* nodo = otra.frente_; nodo != nullptr; nodo = nodo->siguiente) {
            encolar(nodo->pedido);
        }
    } catch (...) {
        while (desencolar()) {}
        throw;
    }
}

ColaPedidos& ColaPedidos::operator=(const ColaPedidos& otra)
{
    if (this == &otra) { return *this; }
    ColaPedidos copia(otra);
    while (desencolar()) {}
    frente_ = copia.frente_;
    final_ = copia.final_;
    cantidad_ = copia.cantidad_;
    copia.frente_ = nullptr;
    copia.final_ = nullptr;
    copia.cantidad_ = 0;
    return *this;
}

void ColaPedidos::encolar(const entidades::Pedido& pedido)
{
    Nodo* nuevo = new Nodo(pedido);
    if (final_ != nullptr) { final_->siguiente = nuevo; }
    else { frente_ = nuevo; }
    final_ = nuevo;
    ++cantidad_;
}

bool ColaPedidos::desencolar() noexcept
{
    if (frente_ == nullptr) { return false; }
    Nodo* retirado = frente_;
    frente_ = frente_->siguiente;
    if (frente_ == nullptr) { final_ = nullptr; }
    delete retirado;
    --cantidad_;
    return true;
}

const entidades::Pedido* ColaPedidos::frente() const noexcept
{
    return frente_ != nullptr ? &frente_->pedido : nullptr;
}

const entidades::Pedido* ColaPedidos::final() const noexcept
{
    return final_ != nullptr ? &final_->pedido : nullptr;
}

const entidades::Pedido* ColaPedidos::buscar(int numero) const noexcept
{
    for (const Nodo* nodo = frente_; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->pedido.numero() == numero) { return &nodo->pedido; }
    }
    return nullptr;
}

std::size_t ColaPedidos::cantidad() const noexcept { return cantidad_; }
bool ColaPedidos::vacia() const noexcept { return frente_ == nullptr; }
}
