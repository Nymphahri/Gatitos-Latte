#include "EntradaConsola.h"

#include <charconv>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

namespace
{
std::string_view recortar(std::string_view texto)
{
    const auto primero = texto.find_first_not_of(" \t\r\n\f\v");

    if (primero == std::string_view::npos)
    {
        return {};
    }

    const auto ultimo = texto.find_last_not_of(" \t\r\n\f\v");
    return texto.substr(primero, ultimo - primero + 1);
}

bool digitos(std::string_view texto)
{
    if (texto.empty())
    {
        return false;
    }

    for (char caracter : texto)
    {
        if (caracter < '0' || caracter > '9')
        {
            return false;
        }
    }
    return true;
}
}

namespace gatitos::presentacion
{
std::optional<std::int64_t> convertirPrecio(std::string_view texto)
{
    texto = recortar(texto);
    const auto separador = texto.find_first_of(".,");
    const auto parteEntera = texto.substr(0, separador);

    if (!digitos(parteEntera))
    {
        return std::nullopt;
    }
    std::int64_t entero = 0;
    const auto resultado =
        std::from_chars(parteEntera.data(),
        parteEntera.data() +
        parteEntera.size(),
        entero);

    if (resultado.ec != std::errc{})
    {
        return std::nullopt;
    }

    std::int64_t centimos = 0;

    if (separador != std::string_view::npos) {
        const auto fraccion = texto.substr(separador + 1);

        if (fraccion.size() > 2 || !digitos(fraccion))
        {
            return std::nullopt;
        }
        centimos = (fraccion[0] - '0') * 10;

        if (fraccion.size() == 2)
        {
            centimos += fraccion[1] - '0';
        }
    }
    const auto maximo = (std::numeric_limits<std::int64_t>::max)();

    if (entero > (maximo - centimos) / 100)
    {
        return std::nullopt;
    }
    const auto total = entero * 100 + centimos;

    if (total <= 0) { return std::nullopt; }
    return total;
}

EntradaConsola::EntradaConsola(std::istream& entrada, std::ostream& salida) noexcept
    : entrada_(entrada), salida_(salida) {}

std::string EntradaConsola::leerLinea(const char* mensaje)
{
    salida_ << mensaje << std::flush;
    std::string linea;

    if (!std::getline(entrada_, linea)) {
        if (entrada_.eof())
        {
            throw FinEntrada{};
        }
        throw std::runtime_error("  No se pudo leer la entrada.");
    }
    return linea;
}

int EntradaConsola::leerEntero(const char* mensaje, int minimo, int maximo)
{
    for (;;)
    {
        const auto linea = leerLinea(mensaje);
        const auto texto = recortar(linea);

        if (!texto.empty())
        {
            int valor = 0;
            const auto resultado = std::from_chars(texto.data(), texto.data() + texto.size(), valor);

            if (resultado.ec == std::errc{} && resultado.ptr == texto.data() + texto.size()
                && valor >= minimo && valor <= maximo)
            {
                return valor;
            }
        }
        if (minimo == 1 && maximo == (std::numeric_limits<int>::max)()) {
            salida_ << "  Dato inválido. Digite un entero mayor que cero dentro del rango admitido.\n";
        } else {
            salida_ << "  Opción inválida. Digite un número entero entre " << minimo << " y " << maximo << ".\n";
        }
    }
}

std::string EntradaConsola::leerTexto(const char* mensaje)
{
    for (;;)
    {
        const auto linea = leerLinea(mensaje);
        const auto texto = recortar(linea);
        if (!texto.empty())
        {
            return std::string(texto);
        }
        salida_ << "  El texto no puede estar vacío.\n";
    }
}

std::int64_t EntradaConsola::leerPrecio(const char* mensaje)
{
    for (;;)
    {
        const auto valor = convertirPrecio(leerLinea(mensaje));
        if (valor)
        {
            return *valor;
        }
        salida_ << "  Precio inválido. Digite un valor mayor que cero con hasta dos decimales.\n  Use punto o coma decimal, sin separar los miles. Ejemplo: 1800.50.\n";
    }
}
void EntradaConsola::esperarEnter()
{
    (void)leerLinea("\n  Presione ENTER para volver al menú.");
}
}
