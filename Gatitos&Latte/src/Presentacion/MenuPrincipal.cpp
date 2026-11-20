#include "MenuPrincipal.h"
#include "UI/EstiloConsola.h"
#include <istream>
#include <ostream>

namespace gatitos::presentacion
{
MenuPrincipal::MenuPrincipal(aplicacion::ServicioProductos& productos,
    aplicacion::ServicioPedidos& pedidos,
    std::istream& entrada, std::ostream& salida) noexcept:servicioProductos_(productos),
    servicioPedidos_(pedidos),
    catalogo_(productos, entrada, salida),
    pedidos_(pedidos, entrada, salida),
    entrada_(entrada, salida),
    flujoEntrada_(entrada), salida_(salida) {}

void MenuPrincipal::ejecutar()
{

    try
    {
        for (;;)
        {
            ui::EstiloConsola::mostrarMenuPrincipal(salida_,
                {
                servicioProductos_.cantidad(),
                servicioPedidos_.cantidadPendientes(),
                servicioPedidos_.cantidadProcesados(),
                servicioPedidos_.cantidadHistorial()
                }
            );

            const int opcion = entrada_.leerEntero("  \nOpción: ", 1, 3);

            if (opcion == 3)
            {
                ui::EstiloConsola::mostrarDespedida(salida_);
                return;
            }

            if (opcion == 1)
            {
                catalogo_.ejecutar();
            }

            else
            {
                pedidos_.ejecutar();
            }

            if (!flujoEntrada_)
            {
                return;
            }
        }

    } catch (const FinEntrada&)
    {
        salida_ << "\n  Entrada cerrada.\n";
    }
}
}
