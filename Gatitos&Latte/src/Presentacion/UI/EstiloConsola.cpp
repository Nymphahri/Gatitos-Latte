#include "EstiloConsola.h"
#include <iostream>
#include <string>
#include <string_view>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace
{
bool coloresDisponibles = false;
constexpr std::size_t ancho = 74;
constexpr const char* dorado = "\x1b[38;2;240;185;85m";
constexpr const char* verde = "\x1b[38;2;163;197;105m";
constexpr const char* rojo = "\x1b[38;2;235;135;130m";
constexpr const char* tenue = "\x1b[38;2;160;157;145m";
constexpr const char* normal = "\x1b[0m";

// Cuenta caracteres UTF-8 del texto del panel, sin contar bytes de continuación.
std::size_t longitudVisible(std::string_view texto)
{
    std::size_t longitud = 0;
    for (unsigned char caracter : texto) {
        if ((caracter & 0xC0) != 0x80) { ++longitud; }
    }
    return longitud;
}

void color(std::ostream& salida, const char* tono, bool activo)
{
    if (activo)
    {
        salida << tono;
    }
}

void borde(std::ostream& salida, bool colores)
{
    color(salida, dorado, colores);
    salida << "  +" << std::string(ancho, '-') << "+\n";
    color(salida, normal, colores);
}

void fila(std::ostream& salida, std::string_view texto, const char* tono, bool colores)
{
    color(salida, dorado, colores);
    salida << "  |";
    color(salida, tono, colores);
    salida << texto;
    const auto longitud = longitudVisible(texto);

    if (longitud < ancho)
    {
        salida << std::string(ancho - longitud, ' ');
    }

    color(salida, dorado, colores);
    salida << "|\n";
    color(salida, normal, colores);
}

void filaCentrada(std::ostream& salida, std::string_view texto, const char* tono, bool colores)
{
    const auto longitud = longitudVisible(texto);
    const auto margen = longitud < ancho ? (ancho - longitud) / 2 : 0;
    fila(salida, std::string(margen, ' ') + std::string(texto), tono, colores);
}

std::string campo(std::string_view texto, std::size_t anchoCampo, bool derecha = false)
{
    std::string visible(texto);
    if (longitudVisible(texto) > anchoCampo) {
        std::size_t fin = 0, caracteres = 0;
        while (fin < texto.size()) {
            if ((static_cast<unsigned char>(texto[fin]) & 0xC0) != 0x80) {
                if (caracteres == anchoCampo - 3) { break; }
                ++caracteres;
            }
            ++fin;
        }
        visible = std::string(texto.substr(0, fin)) + "...";
    }
    const std::string espacios(anchoCampo - longitudVisible(visible), ' ');
    return derecha ? espacios + visible : visible + espacios;
}

std::string precioFormateado(std::int64_t centimos)
{
    std::string entero = std::to_string(centimos / 100);
    for (std::ptrdiff_t i = static_cast<std::ptrdiff_t>(entero.size()) - 3; i > 0; i -= 3) {
        entero.insert(static_cast<std::size_t>(i), ",");
    }
    const auto fraccion = centimos % 100;
    return entero + '.' + (fraccion < 10 ? "0" : "") + std::to_string(fraccion);
}
std::string celda(std::string texto)
{
    const auto longitud = longitudVisible(texto);
    if (longitud < 17)
    {
        texto.append(17 - longitud, ' ');
    }
    return texto;
}
}

namespace gatitos::presentacion::ui
{
void EstiloConsola::configurar()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    const HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    coloresDisponibles = GetConsoleMode(consola, &modo)
        && SetConsoleMode(consola, modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

void EstiloConsola::mostrarMenuProductos(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    if (colores) { salida << "\x1b[2J\x1b[H"; } else { salida << '\n'; }
    borde(salida, colores);
    fila(salida, "   GATITOS & LATTE > Productos", dorado, colores);
    borde(salida, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   1  REGISTRAR PRODUCTO", verde, colores);
    fila(salida, "        Agregar un producto al catálogo de la cafetería.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   2  VER CATÁLOGO", verde, colores);
    fila(salida, "        Mostrar todos los productos registrados.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   3  BUSCAR PRODUCTO", verde, colores);
    fila(salida, "        Consultar por código con búsqueda secuencial o binaria.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   4  ORDENAR CATÁLOGO", verde, colores);
    fila(salida, "        Organizar los productos por código, nombre o precio.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   5  CONSULTAR ÁRBOL DE PRODUCTOS", verde, colores);
    fila(salida, "        Buscar por código o muestra el recorrido inorden.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0  VOLVER", rojo, colores);
    fila(salida, "        Salir al menú principal.", tenue, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
}

void EstiloConsola::mostrarMenuBusqueda(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    if (colores) { salida << "\x1b[2J\x1b[H"; } else { salida << '\n'; }
    borde(salida, colores);
    fila(salida, "   GATITOS & LATTE > Productos > Buscar", dorado, colores);
    borde(salida, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   1   BÚSQUEDA SECUENCIAL", verde, colores);
    fila(salida, "        Revisa los productos uno por uno hasta encontrar el código.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   2   BÚSQUEDA BINARIA", verde, colores);
    fila(salida, "        Busca por mitades en el catálogo ordenado por código.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0   VOLVER A PRODUCTOS", rojo, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
}

void EstiloConsola::mostrarMenuArbol(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    if (colores) { salida << "\x1b[2J\x1b[H"; } else { salida << '\n'; }
    borde(salida, colores);
    fila(salida, "   GATITOS & LATTE > Productos > Árbol", dorado, colores);
    borde(salida, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   1   BUSCAR POR CÓDIGO", verde, colores);
    fila(salida, "        Localiza un producto en el árbol binario de búsqueda.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   2   MOSTRAR RECORRIDO INORDEN", verde, colores);
    fila(salida, "        Lista los productos del árbol en orden de código.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0   VOLVER A PRODUCTOS", rojo, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
}
void EstiloConsola::mostrarEncabezado(std::ostream& salida, std::string_view titulo)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    if (colores) { salida << "\x1b[2J\x1b[H"; }

    else { salida << '\n'; }
    borde(salida, colores);
    fila(salida, "   GATITOS & LATTE > " + std::string(titulo), dorado, colores);
    borde(salida, colores);
    salida << '\n';
}

void EstiloConsola::mostrarMenuOrden(std::ostream& salida)
{
    mostrarEncabezado(salida, "Productos > Ordenar");
    const bool colores = coloresDisponibles && &salida == &std::cout;
    fila(salida, "   1   Código     De menor a mayor.", verde, colores);
    fila(salida, "   2   Nombre     En orden alfabético.", verde, colores);
    fila(salida, "   3   Precio     De menor a mayor.", verde, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0   Volver a Productos", rojo, colores);
    borde(salida, colores);
}

void EstiloConsola::iniciarTabla(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    color(salida, dorado, colores);
    salida << "  " << campo("Código", 10) << ' ' << campo("Nombre", 22) << ' '
           << campo("Categoría", 16) << ' ' << campo("Precio (CRC)", 24, true) << "Disponibilidad\n";
    color(salida, tenue, colores);
    salida << "  " << std::string(82, '-') << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::mostrarFilaProducto(std::ostream& salida, const entidades::Producto& producto)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    salida << "  " << campo(std::to_string(producto.codigo()), 10) << ' '
           << campo(producto.nombre(), 22) << ' ' << campo(producto.categoria(), 16) << ' '
           << campo(precioFormateado(producto.precioCentimos()), 24, true) << "  ";
    color(salida, producto.disponible() ? verde : rojo, colores);
    salida << (producto.disponible() ? "Sí" : "No") << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::terminarTabla(std::ostream& salida, std::size_t cantidad)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    color(salida, tenue, colores);
    salida << "  " << std::string(82, '-') << '\n';

    if (cantidad == 0)
    {
        salida << "  No hay productos registrados.\n";
    }

    else
    {
        salida << "  " << cantidad << (cantidad == 1 ? " producto registrado.\n" : " productos registrados.\n");
    }
    color(salida, normal, colores);
}

void EstiloConsola::mostrarFicha(std::ostream& salida, const entidades::Producto& producto)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    const auto detalle = [&](std::string_view etiqueta, const std::string& valor, const char* tono) {
        const auto longitud = longitudVisible(etiqueta) + longitudVisible(valor);
        salida << "  " << etiqueta << ' ';
        color(salida, tenue, colores);
        salida << std::string(longitud < 68 ? 68 - longitud : 1, '.') << ' ';
        color(salida, tono, colores);
        salida << valor << '\n';
        color(salida, normal, colores);
    };
    detalle("Código", std::to_string(producto.codigo()), dorado);
    detalle("Nombre", producto.nombre(), normal);
    detalle("Categoría", producto.categoria(), normal);
    detalle("Precio", "CRC " + precioFormateado(producto.precioCentimos()), dorado);
    detalle("Disponible", producto.disponible() ? "Sí" : "No", producto.disponible() ? verde : rojo);
}
void EstiloConsola::mostrarMenuPedidos(std::ostream& salida)
{
    mostrarEncabezado(salida, "Pedidos");
    const bool colores = coloresDisponibles && &salida == &std::cout;
    fila(salida, "   1   REGISTRAR PEDIDO", verde, colores);
    fila(salida, "       Ingresa el cliente, el producto y la cantidad.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   2   ATENDER SIGUIENTE PEDIDO", verde, colores);
    fila(salida, "       Consulta y atiende al primero de la cola.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   3   CONSULTAR PEDIDOS", verde, colores);
    fila(salida, "       Revisa los pedidos o busca por número.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   4   VER HISTORIAL", verde, colores);
    fila(salida, "       Muestra primero las operaciones más recientes.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   5   ELIMINAR PEDIDO PROCESADO", rojo, colores);
    fila(salida, "       Selecciona un pedido entregado y confirma su eliminación.", tenue, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0   VOLVER AL MENÚ PRINCIPAL", rojo, colores);
    borde(salida, colores);
}

void EstiloConsola::mostrarMenuConsultaPedidos(std::ostream& salida)
{
    mostrarEncabezado(salida, "Pedidos > Consultar");
    const bool colores = coloresDisponibles && &salida == &std::cout;
    fila(salida, "   1   Todos los pedidos", verde, colores);
    fila(salida, "   2   Pedidos pendientes", verde, colores);
    fila(salida, "   3   Pedidos procesados", verde, colores);
    fila(salida, "   4   Buscar por número", verde, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   0   Volver a Pedidos", rojo, colores);
    borde(salida, colores);
}

void EstiloConsola::mostrarFichaPedido(std::ostream& salida, const entidades::Pedido& pedido)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    color(salida, dorado, colores);
    salida << "\n  PEDIDO #" << pedido.numero() << '\n';
    color(salida, normal, colores);
    salida << "  Cliente:          " << pedido.cliente()
           << "\n  Producto:         " << pedido.producto().nombre() << " (" << pedido.producto().codigo() << ')'
           << "\n  Cantidad:         " << pedido.cantidad()
           << "\n  Precio unitario:  CRC " << precioFormateado(pedido.precioUnitarioCentimos())
           << "\n  Total:            CRC " << precioFormateado(pedido.totalCentimos())
           << "\n  Estado:           ";
    const bool entregado = pedido.estado() == entidades::EstadoPedido::Entregado;
    color(salida, entregado ? verde : dorado, colores);
    salida << (entregado ? "Entregado" : "Pendiente") << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::iniciarTablaPedidos(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    color(salida, dorado, colores);
    salida << "  " << campo("Pedido", 10) << ' ' << campo("Cliente", 14) << ' '
           << campo("Producto", 18) << ' ' << campo("Cant.", 10, true) << ' '
           << campo("Total (CRC)", 24, true) << "  Estado\n";
    color(salida, tenue, colores);
    salida << "  " << std::string(91, '-') << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::mostrarFilaPedido(std::ostream& salida, const entidades::Pedido& pedido)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    salida << "  " << campo(std::to_string(pedido.numero()), 10) << ' '
           << campo(pedido.cliente(), 14) << ' ' << campo(pedido.producto().nombre(), 18) << ' '
           << campo(std::to_string(pedido.cantidad()), 10, true) << ' '
           << campo(precioFormateado(pedido.totalCentimos()), 24, true) << "  ";
    const bool entregado = pedido.estado() == entidades::EstadoPedido::Entregado;
    color(salida, entregado ? verde : dorado, colores);
    salida << (entregado ? "Entregado" : "Pendiente") << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::iniciarHistorial(std::ostream& salida)
{
    mostrarEncabezado(salida, "Pedidos > Historial");
    salida << "  Operaciones más recientes primero.\n\n";
    const bool colores = coloresDisponibles && &salida == &std::cout;
    color(salida, dorado, colores);
    salida << "  Pedido      Operación\n  " << std::string(55, '-') << '\n';
    color(salida, normal, colores);
}

void EstiloConsola::mostrarOperacion(std::ostream& salida, const entidades::OperacionPedido& operacion)
{
    salida << "  " << campo(std::to_string(operacion.numeroPedido()), 10) << "  ";
    switch (operacion.tipo()) {
    case entidades::TipoOperacionPedido::Registro: salida << "Registro de pedido"; break;
    case entidades::TipoOperacionPedido::Entrega: salida << "Entrega de pedido"; break;
    case entidades::TipoOperacionPedido::Eliminacion: salida << "Eliminación de pedido procesado"; break;
    }
    salida << '\n';
}
void EstiloConsola::mostrarConfirmacionAtencion(std::ostream& salida)
{
    salida << "\n  1   Atender pedido\n  0   Volver sin atender\n";
}

void EstiloConsola::mostrarConfirmacionEliminacion(std::ostream& salida)
{
    salida << "\n  Se eliminará este pedido de procesados. El historial se conservará.\n"
              "  1   Confirmar eliminación\n  0   Cancelar\n";
}
void EstiloConsola::mostrarDespedida(std::ostream& salida)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;

    if (colores)
    {
        salida << "\x1b[2J\x1b[H";
    }

    else
    {
        salida << '\n';
    }

    borde(salida, colores);
    fila(salida, "", normal, colores);
    filaCentrada(salida, "   ( (      ", dorado, colores);
    filaCentrada(salida, "    ) )     ", dorado, colores);
    filaCentrada(salida, "  .------.  ", dorado, colores);
    filaCentrada(salida, "  |      |] ", dorado, colores);
    filaCentrada(salida, "  |      |  ", dorado, colores);
    filaCentrada(salida, "   `----'   ", dorado, colores);
    fila(salida, "", normal, colores);
    filaCentrada(salida, "¡Gracias por utilizar nuestro sistema!", dorado, colores);
    filaCentrada(salida, "GATITOS & LATTE", tenue, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
    salida << std::flush;
}

void EstiloConsola::mostrarMenuPrincipal(std::ostream& salida, const ResumenPanel& resumen)
{
    const bool colores = coloresDisponibles && &salida == &std::cout;
    if (colores)
    {
        salida << "\x1b[2J\x1b[H";
    }

    else
    {
        salida << '\n';
    }

    borde(salida, colores);
    fila(salida, R"(   /\_/\       GATITOS & LATTE Café, armonía y buena atención)", dorado, colores);
    fila(salida, R"(  ( o.o )      Sistema de gestión de cafetería)", tenue, colores);
    fila(salida, R"(   > ^ <)", dorado, colores);
    borde(salida, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   " + celda("PRODUCTOS") + celda("PENDIENTES") + celda("PROCESADOS") + celda("HISTORIAL"), tenue, colores);
    fila(salida, "   " + celda(std::to_string(resumen.productos)) + celda(std::to_string(resumen.pendientes))
         + celda(std::to_string(resumen.procesados)) + celda(std::to_string(resumen.operaciones)), verde, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
    fila(salida, "   MENÚ PRINCIPAL", dorado, colores);
    fila(salida, "", normal, colores);
    fila(salida, "   1   Gestión de productos", normal, colores);
    fila(salida, "   2   Gestión de pedidos", normal, colores);
    fila(salida, "   3   Salir", rojo, colores);
    fila(salida, "", normal, colores);
    borde(salida, colores);
    fila(salida, "   Digite una opción y pulse ENTER.", tenue, colores);
    borde(salida, colores);
}
}
