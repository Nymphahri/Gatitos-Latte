# Registro y consulta de productos

## Uso del programa

Abrir `Gatitos&Latte/Gatitos&Latte.slnx` en Visual Studio. Establecer Gatitos&Latte
como proyecto de inicio y ejecutar con Ctrl+F5. El menú ofrece:

1. Registrar producto: solicita código, nombre, categoría, precio y disponibilidad.
2. Listar productos: muestra los registros en orden de ingreso.
3. Buscar por código: muestra un producto o informa que no existe.
0. Salir: termina la ejecución. La información no se conserva entre sesiones.

Los códigos son enteros positivos únicos. Nombre y categoría no pueden quedar
vacíos. El precio es positivo, admite punto o coma decimal y hasta dos decimales,
sin separadores de miles. Por ejemplo, `1800`, `1800.50` y `1800,50`.
La disponibilidad acepta 1 para sí y 0 para no; ambos tipos de productos aparecen
en las consultas.

La entrada se lee por líneas para evitar que un dato incorrecto deje la consola
bloqueada. Un formato incorrecto vuelve a solicitar el campo. Si un código ya está
registrado, se informa el error y se regresa al menú sin sobrescribirlo. Cerrar la
entrada durante un registro no crea productos incompletos.

## Responsabilidades

- `CatalogoProductos` posee el arreglo dinámico, controla códigos duplicados y
  ejecuta la búsqueda secuencial por código.
- `ServicioProductos` construye un Producto válido antes de solicitar su registro
  y expone los casos de uso a la presentación.
- `EntradaConsola` lee y valida el formato de los campos. Convierte el precio a
  céntimos sin usar números de coma flotante y comprueba desbordamientos.
- `MenuCatalogo` presenta opciones y resultados y coordina la interacción.
- `main` construye y conecta esos objetos, y controla errores que impiden continuar.

La búsqueda devuelve una copia opcional del producto. `std::optional` representa
la presencia o ausencia de un resultado; no almacena ni sustituye el catálogo.
El listado consulta referencias constantes que se usan inmediatamente, sin
conservarlas mientras se modifica el arreglo.

## Algoritmo implementado

La búsqueda secuencial recorre los productos desde la primera posición hasta
encontrar el código solicitado o alcanzar el tamaño del arreglo. Su costo es O(n).
El registro también usa esa búsqueda para impedir duplicados. El listado es O(n).

Todavía faltan el ordenamiento, un segundo algoritmo de búsqueda, el BST, los
pedidos, la cola, la lista enlazada y la pila de operaciones.

## Comprobación manual

Registrar código 7, nombre Latte, categoría Café, precio 1800,50 y disponibilidad 1.
Listarlo y buscarlo por código: debe mostrarse como CRC 1800.50. Intentar registrar
nuevamente el código 7: debe rechazarse sin cambiar el primer producto. Buscar 99:
debe indicar que no existe. Introducir texto en una opción numérica: debe solicitar
una opción válida. Salir con 0 y ejecutar nuevamente: el catálogo debe estar vacío.

Las pruebas automatizadas cubren estos recorridos, los límites de los precios,
el crecimiento del catálogo y la interrupción de cada paso de registro.
