#include "camara.h"

Camara::Camara()
{
    Observer_distance = 2.0;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;
}

void Camara::girar(GLfloat x, GLfloat y)
{
    Observer_angle_x += x;
    Observer_angle_y += y;
}

void Camara::setObservador()
{
    glTranslatef( 0.0, 0.0, -Observer_distance );
    glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
    glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

void Camara::zoomIn()
{
    Observer_distance *= 0.9;
}

void Camara::zoomOut()
{
    Observer_distance *= 1.1;
}
