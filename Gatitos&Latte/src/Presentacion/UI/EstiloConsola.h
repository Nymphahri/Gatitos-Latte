#pragma once

#include <cstddef>
#include "../../Entidades/Pedido.h"
#include "../../Entidades/OperacionPedido.h"
#include <iosfwd>
#include <string_view>
#include "../../Entidades/Producto.h"

namespace gatitos::presentacion::ui
{
struct ResumenPanel
{
    std::size_t productos;
    std::size_t pendientes;
    std::size_t procesados;
    std::size_t operaciones;
};

class EstiloConsola
{
public:
    static void configurar();
    static void mostrarConfirmacionAtencion(std::ostream& salida);
    static void mostrarConfirmacionEliminacion(std::ostream& salida);
    static void mostrarMenuPedidos(std::ostream& salida);
    static void mostrarMenuConsultaPedidos(std::ostream& salida);
    static void mostrarFichaPedido(std::ostream& salida, const entidades::Pedido& pedido);
    static void iniciarTablaPedidos(std::ostream& salida);
    static void mostrarFilaPedido(std::ostream& salida, const entidades::Pedido& pedido);
    static void iniciarHistorial(std::ostream& salida);
    static void mostrarOperacion(std::ostream& salida, const entidades::OperacionPedido& operacion);
    static void mostrarEncabezado(std::ostream& salida, std::string_view titulo);
    static void mostrarMenuOrden(std::ostream& salida);
    static void iniciarTabla(std::ostream& salida);
    static void mostrarFilaProducto(std::ostream& salida, const entidades::Producto& producto);
    static void terminarTabla(std::ostream& salida, std::size_t cantidad);
    static void mostrarFicha(std::ostream& salida, const entidades::Producto& producto);
    static void mostrarMenuProductos(std::ostream& salida);
    static void mostrarMenuBusqueda(std::ostream& salida);
    static void mostrarMenuArbol(std::ostream& salida);
    static void mostrarDespedida(std::ostream& salida);
    static void mostrarMenuPrincipal(std::ostream& salida, const ResumenPanel& resumen);
};
}