#pragma once

namespace gatitos::dominio
{
enum class TipoOperacionPedido { Registro, Entrega, Eliminacion };

class OperacionPedido
{
public:
    OperacionPedido(int numeroPedido, TipoOperacionPedido tipo);
    [[nodiscard]] int numeroPedido() const noexcept;
    [[nodiscard]] TipoOperacionPedido tipo() const noexcept;

private:
    int numeroPedido_;
    TipoOperacionPedido tipo_;
};
}
