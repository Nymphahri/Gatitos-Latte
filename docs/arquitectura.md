# Arquitectura inicial

La aplicación será un programa de consola en C++20 organizado por capas dentro
de un único proyecto. Esta base implementa únicamente el punto de entrada.

## Dependencias

Presentacion utiliza Aplicacion. Aplicacion coordina Dominio y Datos. Datos utiliza
Dominio, Estructuras y Algoritmos. Dominio no depende de capas externas.
Estructuras y Algoritmos no dependen de la interfaz ni de los casos de uso.
El punto de entrada compondrá los objetos necesarios al iniciar el programa.

## Criterios de implementación

- Separar declaraciones `.h` e implementaciones `.cpp` cuando se incorporen clases.
- Evitar estado global mutable y `using namespace std` en encabezados.
- Validar el formato en Presentacion y las reglas del negocio en Dominio o Aplicacion.
- Identificar productos y pedidos por códigos estables, evitando índices o punteros
  que queden inválidos al ordenar o redimensionar el arreglo.
- Cada propietario de memoria libera sus recursos y define su política de copia.
- Mantener el precio de venta del pedido aunque el catálogo cambie posteriormente.
- Usar cantidades monetarias enteras en unidades mínimas al implementar los importes.
- Mantener las responsabilidades explícitas sin agregar interfaces ni patrones
  que no resuelvan una necesidad concreta del proyecto.

## Próximos incrementos

1. Modelo de producto, arreglo dinámico y registro y consulta del catálogo.
2. Búsquedas y ordenamiento; índice de productos mediante BST.
3. Modelo de pedido, cálculo del total y cola de pendientes.
4. Atención de pedidos, lista de procesados e historial mediante pila.
5. Consultas integradas, validaciones, pruebas e informe con capturas reales.

Cada incremento debe compilar y verificarse antes de continuar. La documentación
final distinguirá lo implementado de las mejoras futuras.

