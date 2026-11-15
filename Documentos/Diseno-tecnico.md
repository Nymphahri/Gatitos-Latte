# Diseño técnico de Gatitos & Latte

## Alcance actual

La aplicación permite registrar, listar y consultar productos por código en una
consola. Utiliza información en memoria durante la ejecución. Los módulos de
pedidos y los algoritmos restantes se incorporarán en próximos incrementos.

## Arquitectura

Presentacion llama a Aplicacion. Aplicacion utiliza Dominio y Datos. Datos almacena
las entidades mediante Estructuras. Dominio y Estructuras no dependen de la consola.

| Componente | Responsabilidad |
|---|---|
| Producto | Código, nombre, categoría, precio y disponibilidad; valida sus datos. |
| ArregloDinamico | Memoria contigua, capacidad, crecimiento, copia y destrucción. |
| CatalogoProductos | Almacena productos, impide códigos duplicados y realiza consultas. |
| ServicioProductos | Construye productos válidos y coordina el registro. |
| EntradaConsola | Valida formatos y convierte precios a céntimos. |
| MenuCatalogo | Presenta opciones y resultados. |

## Producto e importes

El código debe ser positivo y único en el catálogo. Nombre y categoría deben
contener texto y el precio debe ser mayor que cero. Los importes se guardan como
enteros de 64 bits en céntimos: 180050 representa ₡1800,50. La conversión comprueba
el límite del entero para evitar desbordamientos y no utiliza coma flotante.

## Arreglo dinámico

La estructura administra un bloque contiguo. Cuando se llena, reserva mayor
capacidad, copia los elementos y libera el bloque anterior. La capacidad crece
geométricamente. El acceso es O(1); agregar es O(1) amortizado y O(n) al crecer.

`std::allocator` reserva memoria alineada; `std::construct_at` y `std::destroy_at`
administran la vida de cada objeto. El control del tamaño, crecimiento, acceso y
copia está implementado en el proyecto, sin usar contenedores estándar.

El archivo `.tpp` contiene las definiciones de la plantilla y se incluye desde el
`.h` para que el compilador pueda generar cada tipo de arreglo. La copia es
independiente; el movimiento transfiere el bloque. Al limpiar se destruyen los
elementos y se conserva la capacidad. El destructor libera todos los recursos.

Una reserva fallida conserva los datos originales. Una inserción fallida conserva
el tamaño y los valores, aunque puede haber aumentado la capacidad. Las referencias
a los elementos no deben conservarse cuando el bloque se reemplaza o se destruye.

## Registro y búsqueda

El menú solicita todos los campos antes de registrar. ServicioProductos construye
una entidad válida y CatalogoProductos comprueba que su código no exista antes
de agregarla. Un código duplicado no sobrescribe el registro original.

La búsqueda secuencial recorre los elementos hasta encontrar el código o llegar al
final; su costo es O(n). Devuelve una copia opcional del resultado. `std::optional`
representa presencia o ausencia de un producto y no sustituye el almacenamiento.

## Validaciones de la consola

La entrada se lee por líneas. Los formatos incorrectos vuelven a solicitar el
campo. El precio admite punto o coma y hasta dos decimales, sin separadores de
miles. Cerrar la entrada durante un registro no crea un producto parcial.

## Funcionalidades pendientes

Ordenamiento, segundo algoritmo de búsqueda, árbol binario, pedidos y totales,
cola de pendientes, lista de procesados e historial con pila. El informe final
incluirá objetivos, requerimientos, capturas reales, conclusiones y los demás
apartados exigidos por el curso.
