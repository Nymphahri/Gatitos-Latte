#include "src/Presentacion/MenuCatalogo.h"
#include <exception>
#include <iostream>

int main()
{
    try {
        gatitos::datos::CatalogoProductos catalogo;
        gatitos::aplicacion::ServicioProductos servicio(catalogo);
        gatitos::presentacion::MenuCatalogo menu(servicio, std::cin, std::cout);
        menu.ejecutar();
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "No se pudo continuar: " << error.what() << '\n';
        return 1;
    }
}
