#pragma once

#include <cstdint>
#include <string>

namespace gatitos::dominio
{
class Producto
{
public:
    // Precio en centimos: 180000 representa 1800 colones.
    Producto(int codigo, std::string nombre, std::string categoria,
             std::int64_t precioCentimos, bool disponible = true);

    [[nodiscard]] int codigo() const noexcept;
    [[nodiscard]] const std::string& nombre() const noexcept;
    [[nodiscard]] const std::string& categoria() const noexcept;
    [[nodiscard]] std::int64_t precioCentimos() const noexcept;
    [[nodiscard]] bool disponible() const noexcept;

    void cambiarPrecio(std::int64_t precioCentimos);
    void cambiarDisponibilidad(bool disponible) noexcept;

private:
    int codigo_;
    std::string nombre_;
    std::string categoria_;
    std::int64_t precioCentimos_;
    bool disponible_;
};
}
