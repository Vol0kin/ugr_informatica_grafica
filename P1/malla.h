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
   void draw(int modo, bool ajedrez = false, int inicio = 0) ;

   // funcion que permite crear un VBO
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // funcion de dibujado que permite dibujar figuras 3D en modo ajedrez
   // (alternando entre 2 colores)
   // inicio especifica la posicion del triangulo inicial (0 o 1), el cual
   // determina si se dibujan los triangulos pares o impares
   void dibujar_modo_ajedrez(int inicio);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
   GLuint id_vbo_ver = 0,            // identificador del VBO de vertices
          id_vbo_tri = 0;            // identificador del VBO de triangulos

   // completar: tabla de colores, tabla de normales de vértices
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
      ObjRevolucion( const std::string & nombre_ply_perfil );

   protected:
      void crear(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf);
} ;

#endif
