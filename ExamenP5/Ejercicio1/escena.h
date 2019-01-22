#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"
#include "textura.h"
#include "camara.h"

// Alumno: Vladislav Nikolov Vasilev

enum EstadoRaton
{
    MOVIENDO_CAMARA_FIRSTPERSON,
    ZOOM_IN,
    ZOOM_OUT,
	SELECCIONAR_OBJETO,
    NADA
};

class Escena
{

   private:

   Ejes ejes;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   // Cambio de animaciones
   void conmutarAnimaciones();

   int objeto_actual = 0 ,  // objeto actual (el que se visualiza)
       num_objetos   = 0 ,  // número de objetos (actualizado al crear los objetos en el constructor)
       modo_actual   = 0 ,  // representa el modo de dibujo actual (0 - lineas, 1 - puntos, 2 - relleno, 3 - ajedrez)
	   material_actual = 0, // representa el material actual
       camara_actual = 0,   // representa la camara actual
       num_camaras   = 0;   // representa el numero de camaras

   bool modo_diferido         = false,      // representa uso del modo diferido
        animaciones_activas   = false,      // representa el uso de animaciones
        obj_actual_jerarquico = false,      // representa si el objeto actual es el objJer
		luz_activa			  = false,		// representa si la luz esta activa
		obj_textura			  = false,		// representa si se esta usando un objeto con textura
		obj_estrella		  = false,		// representa si se esta usando el objeto estrella
		camara_perspectiva	  = false;		// camara en persepctiva

   EstadoRaton estadoRaton;         // representa el estado del raton
   GLfloat x_ant, y_ant;
   std::vector<Camara> camaras;
   //Camara camaras;

   const int NUM_MODOS      = 6,	// representa las opciones de dibujo
             NUM_OBJJER     = 7, 	// representa el numero asignado al objJer
			 NUM_SKYBOX	    = 8,	// representa el numero asignado al skybox
			 NUM_CUADRO		= 9,	// representa el numero asignado al cuadro
			 NUM_CHESSBOARD = 10,	// representa el numero asignado al chessboard
			 NUM_ESTRELLA   = 11,	// representa el numero asignado a la estrella
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
   SkyBox * skybox = nullptr;
   Cuadro * cuadro = nullptr;
   ChessBoard * chessboard = nullptr;
   Estrella * estrella = nullptr;

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

   // Material perla
   Tupla4f colorAmbientePerla = {0.25, 0.20725, 0.20725, 0.922},
		   colorDifusoPerla = {1.0, 0.829, 0.829, 0.922},
		   colorEspecularPerla = {0.296648, 0.296648, 0.296648, 0.922};
   float brilloPerla =  11.264;

   // Material ruby
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

    // Metodo que realiza una funcion segun el boton pulsado
    // boton derecho + movimiento           -> rota la camara
    void ratonMovido(int x, int y);

	// establece que se ha pulsado la tecla derecha del raton para mover la camara
    void setRatonMovimiento();

	// establece que se va a hacer zoom para acercar la camara
    void setRatonZoomIn();

	// establece que se va a hacer zoom para alejar la camara
    void setRatonZoomOut();

	// establece que se va a seleccionar con el raton (solo funciona con el
	// objeto estrella)
	void setRatonSeleccion();

	// establece los valors de ant_x y ant_y
	// evita movimientos bruscos de la camara
    void setAntXY(int x, int y);

	// establece que el raton no hace nada (boton distinto al movimiento de rueda,
	// el boton derecho y el boton izquierdo)
	void setRatonNada();

	// obtiene el elemento que se ha seleccionado en funcion de las coordenadas (x,y)
	// de la ventana utilizando el buffer trasero (solo funciona con el objeto estrella)
	void pickColor(int x, int y);

	// permite realizar un zoom, dependiendo de si es para acercar
	// o alejar la camara
    void zoom();
};
#endif
