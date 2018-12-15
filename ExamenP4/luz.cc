#include "luz.h"

Luz::Luz() { }

void Luz::activarLuz(int num_luz) {

	switch (num_luz) {
		case 0:
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, color_ambiente_0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, color_difuso_0);
			glLightfv(GL_LIGHT0, GL_SPECULAR, color_especular_0);
			glLightfv(GL_LIGHT0, GL_POSITION, luz_direccional_0);
			break;
		case 1:
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, color_ambiente_1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, color_difuso_1);
			glLightfv(GL_LIGHT1, GL_SPECULAR, color_especular_1);
			glLightfv(GL_LIGHT1, GL_POSITION, luz_posicional_1);
			break;
	}
}

void Luz::desactivarLuz(int num_luz) {

	switch (num_luz) {
		case 0:
			glDisable(GL_LIGHT0);
			break;
		case 1:
			glDisable(GL_LIGHT1);
			break;
	}
}

void Luz::activarLuzBlanca() {
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuso);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular);
	glLightfv(GL_LIGHT0, GL_POSITION, dir_blanca);
}

void Luz::activarTrasladarLuz(float z) {
	glPushMatrix();
		glTranslatef(luz_posicional_1(X), luz_posicional_1(Y), luz_posicional_1(Z) + z);
		activarLuz(1);
	glPopMatrix();

	std::cout << "Posicion luz: " << luz_posicional_1(X) << ' ' << luz_posicional_1(Y) << ' ' << luz_posicional_1(Z) + z << std::endl;
}
