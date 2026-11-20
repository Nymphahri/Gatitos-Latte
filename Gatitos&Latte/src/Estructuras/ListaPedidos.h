#pragma once

#include "../Entidades/Pedido.h"
#include <cstddef>

namespace gatitos::estructuras
{
class ListaPedidos
{
public:
    ListaPedidos() noexcept = default;
    ~ListaPedidos();
    ListaPedidos(const ListaPedidos& otra);
    ListaPedidos& operator=(const ListaPedidos& otra);

    void agregar(const entidades::Pedido& pedido);
    bool eliminar(int numero) noexcept;
    void limpiar() noexcept;
    [[nodiscard]] const entidades::Pedido* primero() const noexcept;
    [[nodiscard]] const entidades::Pedido* buscar(int numero) const noexcept;
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] bool vacia() const noexcept;

private:
    struct Nodo
    {
        explicit Nodo(const entidades::Pedido& dato) : pedido(dato) {}
        entidades::Pedido pedido;
        Nodo* siguiente = nullptr;
    };
    Nodo* primero_ = nullptr;
    Nodo* ultimo_ = nullptr;
    std::size_t cantidad_ = 0;
};
}
