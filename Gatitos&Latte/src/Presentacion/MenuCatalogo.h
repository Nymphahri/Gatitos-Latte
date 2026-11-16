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
    void registrar();
    void listar() const;
    void buscar(bool binaria = false);
    void ordenar();
    void mostrar(const dominio::Producto& producto) const;

    aplicacion::ServicioProductos& servicio_;
    EntradaConsola entrada_;
    std::ostream& salida_;
};
}
