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
- Listado del catálogo y búsquedas secuencial y binaria por código.
- Ordenamiento por inserción según código, nombre o precio.
- Almacenamiento en memoria mediante un arreglo dinámico propio.
- Árbol binario por código, con inserción, búsqueda y recorrido inorden.
- Registro de pedidos con número automático y cálculo exacto del total.
- Cola FIFO manual: pendientes, siguiente pedido y consulta por número.
- Atención del siguiente pedido por orden FIFO y cambio a estado Entregado.
- Lista enlazada manual de procesados y búsqueda de pendientes o entregados.
- Historial de registros, entregas y eliminaciones mediante una pila manual LIFO.
- Consulta conjunta de pedidos, agrupados en pendientes y entregados.
- Eliminación de pedidos procesados por número, con confirmación e historial.

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

El menú principal separa Productos y Pedidos. Primero se registra un producto
disponible; después, en Pedidos, se indica cliente, código del producto y cantidad.
Cada pedido contiene un producto con su cantidad. El número se asigna automáticamente.
En Pedidos, la opción 5 entrega el primero de la cola; la opción 6 muestra los
procesados. La opción 4 permite buscar tanto pendientes como entregados.
La opción 7 muestra el historial de operaciones, con la operación más
reciente primero. Consultarlo conserva todas las operaciones guardadas.
La opción 8 muestra todos los pedidos guardados, agrupados por estado. La opción 9
elimina un procesado después de mostrarlo y pedir confirmación. Los pendientes no
se pueden eliminar. El historial conserva la eliminación y el número no se reutiliza.

El precio se introduce en colones, con hasta dos decimales y sin separadores de
miles; por ejemplo, `1800.50`. Los datos se pierden al cerrar el programa.

## Organización

| Carpeta | Responsabilidad |
|---|---|
| `Gatitos&Latte/src/Presentacion` | Menú y lectura de datos. |
| `Gatitos&Latte/src/Aplicacion` | Casos de uso de productos y pedidos. |
| `Gatitos&Latte/src/Dominio` | Entidades y validaciones del negocio. |
| `Gatitos&Latte/src/Datos` | Almacenamiento y consultas. |
| `Gatitos&Latte/src/Estructuras` | Estructuras de datos manuales. |
| `Gatitos&Latte/src/Algoritmos` | Ordenamiento por inserción y búsqueda binaria. |
| `Documentos` | Documentación técnica del sistema. |

El archivo `Gatitos&Latte.cpp` construye y conecta los componentes.
Consultar [el diseño técnico](Documentos/Diseno-tecnico.md) para conocer las
responsabilidades y el funcionamiento del catálogo.

## Integrantes

Pendiente de completar antes de la entrega.
