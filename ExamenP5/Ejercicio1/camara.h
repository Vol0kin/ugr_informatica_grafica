#ifndef _CAMARA_H
#define _CAMARA_H

#include "aux.h"

class Camara
{
    private:
        GLfloat Observer_distance,
                Observer_angle_x,
                Observer_angle_y;
        bool camaraOrto;

		// variables para la camara ortogonal
		GLdouble ortoProjLeft = 0.0,
				 ortoProjRight = 0.0,
				 ortoProjBottom = 0.0,
				 ortoProjTop = 0.0,
				 ortoProjNear = 0.0,
				 ortoProjFar = 0.0;

		// metodo para cambiar la proyeccion ortogonal al hacer zoom
		void setOrtoProjection();
    public:
        Camara(bool esOrto = false);
        void girar(GLfloat x, GLfloat y);
        void setObservador(bool lookAt);
        void zoomIn();
        void zoomOut();

        // metodo para establecer la proyeccion de la camara
        // puede establecer una vista en perspectiva o una
        // vista ortogonal
        void setProjection(GLdouble left, GLdouble right, GLdouble bottom,
                           GLdouble top, GLdouble near, GLdouble far);

        bool esCamaraOrto() const;
};

#endif
