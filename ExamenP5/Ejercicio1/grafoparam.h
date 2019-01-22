// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 12; // número de parámetros o grados de libertad
                                   // de este modelo

class Cabeza {
private:
	Cubo * cubo = nullptr;
	Cilindro * cilindro = nullptr;
	Esfera * esfera = nullptr;
public:
	Cabeza();
	void draw(const ModoVis p_modo_vis, const bool p_usar_diferido, float ang_rot_cabeza);
	void dibujarCabeza(const ModoVis p_modo_vis, const bool p_usar_diferido);
	void dibujarOjo(const ModoVis p_modo_vis, const bool p_usar_diferido);
};

class Pierna {
private:
	Cubo *         cubo = nullptr;
	Cilindro * cilindro = nullptr;
	Esfera *     esfera = nullptr;
public:
 	Pierna();
	void draw(const ModoVis p_modo_vis, const bool p_usar_diferido, float ang_pie_inf);
	void dibujarPiernaInferior(const ModoVis p_modo_vis, const bool p_usar_diferido);
};

class GrafoParam
{
public:

	// crea mallas indexadas (nodos terminales del grafo)
	GrafoParam();

	// función principal de visualización
	void draw( const ModoVis p_modo_vis, const bool p_usar_diferido );

	// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
	void actualizarValorEfe( const unsigned iparam, const float valor_na );

	// devuelve el número de parámetros
	unsigned numParametros() { return num_parametros ; }

private:

	// objetos tipo malla indexada (nodos terminales)

	Pierna * pierna = nullptr;
	Cabeza * cabeza = nullptr;
	Cubo * cubo	    = nullptr;
	Esfera * esfera = nullptr;

	// parámetros de la llamada actual (o última) a 'draw'
	ModoVis modo_vis ;      // modo de visualización
	bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)

	// valores efectivos de los parámetros (angulos, distancias, factores de
	// escala, etc.....) calculados a partir de los valores no acotados

	float ag_rotacion_pdd,			// Ag. rotacion de la pierna derecha delantera
		  ag_rotacion_pda,			// Ag. rotacion de la pierna derecha trasera
		  ag_rotacion_pid,			// Ag. rotacion de la pierna izquierda delantera
		  ag_rotacion_pia,			// Ag. rotacion de la pierna izquierda trasera
		  ag_rotacion_pie_pdd,		// Ag. rotacion de la parte inferior de la pierna derecha delantera
		  ag_rotacion_pie_pda,		// Ag. rotacion de la parte inferior de la pierna derecha trasera
		  ag_rotacion_pie_pid,		// Ag. rotacion de la parte inferior de la pierna izquierda delantera
		  ag_rotacion_pie_pia,		// Ag. rotacion de la parte inferior de la pierna izquierda trasera
		  ag_rotacion_cuello,		// Ag. rotacion del cuello
		  ag_rotacion_cabeza,		// Ag. rotacion de la cabeza
		  posicion,					// Posicion del perro en el eje Z (traslacion)
		  ag_rotacion_cola;			// Ag. de rotacion de la cola
} ;

#endif
