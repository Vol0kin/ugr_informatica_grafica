// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 4, 16 );
   cubo     = new Cubo();
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         // altura 1: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         altura_1= 1.0 + 0.3*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 1:
         // altura 2: oscila entre 1.1 y 1.9, a 0.8 oscilaciones por segundo
         altura_2 = 1.5 + 0.4*sin( 0.8*(2.0*M_PI*valor_na) );
         break ;
      case 2:
         // angulo en grados de rotacion 1 (cubo rojoaa)
         // crece linealmente a 150 grados por segundo, inicialmente es 20 grados
         ag_rotacion_1 = 20.0 + 150.0*valor_na ;
         break ;
      case 3:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         ag_rotacion_2 = -7.5 + 37.5*sin( 1.5*(2.0*M_PI*valor_na) );
         break ;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos

   constexpr float
      sep       = 1.5,  // separación entre centros de las columnas
      radio_cil = 0.5 , // radio del cilindro más fino
      radio_cil2 = radio_cil+0.1 ; // radio del cilindro más grueso

   glPushMatrix();
      // primera columna
      glColor3f( 0.6, 0.2, 0.0 );
      columna( altura_1, ag_rotacion_1, radio_cil );
      // segunda columna
      glPushMatrix();
         glTranslatef( sep, 0.0, 0.0 );
         glColor3f( 0.0, 0.2, 0.6 );
         columna( altura_2, ag_rotacion_2, radio_cil2 );
      glPopMatrix();
      // base
      glColor3f( 0.1, 0.6, 0.1 );
      glTranslatef( -radio_cil2, -0.1*radio_cil2, -radio_cil2 );
      glScalef( sep+2.0*radio_cil2, 0.1*radio_cil2, 2.0*radio_cil2 );
      glTranslatef( 0.5, 0.5, 0.5 );
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es una columna (cilindro) de altura = 'altura', con un cubo encima,
// rotado entorno a Y un ángulo en grados = 'ag_rotacion'

void GrafoParam::columna( const float altura, const float ag_rotacion,
                          const float radio_cil )
{


   glPushMatrix();
      glScalef( radio_cil, altura, radio_cil );
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
   glPushMatrix( );
      glTranslatef( 0.0, 0.5+altura, 0.0 );
      glRotatef( ag_rotacion, 0.0, 1.0, 0.0 );
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();
}
