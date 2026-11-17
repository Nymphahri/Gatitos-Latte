#include "src/Presentacion/MenuPrincipal.h"
#include <exception>
#include <iostream>

int main()
{
    try {
        gatitos::datos::CatalogoProductos catalogo;
        gatitos::datos::RegistroPedidos registro;
        gatitos::aplicacion::ServicioProductos productos(catalogo);
        gatitos::aplicacion::ServicioPedidos pedidos(catalogo, registro);
        gatitos::presentacion::MenuPrincipal menu(productos, pedidos, std::cin, std::cout);
        menu.ejecutar();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "No se pudo continuar: " << error.what() << '\n';
        return 1;
    }
}
