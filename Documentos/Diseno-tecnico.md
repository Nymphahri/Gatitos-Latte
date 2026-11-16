# Diseño técnico de Gatitos & Latte

## Alcance actual

La aplicación permite registrar, listar, ordenar y consultar productos en una
consola. Los datos permanecen en memoria durante la ejecución. Los pedidos,
la cola, la lista enlazada, la pila y el árbol están pendientes.

## Arquitectura

Presentacion llama a Aplicacion. Aplicacion utiliza Dominio y Datos. Datos utiliza
Estructuras y Algoritmos. Las estructuras y entidades no imprimen ni leen entradas.

| Componente | Responsabilidad |
|---|---|
| Producto | Código, nombre, categoría, precio y disponibilidad; valida sus datos. |
| ArregloProductos | Arreglo dinámico de punteros, crecimiento, copia y liberación. |
| AlgoritmosProductos | Ordenamiento por inserción y búsqueda binaria. |
| CatalogoProductos | Almacena productos, impide duplicados y prepara las búsquedas. |
| ServicioProductos | Construye productos válidos y coordina los casos de uso. |
| EntradaConsola | Valida formatos y convierte precios a céntimos. |
| MenuCatalogo | Presenta opciones y resultados. |

## Producto e importes

El código debe ser positivo y único en el catálogo. Nombre y categoría deben
contener texto y el precio debe ser mayor que cero. Los importes se guardan como
enteros de 64 bits en céntimos: 180050 representa ₡1800,50. La conversión comprueba
el límite del entero para evitar desbordamientos y no utiliza coma flotante.

## Arreglo dinámico y punteros

ArregloProductos es una clase concreta con declaración en `.h` e implementación
en `.cpp`. No usa plantillas ni contenedores prefabricados.

`Producto** datos_` apunta a un bloque creado con `new Producto*[capacidad]{}`.
Este bloque almacena punteros en posiciones contiguas, no los objetos Producto.
Cada posición ocupada apunta a un producto creado con `new Producto(producto)`.
Las posiciones libres contienen `nullptr`.

Al crecer, se reserva un arreglo de punteros mayor, se copian las direcciones
existentes y se libera el bloque anterior con `delete[]`. Los productos permanecen
en sus propias direcciones. La capacidad se duplica cuando resulta posible; se
comprueba el límite antes de multiplicar.

El arreglo es dueño de los productos. `limpiar()` usa `delete` para cada producto,
coloca los punteros en `nullptr` y reinicia el tamaño. El destructor además usa
`delete[]` para liberar el bloque de punteros. No se debe liberar desde fuera
ningún producto obtenido del arreglo.

La copia es profunda: cada producto se duplica. Se definen destructor, constructor
de copia y asignación para evitar que dos arreglos liberen los mismos objetos.
Si una copia falla, se liberan los objetos parciales. La asignación completa
primero una copia temporal para no perder el destino ante un fallo.

El acceso es O(1). Agregar es O(1) amortizado y O(n) al crecer. La copia y la
destrucción son O(n), suponiendo costo constante por producto. A cambio de un
manejo explícito de punteros, cada producto requiere una reserva individual de
memoria y el arreglo ocupa espacio adicional para las direcciones.

## Ordenamiento por inserción

Se recorre el arreglo desde la segunda posición. Cada elemento se desplaza hacia
la izquierda mediante intercambios de punteros hasta quedar en su lugar dentro de
la parte ya ordenada. No se utiliza `std::sort`.

Los criterios son código, nombre y precio, en orden ascendente. Los empates de
nombre o precio se resuelven por código. La comparación de nombres usa el orden
de `std::string`: distingue mayúsculas y minúsculas y no aplica reglas lingüísticas
especiales para tildes. No debe presentarse como ordenación alfabética española.

El costo es O(n²) en el peor caso, O(n) si ya está ordenado y O(1) de espacio
auxiliar, considerando comparaciones de costo constante. Comparar nombres también
depende de su longitud.

## Búsquedas

La búsqueda secuencial recorre los productos hasta encontrar el código o llegar
al final; no requiere orden previo y su costo es O(n).

La búsqueda binaria examina el elemento central y descarta la mitad que no puede
contener el código. Usa un límite superior exclusivo para manejar también el
arreglo vacío sin restar a un índice cero. Su costo es O(log n) cuando el arreglo
ya está ordenado por código.

CatalogoProductos mantiene una marca de orden. Registrar un producto o elegir
otro criterio invalida el orden por código. Antes de la búsqueda binaria, el
catálogo ordena por código cuando sea necesario y actualiza la marca. Por tanto,
una consulta que necesita preparar el orden puede costar O(n²); no corresponde
afirmar que toda la operación sea siempre O(log n).

La búsqueda binaria cambia el orden visible del catálogo a código. La consola
lo comunica. El algoritmo devuelve un puntero no propietario y el catálogo
devuelve una copia opcional del resultado. `std::optional` expresa presencia o
ausencia; no sustituye el almacenamiento principal.

## Menú y validaciones

1. Registrar producto.
2. Listar productos en el orden actual.
3. Buscar por código mediante búsqueda secuencial.
4. Ordenar productos y mostrar el resultado.
5. Buscar por código mediante búsqueda binaria.
0. Salir.

El precio admite punto o coma y hasta dos decimales, sin separadores de miles.
Los campos incorrectos se solicitan nuevamente. Los códigos duplicados no
sobrescriben datos. Cerrar la entrada durante un registro no crea un producto
parcial. Los productos no disponibles también aparecen en las consultas.

## Pendientes para la entrega

Árbol binario de búsqueda de productos; registro de pedidos y totales; cola FIFO;
procesamiento y estados; lista enlazada de pedidos procesados; pila del historial.
Completar el informe con objetivos, requerimientos, capturas reales, conclusiones
y los demás apartados exigidos por el curso.
