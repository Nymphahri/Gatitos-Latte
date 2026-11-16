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
    [[nodiscard]] const dominio::Producto& productoEn(std::size_t indice) const;
    [[nodiscard]] std::optional<dominio::Producto> buscarPorCodigo(int codigo) const;

    void ordenar(algoritmos::CriterioOrden criterio);
    [[nodiscard]] std::optional<dominio::Producto> buscarBinaria(int codigo);

    [[nodiscard]] std::optional<dominio::Producto> buscarEnArbol(int codigo) const;
    [[nodiscard]] estructuras::ArregloProductos productosInorden() const;

private:
    datos::CatalogoProductos& catalogo_;
};
}
