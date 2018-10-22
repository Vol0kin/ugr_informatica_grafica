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
   cabeza = new Cabeza();
   cubo   = new Cubo();
   esfera = new Esfera(20, 16);
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

	switch(iparam) {
		case 0:
			ag_rotacion_pdd = 30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 1:
			ag_rotacion_pda = -30.0 *  sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 2:
			ag_rotacion_pid = 30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 3:
			ag_rotacion_pia = -30.0 *  sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 4:
			ag_rotacion_pie_pdd = 30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 5:
			ag_rotacion_pie_pda = -30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 6:
			ag_rotacion_pie_pid = 30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 7:
			ag_rotacion_pie_pia = -30.0 * sin(0.7 * (2.0 * M_PI * valor_na));
			break;
		case 8:
			ag_rotacion_cuello = 30.0 * sin(0.3 * (2.0 * M_PI * valor_na));
			break;
		case 9:
			ag_rotacion_cabeza = 35.0 * sin(0.4 * (2.0 * M_PI * valor_na));
			break;
		case 10:
			posicion = 0.0 + 5.0 * sin(0.3 * (2.0 * M_PI * valor_na));
			break;
		case 11:
			ag_rotacion_cola = 60.0 * sin(0.6 * (2.0 * M_PI * valor_na));
			break;
	}
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
	// asegurarnos que está inicializado ok
	assert(pierna != nullptr);
	assert(cabeza != nullptr);
	assert(cubo   != nullptr);
	assert(esfera != nullptr);

	// guardar parametros de visualización para esta llamada a 'draw'
	// (modo de visualización, modo de envío)

	modo_vis      = p_modo_vis ;
	usar_diferido = p_usar_diferido ;

	// dibujar objetos

	glPushMatrix();
		glColor3f(0.957, 0.929, 0.545);
		glTranslatef(0.0, 3.5, posicion);

		//dibujar cuerpo
		glPushMatrix();
			glScalef(6.0, 2.0, 2.0);
			cubo->draw(p_modo_vis, p_usar_diferido);
		glPopMatrix();

		// dibujar la cola
		glPushMatrix();
			glTranslatef(3.0, 1.2, 0.0);
			glRotatef(ag_rotacion_cola, 1.0, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.2, 0.2, 0.2);
				esfera->draw(p_modo_vis, p_usar_diferido);
			glPopMatrix();
			glPushMatrix();
				glRotatef(-45.0, 0.0, 0.0, 1.0);
				glTranslatef(0.0, 1.7, 0.0);
				glScalef(0.4, 3.0, 0.4);
				cubo->draw(p_modo_vis, p_usar_diferido);
			glPopMatrix();
		glPopMatrix();

		// dibujar las patas
		glPushMatrix();
			glTranslatef(-2.5, 0.0, 1.5);
			glPushMatrix();
				glRotatef(ag_rotacion_pdd, 0.0, 0.0, 1.0);
				pierna->draw(p_modo_vis, p_usar_diferido, ag_rotacion_pie_pdd);
			glPopMatrix();
			glTranslatef(5.0, 0.0, 0.0);
			glPushMatrix();
				glRotatef(ag_rotacion_pda, 0.0, 0.0, 1.0);
				pierna->draw(p_modo_vis, p_usar_diferido, ag_rotacion_pie_pda);
			glPopMatrix();
			glTranslatef(0.0, 0.0, -3.0);
			glPushMatrix();
				glRotatef(ag_rotacion_pia, 0.0, 0.0, 1.0);
				pierna->draw(p_modo_vis, p_usar_diferido, ag_rotacion_pie_pia);
			glPopMatrix();
			glTranslatef(-5.0, 0.0, 0.0);
			glPushMatrix();
				glRotatef(ag_rotacion_pid, 0.0, 0.0, 1.0);
				pierna->draw(p_modo_vis, p_usar_diferido, ag_rotacion_pie_pid);
			glPopMatrix();
		glPopMatrix();

		//dibujar cabeza
		glPushMatrix();
			glTranslatef(-3.5, 0.5, 0.0);
			glRotatef(ag_rotacion_cuello + 30.0, 0.0, 0.0, 1.0);
			cabeza->draw(p_modo_vis, p_usar_diferido, ag_rotacion_cabeza);
		glPopMatrix();
	glPopMatrix();
}


//******************************************************************************
// CABEZA

Cabeza::Cabeza() {
	cilindro = new Cilindro(4, 16);
	esfera   = new Esfera(20, 16);
	cubo     = new Cubo();
}

void Cabeza::draw(const ModoVis p_modo_vis, const bool p_usar_diferido , float ang__rot_cabeza) {

	// color para la cabeza (dorado)
	glColor3f(0.957, 0.929, 0.545);

	// dibujar union cuello-cuerpo
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		esfera->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar cuello
	glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glScalef(0.5, 1.0, 0.5);
		cilindro->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 2.0, 0.0);
		glRotatef(ang__rot_cabeza, 0.0, 1.0, 0.0);
		dibujarCabeza(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void Cabeza::dibujarCabeza(const ModoVis p_modo_vis, const bool p_usar_diferido) {


	// dibujar union cabeza-cuello
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		esfera->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar cabeza
	glPushMatrix();
		glTranslatef(-0.5, 0.0, 0.0);
		glScalef(2.0, 1.0, 1.0);
		glTranslatef(-0.5, 0.0, 0.0);
		cubo->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// color para ojos y nariz (negro)
	glColor3f(0.0, 0.0, 0.0);

	// dibujar ojos
	glPushMatrix();

		// dibujar ojo derecho
		glTranslatef(-0.8, 0.7, -0.25);
		dibujarOjo(p_modo_vis, p_usar_diferido);

		// dibujar ojo izquiero
		glTranslatef(0.0, 0.0, 0.5);
		dibujarOjo(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar nariz
	glPushMatrix();
		glTranslatef(-2.5, 0.8, 0.0);
		glScalef(0.3, 0.3, 0.3);
		esfera->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	glColor3f(0.957, 0.929, 0.545);

	// dibujar oreja derecha
	glPushMatrix();
		glTranslatef(-0.6, -0.5, 0.75);
		glScalef(0.2, 2.0, 0.5);
		cubo->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar oreja izquierda
	glPushMatrix();
		glTranslatef(-0.6, -0.5, -0.75);
		glScalef(0.2, 2.0, 0.5);
		cubo->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void Cabeza::dibujarOjo(const ModoVis p_modo_vis, const bool p_usar_diferido) {

	glPushMatrix();
		glScalef(0.2, 0.2, 0.2);
		esfera->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

//******************************************************************************
// PIERNA

Pierna::Pierna() {
	cilindro = new Cilindro(4, 16);
	esfera   = new Esfera(20, 16);
	cubo     = new Cubo();
}

void Pierna::draw(const ModoVis p_modo_vis, const bool p_usar_diferido, float ang_pie_inf) {

	// color para la pierna (dorado)
	glColor3f(0.957, 0.929, 0.545);

	// dibujar union con el cuerpo (centrada en el origen)
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		esfera->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar parte superior de la pierna
	glPushMatrix();
		glTranslatef(0.0, -1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		cilindro->draw(p_modo_vis, p_usar_diferido);
	glPopMatrix();

	// dibujar la parte inferior de la pierna
	glPushMatrix();
		glTranslatef(0.0, -1.5, 0.0);
		// Giro parametrizado
		// se le añade 30 grados para que la rodilla no se pase
		// el limite de movimiento hacia adelante
		glRotatef(ang_pie_inf + 30.0, 0.0, 0.0, 1.0);
		dibujarPiernaInferior(p_modo_vis, p_usar_diferido);
	glPopMatrix();
}

void Pierna::dibujarPiernaInferior(const ModoVis p_modo_vis,
                                   const bool p_usar_diferido) {

    // dibujar la rodilla
    glPushMatrix();
      glScalef(0.5, 0.5, 0.5);
      esfera->draw(p_modo_vis, p_usar_diferido);
   glPopMatrix();

   // dibujar la primera parte de la pierna
   glPushMatrix();
      glTranslatef(0.0, -1.0, 0.0);
      glScalef(0.5, 0.5, 0.5);
      cilindro->draw(p_modo_vis, p_usar_diferido);
   glPopMatrix();

   // dibujar la pata
   // Se tiene que desplazar -1.5 en el eje Y ya que
   // parte del cubo esta 0.5 debajo del plano que forman
   // los ejes X y Z
   glPushMatrix();
      glTranslatef(-0.5, -1.5, 0.0);
      glScalef(2.0, 1.0, 1.0);
      cubo->draw(p_modo_vis, p_usar_diferido);
   glPopMatrix();
}
