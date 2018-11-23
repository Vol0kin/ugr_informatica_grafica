#include "luz.h"

Luz::Luz() { }

void Luz::activarLuz(int num_luz) {

	switch (num_luz) {
		case 0:
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, luz_dir);
			break;
		case 1:
			glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
			glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);
			glLightfv(GL_LIGHT1, GL_POSITION, luz_pos);
			glEnable(GL_LIGHT1);
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
