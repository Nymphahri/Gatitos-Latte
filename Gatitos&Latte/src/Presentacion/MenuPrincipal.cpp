#include "MenuPrincipal.h"
#include <istream>
#include <ostream>

namespace gatitos::presentacion
{
MenuPrincipal::MenuPrincipal(aplicacion::ServicioProductos& productos, aplicacion::ServicioPedidos& pedidos,
                             std::istream& entrada, std::ostream& salida) noexcept
    : catalogo_(productos, entrada, salida), pedidos_(pedidos, entrada, salida),
      entrada_(entrada, salida), flujoEntrada_(entrada), salida_(salida) {}

void MenuPrincipal::ejecutar()
{
    salida_ << "GATITOS & LATTE\nLos datos se conservan solo durante esta ejecucion.\n";
    try {
        for (;;) {
            salida_ << "\nMENU PRINCIPAL\n1. Productos\n2. Pedidos\n0. Salir\n";
            const int opcion = entrada_.leerEntero("Seleccione una opcion: ", 0, 2);
            if (opcion == 0) { salida_ << "Hasta luego.\n"; return; }
            if (opcion == 1) { catalogo_.ejecutar(); }
            else { pedidos_.ejecutar(); }
            if (!flujoEntrada_) { return; }
        }
    } catch (const FinEntrada&) { salida_ << "\nEntrada cerrada.\n"; }
}
}
