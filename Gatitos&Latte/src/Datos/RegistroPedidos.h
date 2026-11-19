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
    void agregar(const dominio::Pedido& pedido);
    [[nodiscard]] std::size_t cantidadPendientes() const noexcept;
    [[nodiscard]] std::optional<dominio::Pedido> buscar(int numero) const;
    [[nodiscard]] std::optional<dominio::Pedido> siguiente() const;
    [[nodiscard]] estructuras::ColaPedidos pendientes() const;
    int atenderSiguiente(); // Devuelve el numero atendido, o 0 si no hay pendientes.
    [[nodiscard]] std::size_t cantidadProcesados() const noexcept;
    [[nodiscard]] estructuras::ListaPedidos procesados() const;
    [[nodiscard]] estructuras::PilaOperaciones historial() const;
    bool eliminarProcesado(int numero);

private:
    estructuras::ColaPedidos pendientes_;
    estructuras::ListaPedidos procesados_;
    estructuras::PilaOperaciones historial_;
    std::int64_t proximoNumero_ = 1;
};
}
