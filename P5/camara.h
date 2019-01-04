#ifndef _CAMARA_H
#define _CAMARA_H

#include "aux.h"

class Camara
{
    private:
        GLfloat Observer_distance,
                Observer_angle_x,
                Observer_angle_y;
    public:
        Camara();
        void girar(GLfloat x, GLfloat y);
        void girarFlechaX(GLfloat direccion);
        void girarFlechaY(GLfloat direccion);
        void setObservador();
        void zoomIn();
        void zoomOut();
};

#endif
