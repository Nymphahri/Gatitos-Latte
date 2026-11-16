#include "MenuCatalogo.h"

#include <limits>
#include <ostream>
#include <stdexcept>

namespace gatitos::presentacion
{
MenuCatalogo::MenuCatalogo(aplicacion::ServicioProductos& servicio, std::istream& entrada,
                         std::ostream& salida) noexcept
    : servicio_(servicio), entrada_(entrada, salida), salida_(salida) {}

void MenuCatalogo::ejecutar()
{
    salida_ << "GATITOS & LATTE\nCatalogo de productos\n"
               "Los datos se conservan solo durante esta ejecucion.\n";
    try {
        for (;;) {
            salida_ << "\n1. Registrar producto\n2. Listar productos\n"
                       "3. Buscar por codigo (secuencial)\n4. Ordenar productos\n5. Buscar por codigo (binaria)\n6. Buscar en el arbol\n7. Mostrar arbol en inorden\n0. Salir\n";
            const int opcion = entrada_.leerEntero("Seleccione una opcion: ", 0, 7);
            if (opcion == 0) { salida_ << "Hasta luego.\n"; return; }
            try {
                switch (opcion) {
                case 1: registrar(); break;
                case 2: listar(); break;
                case 3: buscar(); break;
                case 4: ordenar(); break;
                case 5: buscar(true); break;
                case 6: buscarEnArbol(); break;
                case 7: mostrarInorden(); break;
                }
            } catch (const std::invalid_argument& error) {
                salida_ << error.what() << '\n';
            }
        }
    } catch (const FinEntrada&) {
        salida_ << "\nEntrada cerrada. No se guardan registros incompletos.\n";
    }
}

void MenuCatalogo::registrar()
{
    const int codigo = entrada_.leerEntero("Codigo: ", 1, (std::numeric_limits<int>::max)());
    const auto nombre = entrada_.leerTexto("Nombre: ");
    const auto categoria = entrada_.leerTexto("Categoria: ");
    const auto precio = entrada_.leerPrecio("Precio en colones (ejemplo 1800.50): ");
    const bool disponible = entrada_.leerEntero("Disponible (1 = si, 0 = no): ", 0, 1) == 1;
    servicio_.registrar(codigo, nombre, categoria, precio, disponible);
    salida_ << "Producto registrado correctamente.\n";
}

void MenuCatalogo::mostrar(const dominio::Producto& producto) const
{
    const auto precio = producto.precioCentimos();
    const auto fraccion = precio % 100;
    salida_ << "\nCodigo: " << producto.codigo()
            << "\nNombre: " << producto.nombre()
            << "\nCategoria: " << producto.categoria()
            << "\nPrecio: CRC " << precio / 100 << '.'
            << (fraccion < 10 ? "0" : "") << fraccion
            << "\nDisponible: " << (producto.disponible() ? "Si" : "No") << '\n';
}

void MenuCatalogo::listar() const
{
    if (servicio_.cantidad() == 0) { salida_ << "No hay productos registrados.\n"; return; }
    for (std::size_t i = 0; i < servicio_.cantidad(); ++i) { mostrar(servicio_.productoEn(i)); }
}

void MenuCatalogo::buscar(bool binaria)
{
    const int codigo = entrada_.leerEntero("Codigo a buscar: ", 1, (std::numeric_limits<int>::max)());
    if (binaria) { salida_ << "Busqueda binaria: el catalogo se ordena por codigo si es necesario.\n"; }
    const auto producto = binaria ? servicio_.buscarBinaria(codigo) : servicio_.buscarPorCodigo(codigo);
    if (producto) { mostrar(*producto); }
    else { salida_ << "No se encontro un producto con ese codigo.\n"; }
}
void MenuCatalogo::ordenar()
{
    salida_ << "1. Codigo\n2. Nombre\n3. Precio\n";
    const int opcion = entrada_.leerEntero("Criterio: ", 1, 3);
    algoritmos::CriterioOrden criterio = algoritmos::CriterioOrden::Codigo;
    if (opcion == 2) { criterio = algoritmos::CriterioOrden::Nombre; }
    else if (opcion == 3) { criterio = algoritmos::CriterioOrden::Precio; }
    servicio_.ordenar(criterio);
    salida_ << "Catalogo ordenado de menor a mayor.\n";
    listar();
}
void MenuCatalogo::buscarEnArbol()
{
    const int codigo = entrada_.leerEntero("Codigo a buscar en el arbol: ", 1, (std::numeric_limits<int>::max)());
    const auto producto = servicio_.buscarEnArbol(codigo);
    if (producto) { mostrar(*producto); }
    else { salida_ << "No se encontro un producto con ese codigo.\n"; }
}

void MenuCatalogo::mostrarInorden() const
{
    salida_ << "Recorrido inorden: izquierda, raiz, derecha.\n";
    const auto recorrido = servicio_.productosInorden();
    if (recorrido.vacio()) { salida_ << "No hay productos registrados.\n"; return; }
    for (std::size_t i = 0; i < recorrido.tamano(); ++i) { mostrar(recorrido.en(i)); }
}
}
