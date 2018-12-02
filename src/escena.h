#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"

// Alumno: Vladislav Nikolov Vasilev

class Escena
{

   private:

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   // Cambio de animaciones
   void conmutarAnimaciones();

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 , // número de objetos (actualizado al crear los objetos en el constructor)
       modo_actual   = 0 ; // representa el modo de dibujo actual (0 - lineas, 1 - puntos, 2 - relleno, 3 - ajedrez)

   bool modo_diferido         = false,      // representa uso del modo diferido
        animaciones_activas   = false,      // representa el uso de animaciones
        obj_actual_jerarquico = false,      // representa si el objeto actual es el objJer
		luz_activa			  = false;


   const int num_modos     = 6, // representa las opciones de dibujo
             num_dibujados = 2, // representa los modos de dibujo disponibles
             num_objJer    = 7; // representa el numero asignado al objJer

   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr;
   ObjPLY * ply = nullptr;
   ObjRevolucion * objRevol = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   ObjJerarquico * objJer = nullptr;
   Luz * luz = nullptr;

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
   void mgeDesocupado();

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
