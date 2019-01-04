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
        void setObservador();
        void zoomIn();
        void zoomOut();
};

#endif
