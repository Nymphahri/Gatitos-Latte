#pragma once

#include "../Estructuras/ArregloProductos.h"

namespace gatitos::algoritmos
{
enum class CriterioOrden { Codigo, Nombre, Precio };

void ordenarPorInsercion(estructuras::ArregloProductos& productos, CriterioOrden criterio);

// Precondicion: el arreglo debe estar ordenado por codigo ascendente.
// El resultado pertenece al arreglo; no debe liberarse ni conservarse tras limpiar.
[[nodiscard]] const dominio::Producto* buscarBinariaPorCodigo(
    const estructuras::ArregloProductos& productos, int codigo);
}
