// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -- declaracion de la clase luz para la practica 4
//
// #############################################################################

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz {
	private:
		Tupla4f luz_direccional_0 = {0.5, -0.5, -0.5, 0.0},
				color_ambiente_0 = {0.2, 0.2, 0.2, 1.0},
				color_difuso_0 = {0.0, 0.0, 1.0, 1.0},
				color_especular_0 = {0.0, 0.0, 1.0, 1.0};
		Tupla4f luz_posicional_1 = {11.0, 11.0, 11.0, 1.0},
				color_ambiente_1 = {0.2, 0.2, 0.2, 1.0},
				color_difuso_1 = {0.4, 0.3, 0.1, 1.0},
				color_especular_1 = {0.4, 0.3, 0.1, 1.0};
		Tupla4f dir_blanca = {0.0, 0.0, 1.0, 0.0},
				ambiente = {0.2, 0.2, 0.2, 1.0},
				difuso = {1.0, 1.0, 1.0, 1.0},
				especular = {1.0, 1.0, 1.0, 1.0};

	public:
		Luz();
		void activarLuz(int num_luz);
		void desactivarLuz(int num_luz);
		void activarLuzBlanca();
		void activarTrasladarLuz(float z);
};

#endif
