#pragma once

#include "../Entidades/OperacionPedido.h"
#include <cstddef>

namespace gatitos::estructuras
{
class PilaOperaciones
{
public:
    PilaOperaciones() noexcept = default;
    ~PilaOperaciones();
    PilaOperaciones(const PilaOperaciones& otra);
    PilaOperaciones& operator=(const PilaOperaciones& otra);

    void apilar(const entidades::OperacionPedido& operacion);
    bool desapilar() noexcept;
    [[nodiscard]] const entidades::OperacionPedido* cima() const noexcept;
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] bool vacia() const noexcept;

private:
    struct Nodo
    {
        explicit Nodo(const entidades::OperacionPedido& dato) : operacion(dato) {}
        entidades::OperacionPedido operacion;
        Nodo* siguiente = nullptr;
    };
    Nodo* cima_ = nullptr;
    std::size_t cantidad_ = 0;
};
}
