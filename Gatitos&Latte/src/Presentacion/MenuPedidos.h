#pragma once

#include "../Aplicacion/ServicioPedidos.h"
#include "EntradaConsola.h"

namespace gatitos::presentacion
{
class MenuPedidos
{
public:
    MenuPedidos(aplicacion::ServicioPedidos& servicio, std::istream& entrada, std::ostream& salida) noexcept;
    void ejecutar();

private:
    void registrar();
    void listar() const;
    void mostrarSiguiente() const;
    void buscar();
    void atender();
    void listarProcesados() const;
    void mostrar(const dominio::Pedido& pedido) const;
    aplicacion::ServicioPedidos& servicio_;
    EntradaConsola entrada_;
    std::ostream& salida_;
};
}
