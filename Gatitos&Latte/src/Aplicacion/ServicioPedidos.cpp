#include "ServicioPedidos.h"
#include <stdexcept>
#include <utility>

namespace gatitos::aplicacion
{
ServicioPedidos::ServicioPedidos(const datos::CatalogoProductos& productos, datos::RegistroPedidos& pedidos) noexcept
    : productos_(productos), pedidos_(pedidos) {}

int ServicioPedidos::registrar(std::string cliente, int codigoProducto, int cantidad)
{
    const auto producto = productos_.buscarEnArbol(codigoProducto);
    if (!producto) { throw std::invalid_argument("No existe un producto con ese codigo."); }
    const int numero = pedidos_.siguienteNumero();
    const dominio::Pedido pedido(numero, std::move(cliente), *producto, cantidad);
    pedidos_.agregar(pedido);
    return numero;
}

std::size_t ServicioPedidos::cantidadPendientes() const noexcept { return pedidos_.cantidadPendientes(); }
std::optional<dominio::Pedido> ServicioPedidos::buscar(int numero) const { return pedidos_.buscar(numero); }
std::optional<dominio::Pedido> ServicioPedidos::siguiente() const { return pedidos_.siguiente(); }
estructuras::ColaPedidos ServicioPedidos::pendientes() const { return pedidos_.pendientes(); }
int ServicioPedidos::atenderSiguiente() { return pedidos_.atenderSiguiente(); }
std::size_t ServicioPedidos::cantidadProcesados() const noexcept { return pedidos_.cantidadProcesados(); }
estructuras::ListaPedidos ServicioPedidos::procesados() const { return pedidos_.procesados(); }
estructuras::PilaOperaciones ServicioPedidos::historial() const { return pedidos_.historial(); }
bool ServicioPedidos::eliminarProcesado(int numero) { return pedidos_.eliminarProcesado(numero); }
}
