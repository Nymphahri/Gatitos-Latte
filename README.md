# Gatitos & Latte

Sistema de gestión de pedidos de una cafetería desarrollado en C++ para el curso
ISB-08 Organización de Archivos y Estructuras de Datos, de la Universidad
Internacional San Isidro Labrador.

## Estado actual

Implementados: registro, listado y búsqueda secuencial de productos mediante un
menú de consola. El catálogo utiliza Producto y un arreglo dinámico propio, con
validaciones y pruebas automatizadas. Ordenamiento, búsqueda binaria, árbol y
gestión de pedidos siguen pendientes.
Los nombres de los integrantes se incorporarán antes de la entrega.

## Objetivo

Administrar productos y pedidos aplicando estructuras de datos implementadas
manualmente, algoritmos de búsqueda y ordenamiento y separación de responsabilidades.

## Requisitos técnicos

- Windows con Visual Studio 2026 y la carga de trabajo Desarrollo para el escritorio con C++.
- Herramientas MSVC v145 y Windows SDK 10 o posterior compatible.
- Estándar C++20. No se requieren bibliotecas externas.

## Clonar y ejecutar

```powershell
git clone https://github.com/Nymphahri/Gatitos-Latte.git
cd Gatitos-Latte
```

1. Abrir `Gatitos&Latte/Gatitos&Latte.slnx` en Visual Studio.
2. Seleccionar `Debug` y plataforma `x64`.
3. Compilar la solución con `Ctrl+Shift+B`.
4. Ejecutar sin depuración con `Ctrl+F5`.

La consola permite registrar, listar y buscar productos por código. Los datos se pierden al salir.

Para verificar las clases implementadas, ejecutar desde PowerShell:

    ./tests/Ejecutar-Pruebas.ps1
    ./tests/Ejecutar-Pruebas.ps1 -Configuracion Release

Detalles técnicos: [Producto y arreglo dinámico](docs/productos-y-arreglo.md) y [uso del catálogo](docs/catalogo.md).

## Organización

| Carpeta | Responsabilidad |
|---|---|
| `Gatitos&Latte/src/Presentacion` | Menús, entrada de datos y mensajes de consola. |
| `Gatitos&Latte/src/Aplicacion` | Coordinación de los casos de uso. |
| `Gatitos&Latte/src/Dominio` | Entidades y reglas del negocio. |
| `Gatitos&Latte/src/Datos` | Almacenamiento y consultas en memoria. |
| `Gatitos&Latte/src/Estructuras` | Arreglo dinámico, lista, pila, cola y árbol manuales. |
| `Gatitos&Latte/src/Algoritmos` | Búsquedas y ordenamiento propios. |
| `tests` | Pruebas de entidades, estructuras, catálogo y consola. |
| `docs` | Diseño y documentación técnica. |

`Gatitos&Latte/Gatitos&Latte.cpp` es el punto de entrada. Las carpetas reservadas se documentan con
archivos README hasta incorporar sus primeras clases.

## Restricciones del curso

Los productos se almacenarán en un arreglo dinámico; los pedidos pendientes, en
una cola FIFO; los procesados, en una lista enlazada; el historial, en una pila
LIFO; y la organización de productos utilizará un árbol binario de búsqueda.
Estas estructuras se implementarán desde cero, sin `std::vector`, `std::list`,
`std::stack`, `std::queue` ni contenedores equivalentes que las sustituyan.
Se implementará un algoritmo de ordenamiento y al menos dos de búsqueda.
La información permanecerá en memoria durante la ejecución.

## Forma de trabajo

Cada avance incorpora una responsabilidad concreta, su verificación y la
actualización de la documentación. Los commits describen cambios realmente
implementados. Los archivos de compilación y ajustes personales del IDE no se suben.

## Apoyo de IA

Se utilizó Codex como apoyo para la configuración, implementación de Producto, arreglo dinámico, catálogo y consola, pruebas y
documentación. Las revisiones, modificaciones y validaciones realizadas por los
integrantes se documentarán durante el desarrollo para la entrega académica.
