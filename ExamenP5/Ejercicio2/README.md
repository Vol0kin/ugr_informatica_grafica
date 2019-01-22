# Práctica 5

Se ha pedido implementar:

+ Movimiento de la camara con el ratón.
+ Una camara nueva (en perspectiva u ortogonal).
+ La capacidad de seleccionar distintas partes de un objeto.

## Desarrollo

+ Se ha implementado la clase Camara (Camara.h y Camara.cpp) que contiene el codigo necesario para la gestion de las 2 camaras.
+ Se ha implementado la rotacion de la cámara utilizando el boton derecho del raton.
+ Se ha implementado el zoom con la rueda del raton (hacia arriba acerca la camara y hacia abajo la aleja).
+ Se ha implementado una camara ortogonal y se ha permitido hacer zoom en esta camara.
+ Se ha implementado un nuevo objeto llamado Estrella compuesto por objetos Piramide, del cuál se puede seleccionar cada piramide.
+ Se han implementado las teclas necesarias para poder conmutar entre las camaras.

## Objetos

| Numero | Objeto |
| ------ | ------ |
| 0 | Cubo |
| 1 | Tetraedro |
| 2 | Objeto PLY |
| 3 | Peon |
| 4 | Cilindro |
| 5 | Cono |
| 6 | Esfera |
| 7 | Objeto jerarquico |
| 8 | Skybox |
| 9 | Cuadro |
| 10 | Textura repetida |
| 11 | Estrella (objeto seleccion) |

## Modos de dibujo

Los modos de dibujo no estan disponibles para los objetos:

+ 8
+ 9
+ 10
+ 11

Estos objetos tienen un modo de dibujo fijo y al modificarlo con la tecla correspondiente no sucede nada.

| Numero | Modo |
| ------ | ---- |
| 0 | Lineas |
| 1 | Puntos |
| 2 | Relleno |
| 3 | Ajedrez |
| 4 | Material con iluminacion suave |
| 5 | Material con iluminacion plana |

## Teclas utilizadas

| Tecla | Accion |
| ----- | ------ |
| q | Salir |
| o | Cambiar de objeto |
| m | Cambiar de modo |
| v | Usar modo diferido (solo disponible en objetos 0 - 7) |
| e | Cambiar el material utilizado con iluminacion |
| r | Rotar luz magenta alrededor del objeto cuando la iluminacion esta activada |
| a | Activar animaciones (solo cuando se esta en el objeto jerarquico |
| z | Decrementar parametro actual (solo en objeto jerarquico) |
| Z | Incrementar parametro actual (solo en objeto jerarquico) | 
| < | Desacelerar la velocidad con la que cambia un parametro del objeto jerarquico |
| > | Incrementar velocidad con la que cambia un parametro del objeto jerarquico |
| p | Cambiar parametro que se va a modificar del objeto jerarquico |
| c | Cambiar entre las camaras (perspectiva y ortogonal) |
| Raton Derecho | Rotar camara |
| Raton Izquierdo | Seleccionar elemento (solo en el objeto Estrella) |
| Rueda central arriba | Acercar camara |
| Rueda central abajo | Alejar camara |
