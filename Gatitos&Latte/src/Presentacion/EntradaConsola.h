#pragma once

#include <cstdint>
#include <exception>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

namespace gatitos::presentacion
{
class FinEntrada final : public std::exception
{
public:
    const char* what() const noexcept override { return "Entrada cerrada."; }
};

// Sin separadores de miles. Admite punto o coma y hasta dos decimales.
[[nodiscard]] std::optional<std::int64_t> convertirPrecio(std::string_view texto);

class EntradaConsola
{
public:
    EntradaConsola(std::istream& entrada, std::ostream& salida) noexcept;
    int leerEntero(const char* mensaje, int minimo, int maximo);
    std::string leerTexto(const char* mensaje);
    std::int64_t leerPrecio(const char* mensaje);

private:
    std::string leerLinea(const char* mensaje);
    std::istream& entrada_;
    std::ostream& salida_;
};
}
