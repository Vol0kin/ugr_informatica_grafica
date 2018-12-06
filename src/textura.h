// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -- declaracion de la clase textura para la practica 4
//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"
#include "CImg.h"

class ObjTextura {
	protected:
		std::vector<Tupla3f> vertices;
		std::vector<Tupla2f> coordTextura;
		std::vector<Tupla3i> triangulos;
		std::string nombreImagen;
		GLuint idTextura = 0;

	public:
		ObjTextura(std::string nomImg);
		void draw();
		void initTexels();
};

#endif
