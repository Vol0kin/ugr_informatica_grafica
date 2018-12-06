#include "textura.h"

using namespace cimg_library;

void ObjTextura::initTexels() {
	std::vector<unsigned char> texels;

	CImg<unsigned char> imagen;
	imagen.load(nombreImagen.c_str());

	// Se procesa la imagen para obtener sus datos
	for (long x = 0; x < imagen.height(); x++) {
		for (long y = 0; y < imagen.width(); y++) {
			unsigned char *r = imagen.data(x, y, 0, 0);
			unsigned char *g = imagen.data(x, y, 0, 1);
			unsigned char *b = imagen.data(x, y, 0, 2);
			texels.push_back(*r);
			texels.push_back(*g);
			texels.push_back(*b);
		}
	}

	glGenTextures(1, &idTextura);
	glBindTexture(GL_TEXTURE_2D, idTextura);

	// Interpolacion y repetir coordenadas en caso de pasarse
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Transferencia de los datos a la GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, texels.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

ObjTextura::ObjTextura(std::string nomImg) {
	nombreImagen = nomImg;

	vertices = {	{-0.5, -0.5, -0.5},	// 0
					{0.5, -0.5, -0.5},	// 1
					{-0.5, 0.5, -0.5},	// 2
					{0.5, 0.5, -0.5},	// 3
					{-0.5, -0.5, 0.5},	// 4
					{0.5, -0.5, 0.5},	// 5
					{-0.5, 0.5, 0.5},	// 6
					{0.5, 0.5, 0.5},	// 7
					{-0.5, 0.5, -0.5},	// 8 -> 2
					{0.5, 0.5, -0.5},	// 9 -> 3
					{-0.5, -0.5, -0.5}, // 10 -> 0
					{0.5, -0.5, -0.5},	// 11 -> 1
					{-0.5, 0.5, -0.5},	// 12 -> 2
					{-0.5, -0.5, -0.5}, // 13 -> 0
			   };

	triangulos = {	{2, 0, 4},
			 		{2, 4, 6},
			 		{6, 4, 5},
			 		{6, 5, 7},
			 		{8, 6, 7},
			 		{8, 7, 9},
			 		{4, 10, 11},
			 		{4, 11, 5},
			 		{7, 5, 1},
			 		{7, 1, 3},
			 		{3, 1, 13},
			 		{3, 13, 12},
				};

	// (s, t) : s -> height, t -> width
	coordTextura = {	{0.5, 0.0},		// 0
						{0.5, 0.75},	// 1
						{0.25, 0.0},	// 2
						{0.25, 0.75},	// 3
						{0.5, 0.25},	// 4
						{0.5, 0.5},		// 5
						{0.25, 0.25},	// 6
						{0.25, 0.5},	// 7
						{0.0, 0.25},	// 8
						{0.0, 0.5},		// 9
						{0.75, 0.25},	// 10
						{0.75, 0.5},	// 11
						{0.25, 1.0},	// 12
						{0.5, 1.0},		// 13
			 		};
}

void ObjTextura::draw() {
	// Se ignoran colores  y se aplica directamente el texel
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, idTextura);

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glTexCoordPointer(2, GL_FLOAT, 0, coordTextura.data());

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, triangulos.data());

    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}