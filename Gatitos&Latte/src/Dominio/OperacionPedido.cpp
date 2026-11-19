#include "OperacionPedido.h"
#include <stdexcept>

namespace gatitos::dominio
{
OperacionPedido::OperacionPedido(int numeroPedido, TipoOperacionPedido tipo)
    : numeroPedido_(numeroPedido), tipo_(tipo)
{
    if (numeroPedido_ <= 0) { throw std::invalid_argument("El numero de pedido debe ser positivo."); }
    if (tipo_ != TipoOperacionPedido::Registro && tipo_ != TipoOperacionPedido::Entrega &&
        tipo_ != TipoOperacionPedido::Eliminacion) {
        throw std::invalid_argument("Tipo de operacion de pedido invalido.");
    }
}

int OperacionPedido::numeroPedido() const noexcept { return numeroPedido_; }
TipoOperacionPedido OperacionPedido::tipo() const noexcept { return tipo_; }
}
