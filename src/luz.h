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
		Tupla4f luz_ambiente = {0.0, 0.0, 0.0, 1.0},
				luz_especular = {1.0, 1.0, 1.0, 1.0},
				luz_difusa = {1.0, 1.0, 1.0, 1.0},
				luz_pos = {0.0, 1.0, 1.0, 1.0},
				luz_dir = {0.0, 0.0, 1.0, 0.0};

	public:
		Luz();
		void activarLuz(int num_luz);
		void desactivarLuz(int num_luz);
};

#endif
