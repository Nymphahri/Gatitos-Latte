#pragma once

#include "MenuCatalogo.h"
#include "MenuPedidos.h"

namespace gatitos::presentacion
{
class MenuPrincipal
{
public:
    MenuPrincipal(aplicacion::ServicioProductos& productos, aplicacion::ServicioPedidos& pedidos,
                  std::istream& entrada, std::ostream& salida) noexcept;
    void ejecutar();

private:
    MenuCatalogo catalogo_;
    MenuPedidos pedidos_;
    EntradaConsola entrada_;
    std::istream& flujoEntrada_;
    std::ostream& salida_;
};
}
