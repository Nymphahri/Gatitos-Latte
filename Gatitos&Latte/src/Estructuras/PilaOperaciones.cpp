#include "PilaOperaciones.h"

namespace gatitos::estructuras
{
PilaOperaciones::~PilaOperaciones()
{
    while (desapilar()) {}
}

PilaOperaciones::PilaOperaciones(const PilaOperaciones& otra)
{
    // Copiar de cima a fondo conservando el orden, sin invertir la pila.
    Nodo* ultimo = nullptr;
    try {
        for (const Nodo* nodo = otra.cima_; nodo != nullptr; nodo = nodo->siguiente) {
            Nodo* nuevo = new Nodo(nodo->operacion);
            if (ultimo != nullptr) { ultimo->siguiente = nuevo; }
            else { cima_ = nuevo; }
            ultimo = nuevo;
            ++cantidad_;
        }
    } catch (...) {
        while (desapilar()) {}
        throw;
    }
}

PilaOperaciones& PilaOperaciones::operator=(const PilaOperaciones& otra)
{
    if (this == &otra) { return *this; }
    PilaOperaciones copia(otra);
    while (desapilar()) {}
    cima_ = copia.cima_;
    cantidad_ = copia.cantidad_;
    copia.cima_ = nullptr;
    copia.cantidad_ = 0;
    return *this;
}

void PilaOperaciones::apilar(const dominio::OperacionPedido& operacion)
{
    Nodo* nuevo = new Nodo(operacion);
    nuevo->siguiente = cima_;
    cima_ = nuevo;
    ++cantidad_;
}

bool PilaOperaciones::desapilar() noexcept
{
    if (cima_ == nullptr) { return false; }
    Nodo* retirado = cima_;
    cima_ = cima_->siguiente;
    delete retirado;
    --cantidad_;
    return true;
}

const dominio::OperacionPedido* PilaOperaciones::cima() const noexcept
{
    return cima_ != nullptr ? &cima_->operacion : nullptr;
}

std::size_t PilaOperaciones::cantidad() const noexcept { return cantidad_; }
bool PilaOperaciones::vacia() const noexcept { return cima_ == nullptr; }
}
