#pragma once

#include "../Dominio/Producto.h"
#include "../Estructuras/ArregloProductos.h"
#include "../Algoritmos/AlgoritmosProductos.h"
#include <optional>
#include "../Estructuras/ArbolProductos.h"

namespace gatitos::datos
{
class CatalogoProductos
{
public:
    void agregar(const dominio::Producto& producto);
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] const dominio::Producto& en(std::size_t indice) const;
    [[nodiscard]] std::optional<dominio::Producto> buscarPorCodigo(int codigo) const;
    [[nodiscard]] std::optional<dominio::Producto> buscarBinaria(int codigo);
    void ordenar(algoritmos::CriterioOrden criterio);

    [[nodiscard]] std::optional<dominio::Producto> buscarEnArbol(int codigo) const;
    [[nodiscard]] estructuras::ArregloProductos productosInorden() const;

private:
    estructuras::ArregloProductos productos_;
    // Se destruye antes que productos_: sus nodos no poseen los productos.
    estructuras::ArbolProductos arbol_;
    bool ordenadoPorCodigo_ = true;
};
}
