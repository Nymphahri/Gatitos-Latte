#pragma once

#include "../Datos/CatalogoProductos.h"

namespace gatitos::aplicacion
{
class ServicioProductos
{
public:
    explicit ServicioProductos(datos::CatalogoProductos& catalogo) noexcept;
    void registrar(int codigo, std::string nombre, std::string categoria,
                   std::int64_t precioCentimos, bool disponible);
    [[nodiscard]] std::size_t cantidad() const noexcept;
    [[nodiscard]] const entidades::Producto& productoEn(std::size_t indice) const;
    [[nodiscard]] std::optional<entidades::Producto> buscarPorCodigo(int codigo) const;

    void ordenar(algoritmos::CriterioOrden criterio);
    [[nodiscard]] std::optional<entidades::Producto> buscarBinaria(int codigo);

    [[nodiscard]] std::optional<entidades::Producto> buscarEnArbol(int codigo) const;
    [[nodiscard]] estructuras::ArregloProductos productosInorden() const;

private:
    datos::CatalogoProductos& catalogo_;
};
}
