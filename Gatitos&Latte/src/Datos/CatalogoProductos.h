#pragma once

#include "../Dominio/Producto.h"
#include "../Estructuras/ArregloDinamico.h"
#include <optional>

namespace gatitos::datos
{
class CatalogoProductos
{
public:
    void agregar(const dominio::Producto& producto);
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] const dominio::Producto& en(std::size_t indice) const;
    [[nodiscard]] std::optional<dominio::Producto> buscarPorCodigo(int codigo) const;

private:
    estructuras::ArregloDinamico<dominio::Producto> productos_;
};
}
