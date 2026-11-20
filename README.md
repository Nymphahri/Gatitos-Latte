# Gatitos & Latte

Sistema de gestión de pedidos de una cafetería desarrollado en **C++20** para el curso **ISB-08 Organización de Archivos y Estructuras de Datos** de la Universidad Internacional San Isidro Labrador.

Permite administrar el catálogo de productos, registrar pedidos y atenderlos por orden de llegada mediante una interfaz de consola. La información se almacena en memoria: **al cerrar el programa se pierden los datos de la sesión**.

## Integrantes

Grace Romero Sanabria.

## Objetivo

Desarrollar un sistema de cafetería que aplique estructuras de datos manuales, algoritmos de búsqueda y ordenamiento, y separación de responsabilidades entre entidades, servicios, almacenamiento e interfaz.

## Funcionalidades

- Registrar productos con código único, nombre, categoría, precio y disponibilidad.
- Mostrar el catálogo en tablas y consultar productos mediante fichas.
- Buscar productos por código mediante búsqueda secuencial, binaria o un árbol binario de búsqueda.
- Ordenar el catálogo por código, nombre o precio mediante inserción.
- Mostrar los productos del árbol mediante recorrido inorden.
- Registrar pedidos con número automático, cliente, producto, cantidad y total calculado.
- Consultar el siguiente pedido y confirmar su atención por orden de llegada.
- Consultar todos los pedidos, pendientes, procesados o un pedido por número.
- Eliminar pedidos procesados con confirmación, conservando su historial.
- Mostrar el historial de registros, entregas y eliminaciones de pedidos, con la operación más reciente primero.

El panel principal muestra las cantidades actuales de productos, pedidos pendientes, pedidos procesados y operaciones del historial.

## Estructuras y algoritmos

| Implementación | Uso en el sistema |
|---|---|
| Arreglo dinámico propio | Almacenamiento principal del catálogo. Contiene punteros a los productos, cuyas direcciones se conservan al ampliar el arreglo. |
| Cola enlazada | Pedidos pendientes; el primero en entrar es el primero en atenderse (FIFO). |
| Lista enlazada | Almacenamiento, consulta y eliminación de pedidos procesados. |
| Pila enlazada | Historial de operaciones de pedidos; la última operación aparece primero (LIFO). |
| Árbol binario de búsqueda | Organización por código, búsqueda y recorrido inorden de productos. |
| Ordenamiento por inserción | Orden del catálogo según el criterio seleccionado. |
| Búsquedas secuencial y binaria | Consulta de productos por código. Antes de la búsqueda binaria se garantiza el orden por código. |

Las estructuras y algoritmos requeridos están implementados manualmente. No se utilizan `std::vector`, `std::list`, `std::stack`, `std::queue` ni funciones estándar de ordenamiento para sustituirlos.

## Requisitos

- Windows.
- Git, para clonar el repositorio.
- Visual Studio 2026 con la carga de trabajo **Desarrollo para el escritorio con C++**.
- Herramientas **MSVC v145** y Windows SDK compatible con el proyecto.
- Compilador con soporte para **C++20**.

No requiere bibliotecas externas ni una base de datos. La consola utiliza UTF-8 y activa los colores cuando la terminal los admite.

## Clonar el repositorio

```powershell
git clone https://github.com/Nymphahri/Gatitos-Latte.git
cd Gatitos-Latte
```

## Compilar y ejecutar

1. Abrir `Gatitos&Latte/Gatitos&Latte.slnx` en Visual Studio.
2. Seleccionar la configuración **Debug** y la plataforma **x64**.
3. Compilar la solución con **Ctrl + Shift + B**.
4. Ejecutar sin depuración con **Ctrl + F5**.

También puede compilarse en **Release | x64**. Si una compilación no puede reemplazar el ejecutable porque sigue abierto, cerrar la ejecución anterior y volver a compilar.

## Uso del sistema

Digite el número de una opción y pulse **Enter**. En los submenús, **0** permite volver. Las pantallas de resultados solicitan Enter para regresar.

### Menú principal

```text
1   Gestión de productos
2   Gestión de pedidos
3   Salir
```

### Gestión de productos

```text
1   Registrar producto
2   Ver catálogo
3   Buscar producto
4   Ordenar catálogo
5   Consultar árbol de productos
0   Volver
```

Buscar producto permite elegir búsqueda secuencial o binaria. Consultar árbol permite buscar por código o mostrar el recorrido inorden.

### Gestión de pedidos

```text
1   Registrar pedido
2   Atender siguiente pedido
3   Consultar pedidos
4   Ver historial
5   Eliminar pedido procesado
0   Volver
```

Consultar pedidos agrupa las opciones de todos, pendientes, procesados y búsqueda por número. Atender siguiente muestra el pedido antes de solicitar confirmación; cancelar conserva su estado y posición en la cola.

### Ejemplo de uso

1. En Productos, registrar un producto con código `101`, nombre `Latte`, categoría `Bebidas`, precio `1800.50` y disponibilidad `1`.
2. En Pedidos, registrar al cliente `Ana`, producto `101` y cantidad `2`. El total será **CRC 3,601.00**.
3. Consultar los pendientes para comprobar que el pedido está en la cola.
4. Elegir Atender siguiente y confirmar. El pedido cambia a **Entregado** y pasa a procesados.
5. Consultar el historial para ver la entrega y el registro del pedido.

Los precios se ingresan en colones, con hasta dos decimales y sin separadores de miles; por ejemplo, `1800.50` o `1800,50`. Internamente se guardan en céntimos enteros.

Cada pedido contiene un producto y su cantidad. Solo se pueden pedir productos disponibles y eliminar pedidos procesados. Eliminar un pedido no borra sus operaciones del historial ni permite reutilizar su número durante la sesión.

## Organización del código

Las carpetas de código están dentro de `Gatitos&Latte/src`.

| Carpeta | Responsabilidad |
|---|---|
| `Entidades` | Productos, pedidos y operaciones; validaciones de sus datos y cálculo del total. |
| `Aplicacion` | Servicios que coordinan las operaciones de productos y pedidos. |
| `Datos` | Almacenamiento en memoria, consultas y consistencia entre las estructuras. |
| `Estructuras` | Arreglo dinámico, cola, lista, pila y árbol; administración de memoria y enlaces. |
| `Algoritmos` | Búsquedas secuencial y binaria y ordenamiento por inserción. |
| `Presentacion` | Navegación de menús, lectura y validación del formato de entrada. |
| `Presentacion/UI` | Encabezados, colores, tablas, fichas y presentación de confirmaciones. |

`Gatitos&Latte/Gatitos&Latte.cpp` contiene el punto de entrada y conecta los componentes. La carpeta `Documentos` contiene documentación técnica; véase el [diseño técnico](Documentos/Diseno-tecnico.md).

## Apoyo de herramientas de IA

Se utilizó OpenAI Codex como apoyo en la implementación y reorganización del código, el diseño de la interfaz, la depuración, las verificaciones locales y la documentación.
