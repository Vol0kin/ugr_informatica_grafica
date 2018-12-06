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
		Tupla4f luz_ambiente_l1 = {0.2, 0.2, 0.2, 1.0},
				luz_especular_l1 = {1.0, 0.0, 1.0, 1.0},
				luz_difusa_l1 = {1.0, 0.0, 1.0, 1.0},
				luz_pos_l1 = {0.0, 10.0, 10.0, 1.0},
				luz_dir_l0 = {0.0, 0.0, 1.0, 0.0};

	public:
		Luz();
		void activarLuz(int num_luz);
		void desactivarLuz(int num_luz);
		void activarRotarLuzMagenta(float angulo);
};

#endif
