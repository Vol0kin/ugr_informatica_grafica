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
       modo_actual   = 0 , // representa el modo de dibujo actual (0 - lineas, 1 - puntos, 2 - relleno, 3 - ajedrez)
	   material_actual = 0; // representa el material actual

   bool modo_diferido         = false,      // representa uso del modo diferido
        animaciones_activas   = false,      // representa el uso de animaciones
        obj_actual_jerarquico = false,      // representa si el objeto actual es el objJer
		luz_activa			  = false;


   const int NUM_MODOS      = 6,	// representa las opciones de dibujo
             NUM_OBJJER     = 7, 	// representa el numero asignado al objJer
			 NUM_MATERIALES = 4,	// representa el numero de materiales
			 INCR_ANG_LUZ   = 15;	// representa el incremento del angulo de rotacion de la luz

   int angulo_rotacion_luz = 0;	// Representa el angulo de rotacion de la luz

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

   // Materiales
   // Material azul
   Tupla4f colorAmbienteDifusoAzul = {0.4, 0.8, 1.0, 1.0},
		   colorEspecularAzul = {1.0, 1.0, 1.0, 1.0};
   float brilloAzul = 100.0;

   // Material oro
   Tupla4f colorAmbienteOro = {0.24725, 0.1995, 0.0745, 1.0},
		   colorDifusoOro = {0.75164, 0.60648, 0.22648, 1.0},
		   colorEspecularOro = {0.628281, 0.555802, 0.366065, 1.0};
   float brilloOro = 51.2;

   // Material jade
   Tupla4f colorAmbientePerla = {0.25, 0.20725, 0.20725, 0.922},
		   colorDifusoPerla = {1.0, 0.829, 0.829, 0.922},
		   colorEspecularPerla = {0.296648, 0.296648, 0.296648, 0.922};
   float brilloPerla =  11.264;

   //Ruby
   Tupla4f colorAmbienteRuby = {0.1745, 0.01175, 0.01175, 0.55},
		   colorDifusoRuby = {0.61424, 0.04136, 0.04136, 0.55},
		   colorEspecularRuby = {0.727811, 0.626959, 0.626959, 0.55};
   float brilloRuby = 76.8;

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
