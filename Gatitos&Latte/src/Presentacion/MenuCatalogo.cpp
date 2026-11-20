#include "MenuCatalogo.h"
#include "UI/EstiloConsola.h"

#include <limits>
#include <ostream>
#include <stdexcept>

namespace gatitos::presentacion
{
MenuCatalogo::MenuCatalogo(
    aplicacion::ServicioProductos& servicio,
    std::istream& entrada,
    std::ostream& salida) noexcept: servicio_(servicio),
    entrada_(entrada, salida),
    salida_(salida) {}

void MenuCatalogo::ejecutar()
{
    try {
        for (;;)
        {
            ui::EstiloConsola::mostrarMenuProductos(salida_);
            const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 5);

            if (opcion == 0)
            {
                return;
            }

            try
            {
                switch (opcion)
                {
                case 1: registrar(); entrada_.esperarEnter(); break;
                case 2: listar(); entrada_.esperarEnter(); break;
                case 3: consultarBusqueda(); break;
                case 4: ordenar(); break;
                case 5: consultarArbol(); break;
                }

            } catch (const std::invalid_argument& error)
            {
                salida_ << "\n  No se pudo completar la operación: " << error.what() << '\n';
                entrada_.esperarEnter();
            }
        }

    } catch (const FinEntrada&)
    {
        salida_ << "\n  Entrada cerrada. No se guardan registros incompletos.\n";
    }
}

void MenuCatalogo::consultarBusqueda()
{
    for (;;)
    {
        ui::EstiloConsola::mostrarMenuBusqueda(salida_);
        const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 2);

        if (opcion == 0)
        {
            return;
        }

        buscar(opcion == 2);
        entrada_.esperarEnter();
    }
}

void MenuCatalogo::consultarArbol()
{
    for (;;)

    {
        ui::EstiloConsola::mostrarMenuArbol(salida_);
        const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 2);

        if (opcion == 0)
        {
            return;
        }

        if (opcion == 1)
        {
            buscarEnArbol();
        }

        else
        {
            mostrarInorden();
        }

        entrada_.esperarEnter();
    }
}

void MenuCatalogo::registrar()
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Productos > Registrar");
    const int codigo = entrada_.leerEntero("  Código:          ", 1, (std::numeric_limits<int>::max)());
    const auto nombre = entrada_.leerTexto("  Nombre:          ");
    const auto categoria = entrada_.leerTexto("  Categoría:       ");
    const auto precio = entrada_.leerPrecio("  Precio (CRC):    ");
    const bool disponible = entrada_.leerEntero("  Disponible (1 = Sí, 0 = No): ", 0, 1) == 1;
    servicio_.registrar(codigo, nombre, categoria, precio, disponible);
    salida_ << "  Producto registrado correctamente.\n";
}

void MenuCatalogo::listar() const
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Productos > Catálogo");
    ui::EstiloConsola::iniciarTabla(salida_);
    for (std::size_t i = 0; i < servicio_.cantidad(); ++i) {
        ui::EstiloConsola::mostrarFilaProducto(salida_, servicio_.productoEn(i));
    }
    ui::EstiloConsola::terminarTabla(salida_, servicio_.cantidad());
}

void MenuCatalogo::buscar(bool binaria)
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Productos > Consultar");
    const int codigo = entrada_.leerEntero("  Código a buscar: ", 1, (std::numeric_limits<int>::max)());
    if (binaria)
    {
        salida_ << "  Búsqueda binaria: el catálogo se ordena por código si es necesario.\n";
    }
    const auto producto = binaria ? servicio_.buscarBinaria(codigo) : servicio_.buscarPorCodigo(codigo);

    if (producto)
    {
        ui::EstiloConsola::mostrarFicha(salida_, *producto);
    }

    else
    {
        salida_ << "  No se encontró un producto con ese código.\n";
    }
}

void MenuCatalogo::ordenar()
{
    ui::EstiloConsola::mostrarMenuOrden(salida_);
    const int opcion = entrada_.leerEntero("\n  Opción: ", 0, 3);

    if (opcion == 0)
    {
        return;
    }

    algoritmos::CriterioOrden criterio = algoritmos::CriterioOrden::Codigo;

    if (opcion == 2)
    {
        criterio = algoritmos::CriterioOrden::Nombre;
    }

    else if (opcion == 3)
    {
        criterio = algoritmos::CriterioOrden::Precio;
    }

    servicio_.ordenar(criterio);
    listar();
    salida_ << "\n  Orden aplicado: " << (opcion == 1 ? "código" : opcion == 2 ? "nombre" : "precio") << ".\n";
    entrada_.esperarEnter();
}

void MenuCatalogo::buscarEnArbol()
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Productos > Árbol > Consultar");
    const int codigo = entrada_.leerEntero("  Código a buscar: ", 1, (std::numeric_limits<int>::max)());
    const auto producto = servicio_.buscarEnArbol(codigo);

    if (producto)
    {
        ui::EstiloConsola::mostrarFicha(salida_, *producto);
    }

    else
    {
        salida_ << "  No se encontró un producto con ese código.\n";
    }
}

void MenuCatalogo::mostrarInorden() const
{
    ui::EstiloConsola::mostrarEncabezado(salida_, "Productos > Árbol > Inorden");
    const auto recorrido = servicio_.productosInorden();
    ui::EstiloConsola::iniciarTabla(salida_);

    for (std::size_t i = 0; i < recorrido.tamano(); ++i)
    {
        ui::EstiloConsola::mostrarFilaProducto(salida_, recorrido.en(i));
    }
    ui::EstiloConsola::terminarTabla(salida_, recorrido.tamano());
    salida_ << "\n  Recorrido inorden: izquierda, raíz, derecha.\n";
}
}
