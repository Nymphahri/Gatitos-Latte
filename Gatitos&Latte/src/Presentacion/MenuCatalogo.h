#pragma once

#include "../Aplicacion/ServicioProductos.h"
#include "EntradaConsola.h"

namespace gatitos::presentacion
{
class MenuCatalogo
{
public:
    MenuCatalogo(aplicacion::ServicioProductos& servicio, std::istream& entrada,
                 std::ostream& salida) noexcept;
    void ejecutar();

private:
    void consultarBusqueda();
    void consultarArbol();
    void registrar();
    void listar() const;
    void buscar(bool binaria = false);
    void ordenar();
    void buscarEnArbol();
    void mostrarInorden() const;

    aplicacion::ServicioProductos& servicio_;
    EntradaConsola entrada_;
    std::ostream& salida_;
};
}
