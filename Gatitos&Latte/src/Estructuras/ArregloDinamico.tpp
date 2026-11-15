#pragma once

#include <stdexcept>
#include <utility>

namespace gatitos::estructuras
{
template<class T>
ArregloDinamico<T>::~ArregloDinamico()
{
    limpiar();
    if (datos_ != nullptr) { memoria_.deallocate(datos_, capacidad_); }
}

template<class T>
ArregloDinamico<T>::ArregloDinamico(const ArregloDinamico& otro)
{
    // El temporal libera las copias parciales si una construccion falla.
    ArregloDinamico temporal;
    temporal.reservar(otro.tamano_);
    for (std::size_t i = 0; i < otro.tamano_; ++i) {
        temporal.agregar(otro.datos_[i]);
    }
    intercambiar(temporal);
}

template<class T>
ArregloDinamico<T>& ArregloDinamico<T>::operator=(const ArregloDinamico& otro)
{
    if (this != &otro) {
        ArregloDinamico temporal(otro);
        intercambiar(temporal);
    }
    return *this;
}

template<class T>
ArregloDinamico<T>::ArregloDinamico(ArregloDinamico&& otro) noexcept
{
    intercambiar(otro);
}

template<class T>
ArregloDinamico<T>& ArregloDinamico<T>::operator=(ArregloDinamico&& otro) noexcept
{
    if (this != &otro) {
        ArregloDinamico temporal(std::move(otro));
        intercambiar(temporal);
    }
    return *this;
}

template<class T>
void ArregloDinamico<T>::intercambiar(ArregloDinamico& otro) noexcept
{
    // std::allocator no tiene estado; cualquiera de sus instancias puede liberar el bloque.
    std::swap(datos_, otro.datos_);
    std::swap(tamano_, otro.tamano_);
    std::swap(capacidad_, otro.capacidad_);
}

template<class T>
std::size_t ArregloDinamico<T>::tamano() const noexcept { return tamano_; }

template<class T>
std::size_t ArregloDinamico<T>::capacidad() const noexcept { return capacidad_; }

template<class T>
bool ArregloDinamico<T>::vacio() const noexcept { return tamano_ == 0; }

template<class T>
T& ArregloDinamico<T>::en(std::size_t indice)
{
    if (indice >= tamano_) { throw std::out_of_range("Indice fuera del arreglo."); }
    return datos_[indice];
}

template<class T>
const T& ArregloDinamico<T>::en(std::size_t indice) const
{
    if (indice >= tamano_) { throw std::out_of_range("Indice fuera del arreglo."); }
    return datos_[indice];
}

template<class T>
void ArregloDinamico<T>::agregar(const T& valor)
{
    if (tamano_ == capacidad_) {
        const auto limite = std::allocator_traits<std::allocator<T>>::max_size(memoria_);
        if (tamano_ == limite) { throw std::length_error("Capacidad maxima alcanzada."); }
        const auto nueva = capacidad_ == 0 ? 1 :
            (capacidad_ > limite / 2 ? limite : capacidad_ * 2);
        // Protege agregar(en(i)): reservar invalida las referencias al bloque anterior.
        T copia(valor);
        reservar(nueva);
        std::construct_at(datos_ + tamano_, copia);
    } else {
        std::construct_at(datos_ + tamano_, valor);
    }
    ++tamano_;
}

template<class T>
void ArregloDinamico<T>::reservar(std::size_t nuevaCapacidad)
{
    if (nuevaCapacidad <= capacidad_) { return; }
    const auto limite = std::allocator_traits<std::allocator<T>>::max_size(memoria_);
    if (nuevaCapacidad > limite) { throw std::length_error("Capacidad solicitada demasiado grande."); }

    // allocator solo reserva memoria alineada; el crecimiento y la copia son manuales.
    T* nuevo = memoria_.allocate(nuevaCapacidad);
    std::size_t construidos = 0;
    try {
        for (; construidos < tamano_; ++construidos) {
            std::construct_at(nuevo + construidos, datos_[construidos]);
        }
    } catch (...) {
        while (construidos > 0) { std::destroy_at(nuevo + --construidos); }
        memoria_.deallocate(nuevo, nuevaCapacidad);
        throw;
    }

    for (std::size_t i = tamano_; i > 0; --i) { std::destroy_at(datos_ + i - 1); }
    if (datos_ != nullptr) { memoria_.deallocate(datos_, capacidad_); }
    datos_ = nuevo;
    capacidad_ = nuevaCapacidad;
}

template<class T>
void ArregloDinamico<T>::limpiar() noexcept
{
    while (tamano_ > 0) { std::destroy_at(datos_ + --tamano_); }
}
}
