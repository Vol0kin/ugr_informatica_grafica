#include "luz.h"

Luz::Luz() { }

void Luz::activarLuz(int num_luz) {

	switch (num_luz) {
		case 0:
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, luz_dir_l0);
			break;
		case 1:
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente_l1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa_l1);
			glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular_l1);
			glLightfv(GL_LIGHT1, GL_POSITION, luz_pos_l1);
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

void Luz::activarRotarLuzMagenta(float angulo) {
	glPushMatrix();
		glRotatef(angulo, 0.0, 1.0, 0.0);
		activarLuz(1);
	glPopMatrix();
}
