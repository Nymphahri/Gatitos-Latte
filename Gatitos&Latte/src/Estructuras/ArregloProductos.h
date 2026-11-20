#pragma once

#include "../Entidades/Producto.h"
#include <cstddef>

namespace gatitos::estructuras
{
// El bloque contiguo contiene punteros. Cada producto tiene un unico propietario:
// este arreglo. Las posiciones libres contienen nullptr.
class ArregloProductos
{
public:
    ArregloProductos() noexcept = default;
    ~ArregloProductos();
    ArregloProductos(const ArregloProductos& otro);
    ArregloProductos& operator=(const ArregloProductos& otro);

    [[nodiscard]] std::size_t tamano() const noexcept;
    [[nodiscard]] std::size_t capacidad() const noexcept;
    [[nodiscard]] bool vacio() const noexcept;
    [[nodiscard]] entidades::Producto& en(std::size_t indice);
    [[nodiscard]] const entidades::Producto& en(std::size_t indice) const;
    void agregar(const entidades::Producto& producto);
    void reservar(std::size_t capacidad);
    void intercambiar(std::size_t primero, std::size_t segundo);
    void limpiar() noexcept;
    bool eliminarUltimo() noexcept;

private:
    entidades::Producto** datos_ = nullptr;
    std::size_t tamano_ = 0;
    std::size_t capacidad_ = 0;
};
}
