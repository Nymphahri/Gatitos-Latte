# Producto y arreglo dinámico

## Alcance implementado

Este documento describe las clases base y sus pruebas. El registro mediante menú,
la consulta y el control de códigos duplicados ya están implementados en el
catálogo; consultar catalogo.md. La unicidad corresponde al catálogo, no a la
entidad individual ni al arreglo genérico.

## Producto

`Producto.h` declara la entidad y `Producto.cpp` implementa sus reglas.
El código es un entero positivo; nombre y categoría deben contener texto;
el precio debe ser positivo y se expresa en céntimos mediante `std::int64_t`.
Por ejemplo, 180000 representa ₡1800,00. La disponibilidad comienza en verdadero
salvo que el constructor indique otro valor.

La entidad no imprime ni lee datos. Rechaza entradas inválidas con
`std::invalid_argument`. Cambiar a un precio inválido conserva el precio anterior.
No ofrece un constructor vacío: un producto debe crearse con los datos requeridos.

## ArregloDinamico

La plantilla `ArregloDinamico<T>` almacena objetos en un bloque contiguo cuya
capacidad aumenta geométricamente. La estructura administra explícitamente el
puntero, el tamaño, la capacidad, la construcción, la copia y la destrucción.
No utiliza contenedores estándar.

`std::allocator` proporciona memoria alineada sin construir productos ficticios
para las posiciones libres. `std::construct_at` y `std::destroy_at` comienzan y
terminan la vida de cada objeto. Son herramientas de memoria de C++20; no
implementan el arreglo ni sus operaciones. Esta decisión evita exigir un
constructor por defecto a Producto.

Las declaraciones están en `.h` y las definiciones en `.tpp`, incluido al final
del encabezado. El compilador necesita ver las definiciones para generar el código
de cada tipo usado, por ejemplo `ArregloDinamico<Producto>`.

| Operación | Comportamiento y costo |
|---|---|
| `en(indice)` | Acceso O(1), con comprobación de rango. |
| `agregar(valor)` | Copia al final; O(1) amortizado y O(n) cuando crece. |
| `reservar(capacidad)` | Amplía sin reducir; O(n) al copiar los elementos existentes. |
| Copia | Copia profunda O(n); modificar una copia no altera el original. |
| Movimiento | Transfiere el bloque; el origen queda vacío y reutilizable. |
| `limpiar()` | Destruye los elementos en O(n), conservando la capacidad. |
| Destructor | Destruye los elementos y libera el bloque. |

Los costos suponen costo constante por copia o destrucción de T. La asignación
por movimiento además destruye los elementos que el destino ya tenía.

El tipo T debe admitir copia y su destructor no debe lanzar excepciones.
Si falla una reserva, los elementos originales permanecen intactos. Si falla una
inserción, el tamaño y los valores existentes se conservan; la capacidad puede
haber aumentado si la reserva se completó antes del fallo de la copia final.

Las referencias obtenidas con `en` dejan de ser válidas cuando se reemplaza o
destruye el bloque, o al limpiar sus elementos. El futuro árbol debe identificar
productos por su código, sin conservar punteros al arreglo.

## Verificación

Las pruebas ejercitan las clases sin depender de la consola del programa.
Para ejecutar y repetir las comprobaciones, consultar `tests/README.md`.
