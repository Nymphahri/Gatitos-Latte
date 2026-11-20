#include "MenuPedidos.h"
#include "UI/EstiloConsola.h"
#include <limits>
#include <ostream>
#include <stdexcept>

namespace gatitos::presentacion
{
MenuPedidos::MenuPedidos(aplicacion::ServicioPedidos& servicio,
    std::istream& entrada, std::ostream& salida) noexcept: servicio_(servicio),
    entrada_(entrada, salida),
    salida_(salida) {}

void MenuPedidos::ejecutar()
{
    try
    {
        for (;;)
        {
            ui::EstiloConsola::mostrarMenuPedidos(salida_);
            const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 5);

            if (opcion == 0)
            {
                return;
            }

            try
            {
                switch (opcion)
                {
                case 1: registrar(); break;
                case 2: atender(); break;
                case 3: consultar(); break;
                case 4: mostrarHistorial(); break;
                case 5: eliminarProcesado(); break;
                }

            } catch (const std::invalid_argument& error)
            {
                salida_ << "\n  No se pudo completar la operación: " << error.what() << '\n';
            }

            catch (const std::overflow_error& error)
            {
                salida_ << "\n  No se pudo completar la operación: " << error.what() << '\n';
            }

            if (opcion != 3)
            {
                entrada_.esperarEnter();
            }
        }
    } catch (const FinEntrada&) { salida_ << "\n  Entrada cerrada.\n"; }
}

void MenuPedidos::consultar()
{
    for (;;)
    {
        ui::EstiloConsola::mostrarMenuConsultaPedidos(salida_);
        const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 4);

        if (opcion == 0)
        {
            return;
        }

        ui::EstiloConsola::mostrarEncabezado(salida_, "Pedidos > Consultar");

        switch (opcion)
        {
        case 1: listarTodos(); break;
        case 2: listar(); break;
        case 3: listarProcesados(); break;
        case 4: buscar(); break;
        }
        entrada_.esperarEnter();
    }
}

void MenuPedidos::registrar()
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Pedidos > Registrar");
    const auto cliente = entrada_.leerTexto("  Cliente:          ");
    const int codigo = entrada_.leerEntero("  Código de producto: ", 1, (std::numeric_limits<int>::max)());
    const int cantidad = entrada_.leerEntero("  Cantidad:         ", 1, (std::numeric_limits<int>::max)());
    const int numero = servicio_.registrar(cliente, codigo, cantidad);
    salida_ << "\n  Pedido registrado correctamente.\n";
    ui::EstiloConsola::mostrarFichaPedido(salida_, *servicio_.buscar(numero));
}

void MenuPedidos::listar() const
{
    // Se recorre una copia: consultar no retira los pedidos de la cola original.
    auto copia = servicio_.pendientes();

    if (copia.vacia())
    {
        salida_ << "  No hay pedidos pendientes.\n";
        return;
    }

    salida_ << "\n  Pedidos pendientes — orden de llegada\n\n";
    ui::EstiloConsola::iniciarTablaPedidos(salida_);

    while (!copia.vacia())
    {
        ui::EstiloConsola::mostrarFilaPedido(salida_, *copia.frente());
        copia.desencolar();
    }
}

void MenuPedidos::atender()
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Pedidos > Atender siguiente");
    const auto pendiente = servicio_.siguiente();

    if (!pendiente)
    {
        salida_ << "  No hay pedidos pendientes.\n";
        return;
    }

    ui::EstiloConsola::mostrarFichaPedido(salida_, *pendiente);
    ui::EstiloConsola::mostrarConfirmacionAtencion(salida_);

    if (entrada_.leerEntero("\n  Opción: ", 0, 1) == 0)
    {
        return;
    }

    const int numero = servicio_.atenderSiguiente();
    salida_ << "\n  Pedido entregado correctamente.\n";
    ui::EstiloConsola::mostrarFichaPedido(salida_, *servicio_.buscar(numero));
}

void MenuPedidos::listarProcesados() const
{
    auto copia = servicio_.procesados();
    if (copia.vacia())
    {
        salida_ << "  No hay pedidos procesados.\n"; return;
    }

    salida_ << "\n  Pedidos procesados — orden de atención\n\n";
    ui::EstiloConsola::iniciarTablaPedidos(salida_);

    // Eliminar de esta copia permite recorrerla sin alterar los datos guardados.
    while (!copia.vacia())
    {
        const auto* pedido = copia.primero();
        ui::EstiloConsola::mostrarFilaPedido(salida_, *pedido);
        copia.eliminar(pedido->numero());
    }
}

void MenuPedidos::mostrarHistorial() const
{
    ui::EstiloConsola::iniciarHistorial(salida_);
    auto copia = servicio_.historial();
    if (copia.vacia())
    {
        salida_ << "  No hay operaciones en el historial.\n";
        return;
    }
    while (!copia.vacia())
    {
        ui::EstiloConsola::mostrarOperacion(salida_, *copia.cima());
        copia.desapilar(); // Consultar consume solo la copia, no el historial original.
    }
}
void MenuPedidos::listarTodos() const
{
    if (servicio_.cantidadPendientes() == 0 && servicio_.cantidadProcesados() == 0)
    {
        salida_ << "  No hay pedidos registrados.\n";
        return;
    }

    salida_ << "  Pedidos registrados, agrupados por estado.\n";
    listar();
    listarProcesados();
}

void MenuPedidos::eliminarProcesado()
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Pedidos > Eliminar procesado");
    const int numero = entrada_.leerEntero("  Número del pedido procesado: ", 1, (std::numeric_limits<int>::max)());
    const auto pedido = servicio_.buscar(numero);
    if (!pedido)
    {
        salida_ << "  No se encontró un pedido con ese número.\n";
        return;
    }

    if (pedido->estado() != entidades::EstadoPedido::Entregado) {
        salida_ << "  Este pedido sigue pendiente. Solo puede eliminar pedidos procesados.\n";
        return;
    }

    ui::EstiloConsola::mostrarFichaPedido(salida_, *pedido);
    ui::EstiloConsola::mostrarConfirmacionEliminacion(salida_);

    if (entrada_.leerEntero("\n  Opción: ", 0, 1) == 0)
    {
        salida_ << "  Eliminación cancelada. El pedido se conserva.\n";
        return;
    }

    if (servicio_.eliminarProcesado(numero)) {
        salida_ << "  Pedido eliminado de procesados correctamente.\n";
    }

    else
    {
        salida_ << "  No se encontró el pedido procesado.\n";
    }
}

void MenuPedidos::buscar()
{
    const int numero = entrada_.leerEntero("  Número de pedido: ", 1, (std::numeric_limits<int>::max)());
    const auto pedido = servicio_.buscar(numero);
    if (pedido)
    {
        ui::EstiloConsola::mostrarFichaPedido(salida_, *pedido);
    }

    else
    {
        salida_ << "  No se encontró un pedido con ese número.\n";
    }
}
}
