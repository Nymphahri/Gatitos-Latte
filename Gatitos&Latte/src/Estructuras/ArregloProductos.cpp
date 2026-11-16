#include "ArregloProductos.h"
#include <limits>
#include <stdexcept>

namespace gatitos::estructuras
{
ArregloProductos::~ArregloProductos()
{
    limpiar();
    delete[] datos_;
}

ArregloProductos::ArregloProductos(const ArregloProductos& otro)
{
    try {
        reservar(otro.tamano_);
        for (std::size_t i = 0; i < otro.tamano_; ++i) { agregar(*otro.datos_[i]); }
    } catch (...) {
        limpiar();
        delete[] datos_;
        throw;
    }
}

ArregloProductos& ArregloProductos::operator=(const ArregloProductos& otro)
{
    if (this == &otro) { return *this; }
    // Primero se completa la copia: si falla, el destino permanece intacto.
    ArregloProductos copia(otro);
    limpiar();
    delete[] datos_;
    datos_ = copia.datos_;
    tamano_ = copia.tamano_;
    capacidad_ = copia.capacidad_;
    copia.datos_ = nullptr;
    copia.tamano_ = 0;
    copia.capacidad_ = 0;
    return *this;
}

std::size_t ArregloProductos::tamano() const noexcept { return tamano_; }
std::size_t ArregloProductos::capacidad() const noexcept { return capacidad_; }
bool ArregloProductos::vacio() const noexcept { return tamano_ == 0; }

dominio::Producto& ArregloProductos::en(std::size_t indice)
{
    if (indice >= tamano_) { throw std::out_of_range("Indice fuera del arreglo."); }
    return *datos_[indice];
}

const dominio::Producto& ArregloProductos::en(std::size_t indice) const
{
    if (indice >= tamano_) { throw std::out_of_range("Indice fuera del arreglo."); }
    return *datos_[indice];
}

void ArregloProductos::reservar(std::size_t nuevaCapacidad)
{
    if (nuevaCapacidad <= capacidad_) { return; }
    const auto limite = (std::numeric_limits<std::size_t>::max)() / sizeof(dominio::Producto*);
    if (nuevaCapacidad > limite) { throw std::length_error("Capacidad demasiado grande."); }
    auto** nuevo = new dominio::Producto*[nuevaCapacidad]{};
    for (std::size_t i = 0; i < tamano_; ++i) { nuevo[i] = datos_[i]; }
    // Solo se reemplaza el arreglo de punteros; los productos siguen vivos.
    delete[] datos_;
    datos_ = nuevo;
    capacidad_ = nuevaCapacidad;
}

void ArregloProductos::agregar(const dominio::Producto& producto)
{
    if (tamano_ == capacidad_) {
        const auto limite = (std::numeric_limits<std::size_t>::max)() / sizeof(dominio::Producto*);
        if (tamano_ == limite) { throw std::length_error("Capacidad maxima alcanzada."); }
        const auto nueva = capacidad_ == 0 ? 1 : (capacidad_ > limite / 2 ? limite : capacidad_ * 2);
        reservar(nueva);
    }
    datos_[tamano_] = new dominio::Producto(producto);
    ++tamano_;
}

void ArregloProductos::intercambiar(std::size_t primero, std::size_t segundo)
{
    if (primero >= tamano_ || segundo >= tamano_) { throw std::out_of_range("Indice fuera del arreglo."); }
    dominio::Producto* temporal = datos_[primero];
    datos_[primero] = datos_[segundo];
    datos_[segundo] = temporal;
}

void ArregloProductos::limpiar() noexcept
{
    for (std::size_t i = 0; i < tamano_; ++i) {
        delete datos_[i];
        datos_[i] = nullptr;
    }
    tamano_ = 0;
}
bool ArregloProductos::eliminarUltimo() noexcept
{
    if (vacio()) { return false; }
    --tamano_;
    delete datos_[tamano_];
    datos_[tamano_] = nullptr;
    return true;
}
}
