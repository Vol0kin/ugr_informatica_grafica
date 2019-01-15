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

constexpr int num_parametros = 8; // número de parámetros o grados de libertad
                                   // de este modelo

class SubPierna {
	private:
		Esfera * esfera = nullptr;
		Cilindro * cilindro = nullptr;
	public:
		SubPierna();
		void dibujar(const ModoVis p_modo_vis, const bool p_usar_diferido);
};


class Pierna {
	private:
		SubPierna * sb = nullptr;
		Cilindro * cilindro = nullptr;
	public:
		Pierna();
		void dibujar(const ModoVis p_modo_vis, const bool p_usar_diferido, float ang_rot_sb);	
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
	Cubo * cubo	    = nullptr;
	

	// parámetros de la llamada actual (o última) a 'draw'
	ModoVis modo_vis ;      // modo de visualización
	bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)

	// valores efectivos de los parámetros (angulos, distancias, factores de
	// escala, etc.....) calculados a partir de los valores no acotados

	float ag_rotacion_pa,			// Ag. rotacion de la pierna derecha delantera
		  ag_rotacion_pt,			// Ag. rotacion de la pierna derecha trasera
		  ag_rotacion_pd,			// Ag. rotacion de la pierna izquierda delantera
		  ag_rotacion_pi,			// Ag. rotacion de la pierna izquierda trasera
		  ag_rotacion_sb_pa,		// Ag. rotacion de la parte inferior de la pierna derecha delantera
		  ag_rotacion_sb_pt,		// Ag. rotacion de la parte inferior de la pierna derecha trasera
		  ag_rotacion_sb_pd,		// Ag. rotacion de la parte inferior de la pierna izquierda delantera
		  ag_rotacion_sb_pi;
} ;

#endif
