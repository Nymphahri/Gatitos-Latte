#include "../Gatitos&Latte/src/Aplicacion/ServicioProductos.h"
#include "../Gatitos&Latte/src/Presentacion/MenuCatalogo.h"
#include "../Gatitos&Latte/src/Presentacion/EntradaConsola.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
using gatitos::datos::CatalogoProductos;
using gatitos::aplicacion::ServicioProductos;
using gatitos::presentacion::MenuCatalogo;
using gatitos::presentacion::convertirPrecio;

void exigir(bool condicion, const char* mensaje)
{
    if (!condicion) { throw std::runtime_error(mensaje); }
}

template<class Accion>
void esperarInvalido(Accion accion)
{
    try { accion(); }
    catch (const std::invalid_argument&) { return; }
    throw std::runtime_error("Debia rechazar los datos");
}

void registroYDuplicados()
{
    CatalogoProductos catalogo;
    ServicioProductos servicio(catalogo);
    exigir(servicio.cantidad() == 0 && !servicio.buscarPorCodigo(1), "Catalogo no inicia vacio");
    servicio.registrar(7, "Latte", "Cafe", 180050, true);
    esperarInvalido([&] { servicio.registrar(7, "Te", "Bebida", 90000, false); });
    esperarInvalido([&] { servicio.registrar(8, " ", "Bebida", 90000, true); });
    const auto encontrado = servicio.buscarPorCodigo(7);
    exigir(servicio.cantidad() == 1 && encontrado && encontrado->nombre() == "Latte", "Registro invalido altero catalogo");
    exigir(!servicio.buscarPorCodigo(999), "Busqueda inventa producto");
    for (int codigo = 8; codigo <= 80; ++codigo) {
        servicio.registrar(codigo, "Producto", "Bebida", 10000, false);
    }
    exigir(servicio.cantidad() == 74 && servicio.productoEn(73).codigo() == 80, "Crecimiento perdio registros");
    exigir(servicio.buscarPorCodigo(7)->precioCentimos() == 180050, "Precio inicial alterado");
    auto copia = servicio.buscarPorCodigo(7);
    copia->cambiarPrecio(1);
    exigir(servicio.buscarPorCodigo(7)->precioCentimos() == 180050, "Consulta expone almacenamiento mutable");
}

void preciosExactosYLimites()
{
    exigir(convertirPrecio("1800") == 180000, "Precio entero mal convertido");
    exigir(convertirPrecio("1800.5") == 180050, "Decimal mal convertido");
    exigir(convertirPrecio(" 1800,50 ") == 180050, "Coma decimal mal convertida");
    exigir(convertirPrecio("0.01") == 1, "Centimo perdido");
    exigir(convertirPrecio("92233720368547758.07") == 9223372036854775807LL, "Limite valido rechazado");
    const char* invalidos[] = {"", "0", "-1", "+1", "1.234", "1,800.50", "1.", ".50", "1e3", "nan", "12abc", "1 2", "92233720368547758.08", "999999999999999999999999"};
    for (const char* texto : invalidos) {
        exigir(!convertirPrecio(texto), "Formato de precio invalido aceptado");
    }
}

void recorridoCompletoMenu()
{
    CatalogoProductos catalogo;
    ServicioProductos servicio(catalogo);
    std::istringstream entrada("1\n7\nLatte de vainilla\nCafe\n1800,50\n1\n2\n3\n7\n3\n99\n0\n");
    std::ostringstream salida;
    MenuCatalogo menu(servicio, entrada, salida);
    menu.ejecutar();
    exigir(servicio.cantidad() == 1, "Menu no registro producto");
    exigir(salida.str().find("Latte de vainilla") != std::string::npos, "Consulta no muestra nombre");
    exigir(salida.str().find("1800.50") != std::string::npos, "Precio visible incorrecto");
    exigir(salida.str().find("No se encontro") != std::string::npos, "Busqueda sin resultado no informa");
}

void menuRecuperaEntradasInvalidas()
{
    CatalogoProductos catalogo;
    ServicioProductos servicio(catalogo);
    std::istringstream entrada("texto\n999999999999999999\n9\n1\n0\nabc\n1\n \nTe verde\n\nBebida\n-3\n1.234\n900.25\n2\n0\n0\n");
    std::ostringstream salida;
    MenuCatalogo menu(servicio, entrada, salida);
    menu.ejecutar();
    const auto p = servicio.buscarPorCodigo(1);
    exigir(p && p->nombre() == "Te verde" && p->precioCentimos() == 90025 && !p->disponible(), "No se recupero de entradas invalidas");
}

void menuVacioYDuplicado()
{
    CatalogoProductos catalogo;
    ServicioProductos servicio(catalogo);
    std::istringstream entrada("2\n1\n1\nLatte\nCafe\n1800\n1\n1\n1\nTe\nBebida\n900\n1\n0\n");
    std::ostringstream salida;
    MenuCatalogo menu(servicio, entrada, salida);
    menu.ejecutar();
    exigir(salida.str().find("No hay productos") != std::string::npos, "Lista vacia no informa");
    exigir(salida.str().find("Ya existe") != std::string::npos, "Duplicado no informa");
    exigir(servicio.cantidad() == 1 && servicio.productoEn(0).nombre() == "Latte", "Duplicado sobrescribe producto");
}

void cierreEntradaNoRegistraParciales()
{
    const char* sesiones[] = {"", "1\n", "1\n1\n", "1\n1\nCafe\n", "1\n1\nCafe\nBebida\n", "1\n1\nCafe\nBebida\n1800\n"};
    for (const char* sesion : sesiones) {
        CatalogoProductos catalogo;
        ServicioProductos servicio(catalogo);
        std::istringstream entrada(sesion);
        std::ostringstream salida;
        MenuCatalogo menu(servicio, entrada, salida);
        menu.ejecutar();
        exigir(servicio.cantidad() == 0, "Cierre de entrada creo producto parcial");
    }
}
}

int ejecutarPruebasCatalogo()
{
    struct Caso { const char* nombre; void (*ejecutar)(); };
    const Caso casos[] = {
        {"Registro y duplicados", registroYDuplicados},
        {"Precios exactos y limites", preciosExactosYLimites},
        {"Recorrido completo del menu", recorridoCompletoMenu},
        {"Recuperacion de entradas invalidas", menuRecuperaEntradasInvalidas},
        {"Menu vacio y duplicado", menuVacioYDuplicado},
        {"Cierre sin registros parciales", cierreEntradaNoRegistraParciales}
    };
    int fallos = 0;
    for (const auto& caso : casos) {
        try { caso.ejecutar(); std::cout << "OK: " << caso.nombre << '\n'; }
        catch (const std::exception& error) { ++fallos; std::cerr << "ERROR: " << caso.nombre << ": " << error.what() << '\n'; }
    }
    return fallos;
}
