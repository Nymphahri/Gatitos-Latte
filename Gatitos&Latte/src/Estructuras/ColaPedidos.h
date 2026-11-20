#pragma once

#include "../Entidades/Pedido.h"
#include <cstddef>

namespace gatitos::estructuras
{
class ColaPedidos
{
public:
    ColaPedidos() noexcept = default;
    ~ColaPedidos();
    ColaPedidos(const ColaPedidos& otra);
    ColaPedidos& operator=(const ColaPedidos& otra);

    void encolar(const entidades::Pedido& pedido);
    bool desencolar() noexcept;
    [[nodiscard]] const entidades::Pedido* frente() const noexcept;
    [[nodiscard]] const entidades::Pedido* final() const noexcept;
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
    Nodo* frente_ = nullptr;
    Nodo* final_ = nullptr;
    std::size_t cantidad_ = 0;
};
}
