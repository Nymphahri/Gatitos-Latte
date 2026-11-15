#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

namespace gatitos::estructuras
{
// Bloque contiguo de elementos. Solo [0, tamano_) contiene objetos construidos.
// T debe admitir copia; no necesita constructor por defecto.
template<class T>
class ArregloDinamico
{
    static_assert(std::is_copy_constructible_v<T>, "T debe admitir copia");
    static_assert(std::is_nothrow_destructible_v<T>, "El destructor de T no debe lanzar");

public:
    ArregloDinamico() noexcept = default;
    ~ArregloDinamico();
    ArregloDinamico(const ArregloDinamico& otro);
    ArregloDinamico& operator=(const ArregloDinamico& otro);
    ArregloDinamico(ArregloDinamico&& otro) noexcept;
    ArregloDinamico& operator=(ArregloDinamico&& otro) noexcept;

    [[nodiscard]] std::size_t tamano() const noexcept;
    [[nodiscard]] std::size_t capacidad() const noexcept;
    [[nodiscard]] bool vacio() const noexcept;
    [[nodiscard]] T& en(std::size_t indice);
    [[nodiscard]] const T& en(std::size_t indice) const;

    void agregar(const T& valor);
    void reservar(std::size_t capacidad);
    void limpiar() noexcept;

private:
    void intercambiar(ArregloDinamico& otro) noexcept;

    std::allocator<T> memoria_;
    T* datos_ = nullptr;
    std::size_t tamano_ = 0;
    std::size_t capacidad_ = 0;
};
}

#include "ArregloDinamico.tpp"
