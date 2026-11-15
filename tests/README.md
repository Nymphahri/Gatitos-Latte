# Pruebas

El proyecto `GatitosLatte.Pruebas.vcxproj` forma parte de la solución y ejecuta
pruebas de Producto, ArregloDinamico, catálogo y consola, sin bibliotecas externas.
No utiliza `assert`, por lo que las comprobaciones también funcionan en Release.

Desde PowerShell, en la raíz del repositorio:

```powershell
./tests/Ejecutar-Pruebas.ps1
./tests/Ejecutar-Pruebas.ps1 -Configuracion Release
```

También se puede seleccionar GatitosLatte.Pruebas como proyecto de inicio en
Visual Studio y ejecutar con Ctrl+F5. Para volver al programa, seleccionar
Gatitos&Latte como proyecto de inicio.

Resultado esperado: trece casos con `OK` y `Fallos: 0`. Un fallo devuelve un
código de salida distinto de cero. Las pruebas cubren entradas inválidas,
conservación del precio, índices incorrectos, crecimiento, referencias al propio
arreglo durante una inserción, copia profunda, movimiento, limpieza y liberación
de objetos cuando una copia lanza una excepción.

El tipo Registro existe únicamente en las pruebas: cuenta sus instancias vivas
y permite interrumpir una copia para verificar la limpieza de objetos parciales.

PruebasCatalogo.cpp cubre registro, duplicados, búsqueda, precios exactos,
recorridos del menú, recuperación ante datos inválidos y cierre de entrada.
