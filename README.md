### Enunciados

## Ejercicio de Grafos:

Dado un grafo no orientado que modela las rutas de la provincia de Buenos Aires, devolver todos los caminos alternativos que se pueden tomar para ir desde la ciudad de Buenos Aires a la ciudad de Tandil, considerando que en el tramo Las Flores-Rauch está cortado al tránsito.

## Ejercicio de Backtracking:

Una facultad presenta una carrera nueva, que tiene una lista de materias que deben ser cursadas en el mismo cuatrimestre, cada materia tiene una lista de comisiones posibles a cursar (solo debe elegirse una de todas ellas). Cada materia puede tener varias comisiones y cada comisión tiene asociado el horario de inicio y fin.

Implementar un algoritmo de backtracking que devuelva un listado con todas las combinaciones posibles que permitan asistir a una comisión de cada materia sin que se solapen los horarios. Considerar realizar una función son_compatibles(comision_1, comision_2) que dados dos comisiones devuelve un valor booleano que indica si se pueden cursar al mismo tiempo.

a) Realizar el Árbol de exploración: estado inicial, criterio de ramificación y profundidad del árbol (No se debe entregar)

b) Una solución para el problema en c++ usando la técnica de programación backtracking. 

c) Plantear e implementar una poda posible al algoritmo implementado en el punto b).

d) Hacer una estimación del orden de complejidad del algoritmo (Agregarla como comentario de la función Backtraking)

## Ejercio de Aproximación:

Una empresa de logística tiene que enviar N paquetes de una ciudad a otra. Cada paquete ocupa un volumen Vi, con i que va desde 1 mts3, hasta 100 mts3.
La empresa cuenta con varios camiones de 100mts3 de capacidad pero desea MINIMIZAR la cantidad de camiones que deben viajar.

Considerando solo el volumen de los paquetes SIN considerar su forma, escribir un algoritmo de aproximación en tiempo polinomial en C++ para determinar cuántos camiones deben viajar y cómo se deben distribuir los paquetes en cada camión.
