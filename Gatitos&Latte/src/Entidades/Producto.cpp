#include "Producto.h"

#include <stdexcept>
#include <utility>

namespace
{
bool contieneTexto(const std::string& texto)
{
    return texto.find_first_not_of(" \t\n\r\f\v") != std::string::npos;
}

void validarPrecio(std::int64_t precio)
{
    if (precio <= 0) {
        throw std::invalid_argument("El precio debe ser mayor que cero.");
    }
}
}

namespace gatitos::entidades
{
Producto::Producto(int codigo, std::string nombre, std::string categoria,
                   std::int64_t precioCentimos, bool disponible)
    : codigo_(codigo), nombre_(std::move(nombre)), categoria_(std::move(categoria)),
      precioCentimos_(precioCentimos), disponible_(disponible)
{
    if (codigo_ <= 0) {
        throw std::invalid_argument("El codigo debe ser mayor que cero.");
    }
    if (!contieneTexto(nombre_)) {
        throw std::invalid_argument("El nombre no puede estar vacio.");
    }
    if (!contieneTexto(categoria_)) {
        throw std::invalid_argument("La categoria no puede estar vacia.");
    }
    validarPrecio(precioCentimos_);
}

int Producto::codigo() const noexcept { return codigo_; }
const std::string& Producto::nombre() const noexcept { return nombre_; }
const std::string& Producto::categoria() const noexcept { return categoria_; }
std::int64_t Producto::precioCentimos() const noexcept { return precioCentimos_; }
bool Producto::disponible() const noexcept { return disponible_; }

void Producto::cambiarPrecio(std::int64_t precioCentimos)
{
    validarPrecio(precioCentimos);
    precioCentimos_ = precioCentimos;
}

void Producto::cambiarDisponibilidad(bool disponible) noexcept
{
    disponible_ = disponible;
}
}
