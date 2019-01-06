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
    public:
        Camara(bool esOrto = false);
        void girar(GLfloat x, GLfloat y);
        void setObservador();
        void zoomIn();
        void zoomOut();

        // metodo para establecer la proyeccion de la camara
        // puede establecer una vista en perspectiva o una
        // vista ortogonal
        void setProjection(GLdouble left, GLdouble right, GLdouble bottom,
                           GLdouble top, GLdouble near, GLdouble far) const;

        bool esCamaraOrto() const;
};

#endif
