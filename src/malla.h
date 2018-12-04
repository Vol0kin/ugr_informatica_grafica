// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

// Alumno: Vladislav Nikolov Vasilev

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

// Modo de visualizacion
enum ModoVis {
   lineas,
   puntos,
   relleno,
   ajedrez,
   luz_suave,
   luz_plana
};

enum Material {
	azul,
	oro,
	perla,
	ruby
};

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   // segun el valor de modo (0 - inmediato, 1 - diferido)
   void draw(ModoVis modo_visualiz, bool modo_diferido) ;

   // funcion que permite crear un VBO
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // funcion de dibujado que permite dibujar figuras 3D en modo ajedrez
   // (alternando entre 2 colores)
   // inicio especifica la posicion del triangulo inicial (0 o 1), el cual
   // determina si se dibujan los triangulos pares o impares
   void dibujar_modo_ajedrez();


   // metodo que permite dibujar un objeto cuando la luz esta activa
   // dibuja el objeto con sombreado de Gouraud
   void dibujar_luz_suave();

   // metodo que permite dibujar un objeto cuando la luz esta activa
   // dibuja el objeto con sombreado plano
   void dibujar_luz_plana();

   // permite crear un material dados los colores del material y el brillo
   void crear_material();

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   GLuint id_vbo_ver = 0,            // identificador del VBO de vertices
          id_vbo_tri = 0;            // identificador del VBO de triangulos

   // completar: tabla de colores, tabla de normales de vértices
   std::vector<Tupla3f> normalesCaras,		// Normales a las caras
   						normalesVertices;	// Normales a los vertices

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
	Tupla4f colorAmbienteRuby ={ 0.1745f, 0.01175f, 0.01175f, 0.55f },
			colorDifusoRuby ={0.61424f, 0.04136f, 0.04136f, 0.55f },
			colorEspecularRuby ={0.727811f, 0.626959f, 0.626959f, 0.55f };
	float brilloRuby = 76.8;

	Material material;
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo() ;

} ;

// *****************************************************************************
// Tetraedro

class Tetraedro : public ObjMallaIndexada {
   public:
      Tetraedro();
};

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      // Constructor sin parametros para ser llamado por las clases hijas
      ObjRevolucion() {}
      ObjRevolucion( const std::string & nombre_ply_perfil );

   protected:
      void crear(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf,
                 bool tapa_sur = true, bool tapa_norte = true);
} ;

// *****************************************************************************
// Clase cilindro
// Representa un cilindro de radio 1 y altura 1, cuya base esta sobre el origen

class Cilindro : public ObjRevolucion {
   public:
      Cilindro(const int num_vert_perfil, const int num_instancias_perf);
};

// *****************************************************************************
// Clase Cono
// Representa un cono de radio 1 y altura 1, cuya base esta sobre el origen

class Cono : public ObjRevolucion {
   public:
      Cono(const int num_vert_perfil, const int num_instancias_perf);
};

// *****************************************************************************
// Clase Esfera
// Representa una esfera de radio 1 centrada en el origen

class Esfera : public ObjRevolucion {
	public:
		Esfera(const int num_vert_perfil, const int num_instancias_perf);

	protected:
		void calcular_normales();
};

#endif
