#include "MenuPedidos.h"
#include <limits>
#include <ostream>
#include <stdexcept>

namespace
{
void mostrarImporte(std::ostream& salida, std::int64_t centimos)
{
    const auto fraccion = centimos % 100;
    salida << "CRC " << centimos / 100 << '.' << (fraccion < 10 ? "0" : "") << fraccion;
}
}

namespace gatitos::presentacion
{
MenuPedidos::MenuPedidos(aplicacion::ServicioPedidos& servicio, std::istream& entrada, std::ostream& salida) noexcept
    : servicio_(servicio), entrada_(entrada, salida), salida_(salida) {}

void MenuPedidos::ejecutar()
{
    try {
        for (;;) {
            salida_ << "\nPEDIDOS\n1. Registrar pedido\n2. Ver pendientes\n"
                       "3. Ver siguiente pedido\n4. Buscar pedido por numero\n0. Volver\n";
            const int opcion = entrada_.leerEntero("Seleccione una opcion: ", 0, 4);
            if (opcion == 0) { return; }
            try {
                switch (opcion) {
                case 1: registrar(); break;
                case 2: listar(); break;
                case 3: mostrarSiguiente(); break;
                case 4: buscar(); break;
                }
            } catch (const std::invalid_argument& error) { salida_ << error.what() << '\n'; }
            catch (const std::overflow_error& error) { salida_ << error.what() << '\n'; }
        }
    } catch (const FinEntrada&) { salida_ << "\nEntrada cerrada. No se guardan pedidos incompletos.\n"; }
}

void MenuPedidos::registrar()
{
    const auto cliente = entrada_.leerTexto("Nombre del cliente: ");
    const int codigo = entrada_.leerEntero("Codigo del producto: ", 1, (std::numeric_limits<int>::max)());
    const int cantidad = entrada_.leerEntero("Cantidad: ", 1, (std::numeric_limits<int>::max)());
    const int numero = servicio_.registrar(cliente, codigo, cantidad);
    salida_ << "Pedido registrado correctamente.\n";
    mostrar(*servicio_.buscar(numero));
}

void MenuPedidos::mostrar(const dominio::Pedido& pedido) const
{
    salida_ << "\nPedido #" << pedido.numero() << "\nCliente: " << pedido.cliente()
            << "\nProducto: " << pedido.producto().nombre() << " (" << pedido.producto().codigo() << ")"
            << "\nCantidad: " << pedido.cantidad() << "\nPrecio unitario: ";
    mostrarImporte(salida_, pedido.precioUnitarioCentimos());
    salida_ << "\nTotal: ";
    mostrarImporte(salida_, pedido.totalCentimos());
    switch (pedido.estado()) {
    case dominio::EstadoPedido::Pendiente: salida_ << "\nEstado: Pendiente\n"; break;
    }
}

void MenuPedidos::listar() const
{
    // Se recorre una copia: consultar no retira los pedidos de la cola original.
    auto copia = servicio_.pendientes();
    if (copia.vacia()) { salida_ << "No hay pedidos pendientes.\n"; return; }
    salida_ << "Pedidos pendientes en orden de llegada:\n";
    while (!copia.vacia()) { mostrar(*copia.frente()); copia.desencolar(); }
}

void MenuPedidos::mostrarSiguiente() const
{
    const auto pedido = servicio_.siguiente();
    if (pedido) { salida_ << "Siguiente pedido por atender:\n"; mostrar(*pedido); }
    else { salida_ << "No hay pedidos pendientes.\n"; }
}

void MenuPedidos::buscar()
{
    const int numero = entrada_.leerEntero("Numero de pedido: ", 1, (std::numeric_limits<int>::max)());
    const auto pedido = servicio_.buscar(numero);
    if (pedido) { mostrar(*pedido); }
    else { salida_ << "No se encontro un pedido con ese numero.\n"; }
}
}
