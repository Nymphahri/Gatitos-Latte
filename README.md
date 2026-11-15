# Gatitos & Latte

Sistema de gestión de pedidos de una cafetería desarrollado en C++ para el curso
ISB-08 Organización de Archivos y Estructuras de Datos de la Universidad
Internacional San Isidro Labrador.

## Objetivo

Administrar productos y pedidos mediante estructuras de datos implementadas
manualmente, con separación por capas y responsabilidades.

## Funciones disponibles

- Registro de productos con código, nombre, categoría, precio y disponibilidad.
- Validación de códigos duplicados y datos de entrada.
- Listado del catálogo y búsqueda secuencial por código.
- Almacenamiento en memoria mediante un arreglo dinámico propio.

Pendientes: ordenamiento, búsqueda binaria, árbol de productos, registro y atención
de pedidos, cola, lista enlazada e historial mediante pila.

## Requisitos

- Visual Studio 2026 con Desarrollo para el escritorio con C++.
- Herramientas MSVC v145 y Windows SDK compatible.
- C++20. No requiere bibliotecas externas ni base de datos.

## Clonar y ejecutar

```powershell
git clone https://github.com/Nymphahri/Gatitos-Latte.git
cd Gatitos-Latte
```

1. Abrir `Gatitos&Latte/Gatitos&Latte.slnx`.
2. Seleccionar Debug y plataforma x64.
3. Compilar con Ctrl+Shift+B.
4. Ejecutar con Ctrl+F5.

El precio se introduce en colones, con hasta dos decimales y sin separadores de
miles; por ejemplo, `1800.50`. Los datos se pierden al cerrar el programa.

## Organización

| Carpeta | Responsabilidad |
|---|---|
| `Gatitos&Latte/src/Presentacion` | Menú y lectura de datos. |
| `Gatitos&Latte/src/Aplicacion` | Casos de uso del catálogo. |
| `Gatitos&Latte/src/Dominio` | Entidades y validaciones del negocio. |
| `Gatitos&Latte/src/Datos` | Almacenamiento y consultas. |
| `Gatitos&Latte/src/Estructuras` | Estructuras de datos manuales. |
| `Documentos` | Documentación técnica del sistema. |

El archivo `Gatitos&Latte.cpp` construye y conecta los componentes.
Consultar [el diseño técnico](Documentos/Diseno-tecnico.md) para conocer las
responsabilidades y el funcionamiento del catálogo.

## Integrantes

Pendiente de completar antes de la entrega.
