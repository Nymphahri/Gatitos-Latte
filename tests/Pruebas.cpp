#include "../Gatitos&Latte/src/Dominio/Producto.h"
#include "../Gatitos&Latte/src/Estructuras/ArregloDinamico.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

using gatitos::dominio::Producto;
using gatitos::estructuras::ArregloDinamico;

namespace
{
void exigir(bool condicion, const char* mensaje)
{
    if (!condicion) { throw std::runtime_error(mensaje); }
}

template<class Excepcion, class Accion>
void esperarExcepcion(Accion accion)
{
    try { accion(); }
    catch (const Excepcion&) { return; }
    throw std::runtime_error("No se produjo la excepcion esperada");
}

void productoRechazaDatosInvalidos()
{
    esperarExcepcion<std::invalid_argument>([] { Producto p(0, "Latte", "Cafe", 180000); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(-1, "Latte", "Cafe", 180000); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(1, "", "Cafe", 180000); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(1, " \t\n", "Cafe", 180000); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(1, "Latte", "  ", 180000); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(1, "Latte", "Cafe", 0); });
    esperarExcepcion<std::invalid_argument>([] { Producto p(1, "Latte", "Cafe", -1); });
}

void productoConservaPrecioYValidaCambios()
{
    Producto p(7, "Latte", "Cafe", 180050);
    exigir(p.codigo() == 7 && p.precioCentimos() == 180050 && p.disponible(), "Producto inicial invalido");
    p.cambiarDisponibilidad(false);
    p.cambiarPrecio(190075);
    esperarExcepcion<std::invalid_argument>([&] { p.cambiarPrecio(-1); });
    exigir(p.precioCentimos() == 190075 && !p.disponible(), "Cambio invalido altero el producto");
    p.cambiarDisponibilidad(true);
    exigir(p.disponible(), "No se restauro disponibilidad");
}

void arregloVacioYLimites()
{
    ArregloDinamico<int> a;
    exigir(a.vacio() && a.tamano() == 0, "Arreglo no inicia vacio");
    esperarExcepcion<std::out_of_range>([&] { (void)a.en(0); });
    a.agregar(42);
    esperarExcepcion<std::out_of_range>([&] { (void)a.en(1); });
    const auto& lectura = a;
    exigir(lectura.en(0) == 42, "Lectura constante incorrecta");
    esperarExcepcion<std::out_of_range>([&] { (void)lectura.en(1); });
    esperarExcepcion<std::length_error>([&] { a.reservar((std::numeric_limits<std::size_t>::max)()); });
    exigir(a.tamano() == 1 && a.en(0) == 42, "Reserva imposible altero los datos");
}

void crecimientoConservaOrdenYProductos()
{
    ArregloDinamico<Producto> a;
    a.reservar(1);
    a.agregar(Producto(1, "Latte", "Cafe", 180000));
    a.agregar(a.en(0)); // La referencia de origen pertenece al bloque que va a crecer.
    for (int codigo = 2; codigo <= 64; ++codigo) {
        a.agregar(Producto(codigo, "Cafe", "Bebida", 100000 + codigo));
    }
    exigir(a.tamano() == 65 && a.capacidad() >= 65, "Crecimiento incompleto");
    exigir(a.en(0).nombre() == "Latte" && a.en(1).categoria() == "Cafe", "Alias perdido al crecer");
    for (std::size_t i = 2; i < a.tamano(); ++i) {
        exigir(a.en(i).codigo() == static_cast<int>(i), "Orden alterado durante crecimiento");
    }
    const auto capacidad = a.capacidad();
    a.reservar(1);
    exigir(a.capacidad() == capacidad, "Reservar redujo la capacidad");
}

void copiasIndependientes()
{
    ArregloDinamico<Producto> original;
    original.agregar(Producto(1, "Latte", "Cafe", 180000));
    auto copia = original;
    copia.en(0).cambiarPrecio(200000);
    exigir(original.en(0).precioCentimos() == 180000, "Copia comparte memoria");
    ArregloDinamico<Producto> asignado;
    asignado.agregar(Producto(2, "Te", "Bebida", 90000));
    asignado = original;
    asignado.en(0).cambiarDisponibilidad(false);
    exigir(original.en(0).disponible() && asignado.en(0).codigo() == 1, "Asignacion no independiente");
    auto& mismo = original;
    original = mismo;
    exigir(original.tamano() == 1 && original.en(0).codigo() == 1, "Autoasignacion perdio datos");
    ArregloDinamico<Producto> vacio;
    asignado = vacio;
    exigir(asignado.vacio(), "Asignacion vacia fallo");
}

void movimientoYReutilizacion()
{
    ArregloDinamico<int> origen;
    origen.agregar(7);
    ArregloDinamico<int> destino(std::move(origen));
    exigir(origen.vacio() && destino.en(0) == 7, "Movimiento incorrecto");
    origen.agregar(9);
    destino = std::move(origen);
    exigir(origen.vacio() && destino.en(0) == 9, "Asignacion por movimiento incorrecta");
    auto& mismo = destino;
    destino = std::move(mismo);
    exigir(destino.tamano() == 1 && destino.en(0) == 9, "Automovimiento perdio datos");
    destino.limpiar();
    exigir(destino.vacio(), "Limpiar no vacio el arreglo");
    destino.agregar(12);
    exigir(destino.en(0) == 12, "No se puede reutilizar despues de limpiar");
}

// Tipo de prueba para detectar objetos vivos y simular una copia que falla.
struct Registro
{
    inline static int vivos = 0;
    inline static int copiasRestantes = -1;
    int valor;
    explicit Registro(int dato) : valor(dato) { ++vivos; }
    Registro(const Registro& otro) : valor(otro.valor)
    {
        if (copiasRestantes == 0) { throw std::runtime_error("Copia interrumpida"); }
        if (copiasRestantes > 0) { --copiasRestantes; }
        ++vivos;
    }
    ~Registro() { --vivos; }
};

void excepcionesNoPierdenObjetos()
{
    {
        ArregloDinamico<Registro> a;
        a.agregar(Registro(10));
        a.agregar(Registro(20));
        const int vivos = Registro::vivos;
        Registro::copiasRestantes = 1;
        esperarExcepcion<std::runtime_error>([&] { a.reservar(a.capacidad() + 1); });
        exigir(Registro::vivos == vivos && a.tamano() == 2 && a.en(1).valor == 20, "Reserva fallida pierde objetos");
        Registro::copiasRestantes = 1;
        esperarExcepcion<std::runtime_error>([&] { auto copia = a; });
        exigir(Registro::vivos == vivos, "Constructor de copia pierde objetos");
        Registro::copiasRestantes = -1;
        ArregloDinamico<Registro> destino;
        destino.agregar(Registro(99));
        Registro::copiasRestantes = 1;
        esperarExcepcion<std::runtime_error>([&] { destino = a; });
        exigir(destino.tamano() == 1 && destino.en(0).valor == 99, "Asignacion fallida pierde destino");
        Registro::copiasRestantes = 0;
        esperarExcepcion<std::runtime_error>([&] { a.agregar(a.en(0)); });
        exigir(a.tamano() == 2 && a.en(0).valor == 10, "Insercion fallida altera datos");
        Registro::copiasRestantes = -1;
        a.limpiar();
        exigir(Registro::vivos == 1, "Limpiar no destruye los elementos");
    }
    exigir(Registro::vivos == 0, "Quedaron objetos vivos despues de destruir los arreglos");
}
}

int ejecutarPruebasCatalogo();

int main()
{
    struct Caso { const char* nombre; void (*ejecutar)(); };
    const Caso casos[] = {
        {"Producto rechaza datos invalidos", productoRechazaDatosInvalidos},
        {"Producto conserva precio y valida cambios", productoConservaPrecioYValidaCambios},
        {"Arreglo vacio y limites", arregloVacioYLimites},
        {"Crecimiento conserva orden y productos", crecimientoConservaOrdenYProductos},
        {"Copias independientes", copiasIndependientes},
        {"Movimiento y reutilizacion", movimientoYReutilizacion},
        {"Excepciones no pierden objetos", excepcionesNoPierdenObjetos}
    };
    int fallos = 0;
    for (const auto& caso : casos) {
        try { caso.ejecutar(); std::cout << "OK: " << caso.nombre << '\n'; }
        catch (const std::exception& error) {
            ++fallos;
            std::cerr << "ERROR: " << caso.nombre << ": " << error.what() << '\n';
        }
    }
    fallos += ejecutarPruebasCatalogo();
    std::cout << "Fallos: " << fallos << '\n';
    return fallos == 0 ? 0 : 1;
}
