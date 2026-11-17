#pragma once

#include "../Estructuras/ColaPedidos.h"
#include <optional>

namespace gatitos::datos
{
class RegistroPedidos
{
public:
    [[nodiscard]] int siguienteNumero() const;
    void agregar(const dominio::Pedido& pedido);
    [[nodiscard]] std::size_t cantidadPendientes() const noexcept;
    [[nodiscard]] std::optional<dominio::Pedido> buscar(int numero) const;
    [[nodiscard]] std::optional<dominio::Pedido> siguiente() const;
    [[nodiscard]] estructuras::ColaPedidos pendientes() const;

private:
    estructuras::ColaPedidos pendientes_;
    std::int64_t proximoNumero_ = 1;
};
}
