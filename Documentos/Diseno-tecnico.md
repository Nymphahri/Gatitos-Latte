# Diseño técnico de Gatitos & Latte

## Alcance actual

La aplicación permite registrar, listar, ordenar y consultar productos en una
consola. También registra pedidos y mantiene una cola FIFO de pendientes.
Permite atender el siguiente pedido y conservarlo como Entregado en una lista
enlazada. Una pila conserva el historial de registros y entregas. Los datos
permanecen en memoria durante la ejecución.

## Arquitectura

Presentacion llama a Aplicacion. Aplicacion utiliza Dominio y Datos. Datos utiliza
Estructuras y Algoritmos. Las estructuras y entidades no imprimen ni leen entradas.

| Componente | Responsabilidad |
|---|---|
| Producto | Código, nombre, categoría, precio y disponibilidad; valida sus datos. |
| ArregloProductos | Arreglo dinámico de punteros, crecimiento, copia y liberación. |
| ArbolProductos | Índice por código, búsqueda y recorrido inorden. |
| AlgoritmosProductos | Ordenamiento por inserción y búsqueda binaria. |
| CatalogoProductos | Almacena productos, impide duplicados y prepara las búsquedas. |
| ServicioProductos | Construye productos válidos y coordina los casos de uso. |
| EntradaConsola | Valida formatos y convierte precios a céntimos. |
| MenuCatalogo | Presenta opciones y resultados del catálogo. |
| Pedido | Guarda cliente, producto, cantidad, precio de venta, total y estado. |
| ColaPedidos | Mantiene los pendientes mediante nodos enlazados FIFO. |
| ListaPedidos | Guarda procesados en nodos enlazados, con búsqueda y eliminación. |
| OperacionPedido | Identifica el número del pedido y el tipo de operación realizada. |
| PilaOperaciones | Conserva las operaciones más recientes en la cima mediante nodos propios. |
| RegistroPedidos | Asigna números y mantiene cola, lista e historial coherentes. |
| ServicioPedidos | Coordina registro, atención y consultas de pedidos. |
| MenuPedidos | Registro, atención y consultas de pendientes y procesados. |
| MenuPrincipal | Navega entre los módulos sin perder sus datos. |

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

## Menú del catálogo y validaciones

1. Registrar producto.
2. Listar productos en el orden actual.
3. Buscar por código mediante búsqueda secuencial.
4. Ordenar productos y mostrar el resultado.
5. Buscar por código mediante búsqueda binaria.
6. Buscar por código en el árbol.
7. Mostrar los productos mediante recorrido inorden.
0. Volver al menú principal.

El precio admite punto o coma y hasta dos decimales, sin separadores de miles.
Los campos incorrectos se solicitan nuevamente. Los códigos duplicados no
sobrescriben datos. Cerrar la entrada durante un registro no crea un producto
parcial. Los productos no disponibles también aparecen en las consultas.

## Árbol binario de productos

Cada nodo contiene un puntero constante a un producto y dos enlaces: izquierdo
y derecho. Los códigos menores se insertan a la izquierda y los mayores a la
derecha. No se permiten códigos repetidos ni se utilizan bibliotecas de árboles.

El arreglo continúa siendo el almacenamiento principal y dueño de los productos.
El árbol posee únicamente sus nodos. Las direcciones de los productos permanecen
estables al ampliar u ordenar el arreglo, porque estas operaciones reorganizan
punteros, no mueven los objetos. El catálogo no permite modificar sus códigos.

Al registrar se agrega primero el producto al arreglo y después su referencia al
árbol. Si falla la creación del nodo, se retira el último producto agregado para
que ambas estructuras conserven el mismo contenido. Antes de insertar se comprueba
el código en el árbol. Esta comprobación no sustituye las búsquedas secuencial y
binaria, que permanecen disponibles en el menú.

El árbol se destruye antes que el arreglo y libera solamente sus nodos. No admite
copia, para evitar compartir nodos accidentalmente. Tampoco admite insertar objetos
temporales: los productos referenciados deben seguir vivos mientras exista el árbol.
El catálogo no ofrece eliminación de productos; cualquier incorporación futura de
esa función deberá retirar primero el nodo correspondiente.

La inserción usa recursividad. El recorrido inorden visita izquierda, raíz y
derecha y produce los productos en orden ascendente de código, sin cambiar el
orden actual del arreglo. Devuelve un arreglo independiente para la presentación.
La liberación visita los hijos antes de eliminar cada nodo.

La búsqueda es iterativa. Inserción y búsqueda cuestan O(h), donde h es la altura:
O(log n) en un árbol equilibrado y O(n) cuando queda como una cadena. Este BST no
se balancea automáticamente. El recorrido cuesta O(n), más O(n) para la copia de
resultados, y las operaciones recursivas ocupan O(h) de pila de llamadas. Una cadena
muy profunda puede agotar esa pila; no es una estructura diseñada para volúmenes
arbitrariamente grandes.

## Pedidos y cola FIFO

Cada Pedido contiene un número positivo, cliente, copia del producto solicitado,
cantidad positiva, precio unitario en céntimos, total y estado Pendiente. Se admite
un producto por pedido, con la cantidad solicitada. Los productos inexistentes o
no disponibles se rechazan. El producto se consulta mediante el árbol del catálogo.

El total se calcula multiplicando precio por cantidad. Antes de multiplicar se
comprueba el límite del entero de 64 bits, para evitar desbordamientos. La copia
del producto conserva el precio al momento del registro, independientemente de
cambios posteriores en el catálogo.

RegistroPedidos asigna números consecutivos desde 1 durante cada ejecución. El
contador avanza solamente después de agregar el pedido a la cola. Un registro
rechazado no consume un número. El contador está limitado al rango de los números
de pedido de tipo int y comprueba su agotamiento antes de asignar otro.

ColaPedidos utiliza nodos propios con un Pedido y un puntero siguiente. Frente
apunta al primero y final al último. Encolar agrega al final; desencolar elimina
el frente. Ambas operaciones cuestan O(1), suponiendo costo constante por copia
de Pedido. Al retirar el último nodo, ambos punteros quedan en nullptr. La cola
libera sus nodos al destruirse y realiza copias independientes.

Ver el siguiente pedido no lo retira. Listar pendientes crea una copia de la cola
y la recorre en orden de llegada: la cola original no cambia. Esta consulta cuesta
O(n) de tiempo y memoria adicional. Buscar por número recorre la cola y, si no encuentra el pedido, la lista de procesados; cuesta O(p + e), con p pendientes y e entregados.

El menú principal ofrece Productos, Pedidos y Salir. El menú de Pedidos ofrece
registrar, listar pendientes, ver el siguiente, buscar por número, atender el siguiente, listar procesados, ver historial y volver. Los
objetos de datos viven durante toda la ejecución, por lo que navegar entre menús
no elimina información. Un cierre de entrada no guarda pedidos parciales.

## Atención y lista enlazada de procesados

La opción Atender siguiente toma exclusivamente el frente de la cola FIFO. Se
copia el pedido, se marca Entregado y se agrega al final de ListaPedidos. Solo
después de guardar esa copia se desencola el original. Si falla la copia o la
reserva del nodo, el pedido continúa pendiente. Una cola vacía no produce cambios.
La operación devuelve el número atendido, o 0 cuando no hay pendientes.

ListaPedidos es una lista simplemente enlazada: cada nodo posee un Pedido y un
puntero al siguiente. Primero y último identifican sus extremos; agregar al final
conserva el orden de atención y cuesta O(1). Buscar y eliminar por número cuestan
O(n). Eliminar ajusta los enlaces y los extremos antes de liberar el nodo. La
estructura implementa eliminación, pero el menú aún no permite borrar procesados.

La lista libera todos sus nodos iterativamente. Su constructor de copia y su
asignación crean nodos independientes. La asignación prepara una copia antes de
reemplazar el contenido para conservarlo si la reserva de memoria falla.

Ver procesados recorre una copia, eliminando su primer nodo tras mostrarlo. Esta
consulta cuesta O(n) de tiempo y memoria adicional y no modifica la lista original.
Los costos suponen tamaño constante de los datos de cada Pedido; copiar sus cadenas
también depende de su longitud. Los datos de venta y el total no cambian al entregar.

El registro solo acepta nuevos pedidos Pendientes. La búsqueda por número incluye
ambas estructuras, mientras que siguiente consulta únicamente la cola. Los números
no se reinician al vaciarla. No existe todavía un estado Cancelado ni una opción
para revertir una entrega. El historial permite consultar las acciones realizadas.

## Historial de operaciones mediante pila

OperacionPedido guarda el número positivo del pedido y el tipo de operación:
Registro o Entrega. El historial conserva acciones, mientras que la cola y la
lista conservan los pedidos. Consultar productos o pedidos no agrega operaciones.

PilaOperaciones utiliza nodos propios, cada uno con una operación y un puntero al
siguiente. Apilar enlaza un nodo nuevo antes de la cima. Desapilar libera la cima
y avanza al siguiente nodo. Ambas operaciones, consultar la cima y consultar la
cantidad cuestan O(1). No se utiliza std::stack ni otro contenedor prefabricado.

La copia conserva el orden desde la cima hasta el fondo y crea nodos independientes.
La asignación prepara primero una copia temporal. La destrucción libera los nodos
iterativamente. Copiar y destruir la pila cuestan O(n).

RegistroPedidos prepara una entrada de historial antes de agregar el pedido a la
cola o a la lista. Si esa inserción falla, desapila la entrada recién creada y
propaga el error. El número avanza solo después de registrar el pedido; al entregar,
se retira el pendiente solo después de guardar el procesado. Los registros rechazados
y los intentos de atender una cola vacía no generan entradas en el historial.

La opción 7 de Pedidos muestra una copia de la pila y la consume mediante cima y
desapilar. Cuesta O(n) de tiempo y memoria adicional. La pila original permanece
intacta, por lo que la consulta puede repetirse sin perder datos. Desapilar una
entrada de esa copia no deshace una entrega ni elimina un pedido.

Si se registran #1 y #2 y luego se entrega #1, el historial muestra: entrega #1,
registro #2 y registro #1. Esto demuestra LIFO: la última operación entra en la
cima y es la primera en consultarse. El historial cubre registros y entregas de
pedidos; no almacena cambios del catálogo ni fechas, y se pierde al cerrar el programa.

## Pendientes para la entrega

Eliminación de procesados desde el menú y consulta conjunta de todos los pedidos.
Completar el informe con objetivos, requerimientos, capturas reales, conclusiones
y los demás apartados exigidos por el curso.
