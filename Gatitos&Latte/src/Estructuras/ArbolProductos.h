#pragma once

#include "ArregloProductos.h"

namespace gatitos::estructuras
{
// Indice no propietario: los productos deben vivir mas tiempo que el arbol.
// El arbol libera sus nodos, pero nunca los productos a los que apunta.
class ArbolProductos
{
public:
    ArbolProductos() noexcept = default;
    ~ArbolProductos();
    ArbolProductos(const ArbolProductos&) = delete;
    ArbolProductos& operator=(const ArbolProductos&) = delete;

    void insertar(const dominio::Producto& producto);
    void insertar(dominio::Producto&&) = delete; // No guardar referencias a temporales.
    [[nodiscard]] const dominio::Producto* buscar(int codigo) const noexcept;
    [[nodiscard]] ArregloProductos inorden() const;

private:
    struct Nodo
    {
        explicit Nodo(const dominio::Producto& dato) : producto(&dato) {}
        const dominio::Producto* producto;
        Nodo* izquierdo = nullptr;
        Nodo* derecho = nullptr;
    };

    static void insertarNodo(Nodo*& nodo, const dominio::Producto& producto);
    static void recorrerInorden(const Nodo* nodo, ArregloProductos& resultado);
    static void liberar(Nodo* nodo) noexcept;
    Nodo* raiz_ = nullptr;
};
}
