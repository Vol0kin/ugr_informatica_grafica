#include "camara.h"

Camara::Camara(bool esOrto)
{
    Observer_distance = 2.0;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

    camaraOrto = esOrto;
}

void Camara::girar(GLfloat x, GLfloat y)
{
    if (!camaraOrto)
    {
        Observer_angle_x += x;
        Observer_angle_y += y;
    }
}

void Camara::setObservador()
{
    glTranslatef( 0.0, 0.0, -Observer_distance );
    glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
    glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

void Camara::zoomIn()
{
    Observer_distance /= 1.2;
}

void Camara::zoomOut()
{
    Observer_distance *= 1.2;
}

void Camara::setProjection(GLdouble left, GLdouble right, GLdouble bottom,
                           GLdouble top, GLdouble near, GLdouble far) const
{
    if (camaraOrto)
    {
        glOrtho(left * Observer_distance, right * Observer_distance,
                bottom * Observer_distance, top * Observer_distance,
                near, far);
    }
    else
    {
        glFrustum(left, right, bottom, top, near, far);
    }
}

bool Camara::esCamaraOrto() const { return camaraOrto; }
