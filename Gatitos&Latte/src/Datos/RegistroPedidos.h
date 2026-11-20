#pragma once

#include "../Estructuras/ColaPedidos.h"
#include "../Estructuras/ListaPedidos.h"
#include "../Estructuras/PilaOperaciones.h"
#include <optional>

namespace gatitos::datos
{
class RegistroPedidos
{
public:
    [[nodiscard]] int siguienteNumero() const;
    void agregar(const entidades::Pedido& pedido);
    [[nodiscard]] std::size_t cantidadPendientes() const noexcept;
    [[nodiscard]] std::optional<entidades::Pedido> buscar(int numero) const;
    [[nodiscard]] std::optional<entidades::Pedido> siguiente() const;
    [[nodiscard]] estructuras::ColaPedidos pendientes() const;
    int atenderSiguiente(); // Devuelve el numero atendido, o 0 si no hay pendientes.
    [[nodiscard]] std::size_t cantidadProcesados() const noexcept;
    [[nodiscard]] estructuras::ListaPedidos procesados() const;
    [[nodiscard]] estructuras::PilaOperaciones historial() const;
    [[nodiscard]] std::size_t cantidadHistorial() const noexcept;
    bool eliminarProcesado(int numero);

private:
    estructuras::ColaPedidos pendientes_;
    estructuras::ListaPedidos procesados_;
    estructuras::PilaOperaciones historial_;
    std::int64_t proximoNumero_ = 1;
};
}
