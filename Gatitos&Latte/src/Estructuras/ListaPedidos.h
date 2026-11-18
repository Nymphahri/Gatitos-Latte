#pragma once

#include "../Dominio/Pedido.h"
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

    void agregar(const dominio::Pedido& pedido);
    bool eliminar(int numero) noexcept;
    void limpiar() noexcept;
    [[nodiscard]] const dominio::Pedido* primero() const noexcept;
    [[nodiscard]] const dominio::Pedido* buscar(int numero) const noexcept;
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] bool vacia() const noexcept;

private:
    struct Nodo
    {
        explicit Nodo(const dominio::Pedido& dato) : pedido(dato) {}
        dominio::Pedido pedido;
        Nodo* siguiente = nullptr;
    };
    Nodo* primero_ = nullptr;
    Nodo* ultimo_ = nullptr;
    std::size_t cantidad_ = 0;
};
}
