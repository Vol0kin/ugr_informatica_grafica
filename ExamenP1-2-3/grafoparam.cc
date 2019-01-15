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
   pierna = new Pierna();
   cubo   = new Cubo();
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

	switch(iparam) {
		case 0: //20-90
			// ag. de rotacion de la pierna derecha delantera
			// oscila entre -30 y 30 grados
			// inicialmente es 0 grados
			ag_rotacion_pa = -35.0 + 55.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 1:
			// ag. de rotacion de la pierna derecha trasera
			// oscila entre -30 y 30 grados
			// inicialmente es 0 grados
			// invertido respecto a la pierna delantera de ese lado
			ag_rotacion_pt = -35.0 + 55.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 2:
			// ag. de rotacion de la pierna izquierda delantera
			// oscila entre -30 y 30 grados
			// inicialmente es 0 grados
			ag_rotacion_pd = -35.0 + 55.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 3:
			// ag. de rotacion de la pierna izquierda trasera
			// oscila entre -30 y 30 grados
			// inicialmente es 0 grados
			// invertido respecto a la pierna delantera de ese lado
			ag_rotacion_pi = -35.0 + 55.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 4: //20 - 160
			// ag. de rotacion de la parte inferior de la pierna derecha delantera
			// oscila entre 0 y 60 grados
			// inicialmente es 30 grados
			ag_rotacion_sb_pa = 70.0 + 90.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 5:
			// ag. de rotacion de la parte inferior de la pierna derecha trasera
			// oscila entre 0 y 60 grados
			// inicialmente es 30 grados
			// invertido respecto a la pierna delantera de ese lado
			ag_rotacion_sb_pt = 70.0 + 90.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 6:
			// ag. de rotacion de la parte inferior de la pierna izquierda delantera
			// oscila entre 0 y 60 grados
			// inicialmente es 30 grados
			ag_rotacion_sb_pd = 70.0 + 90.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 7:
			// ag. de rotacion de la parte inferior de la pierna izquierda trasera
			// oscila entre 0 y 60 grados
			// inicialmente es 30 grados
			// invertido respecto a la pierna delantera de ese lado
			ag_rotacion_sb_pi = 70.0 + 90.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
	}
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
	// asegurarnos que está inicializado ok
	assert(cubo   != nullptr);

	// guardar parametros de visualización para esta llamada a 'draw'
	// (modo de visualización, modo de envío)

	modo_vis      = p_modo_vis ;
	usar_diferido = p_usar_diferido ;

	// dibujar objetos

	glPushMatrix();
		glPushMatrix();
			glScalef(2.0, 2.0, 2.0);
			glTranslatef(0.0, 0.5, 0.0);
			cubo->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(ag_rotacion_pd, 0.0, 0.0, 1.0);
			glRotatef(45.0, 0.0, 0.0, 1.0);
			pierna->dibujar(modo_vis, usar_diferido, ag_rotacion_sb_pd);
		glPopMatrix();

		glRotatef(90.0, 0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(ag_rotacion_pa, 0.0, 0.0, 1.0);		
			glRotatef(45.0, 0.0, 0.0, 1.0);
			pierna->dibujar(modo_vis, usar_diferido, ag_rotacion_sb_pa);
		glPopMatrix();

		glRotatef(90.0, 0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(ag_rotacion_pi, 0.0, 0.0, 1.0);			
			glRotatef(45.0, 0.0, 0.0, 1.0);
			pierna->dibujar(modo_vis, usar_diferido, ag_rotacion_sb_pi);
		glPopMatrix();

		glRotatef(90.0, 0.0, 1.0, 0.0);
		glPushMatrix();
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef(ag_rotacion_pt, 0.0, 0.0, 1.0);			
			glRotatef(45.0, 0.0, 0.0, 1.0);
			pierna->dibujar(modo_vis, usar_diferido, ag_rotacion_sb_pt);
		glPopMatrix();
	glPopMatrix();
}

//******************************************************************************
// PIERNA

Pierna::Pierna() {
	sb = new SubPierna();
	cilindro = new Cilindro(20, 16);
}

void Pierna::dibujar(const ModoVis p_modo_vis, const bool p_usar_diferido, float ang_rot_sb) {
	glPushMatrix();
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glPushMatrix();
			glScalef(0.45, 2.0, 0.45);
			glTranslatef(0.0, -1.0, 0.0);
			cilindro->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -2.0, 0.0);
			glRotatef(-ang_rot_sb, 0.0, 0.0, 1.0);			
			sb->dibujar(p_modo_vis, p_usar_diferido);
		glPopMatrix();
	glPopMatrix();
}


//******************************************************************************
// SUBPIERNA

SubPierna::SubPierna() {
	esfera = new Esfera(20, 16);
	cilindro = new Cilindro(20, 16);
}

void SubPierna::dibujar(const ModoVis p_modo_vis, const bool p_usar_diferido) {
	glPushMatrix();
		glPushMatrix();
			glScalef(0.45, 0.45, 0.45);
			esfera->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glScalef(0.45, 2.0, 0.45);
			glTranslatef(0.0, -1.0, 0.0);
			cilindro->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -2.0, 0.0);
			glScalef(0.45, 0.45, 0.45);
			esfera->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();
	glPopMatrix();
}
