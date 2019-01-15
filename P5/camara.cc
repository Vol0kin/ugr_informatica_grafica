#include "camara.h"

Camara::Camara(bool esOrto)
{
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

	camaraOrto = esOrto;

	Observer_distance = 2.0;

	// si la camara es ortogonal se establece el observador a una mayor distancia
	// para conseguir un mayor zoom
	if (camaraOrto)
		Observer_distance = 20.0;

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
	if (!camaraOrto)
	{
		glTranslatef( 0.0, 0.0, -Observer_distance );
		glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
		glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
	}
}

void Camara::zoomIn()
{
    Observer_distance /= 1.2;

	if (camaraOrto)
		setOrtoProjection();
}

void Camara::zoomOut()
{
    Observer_distance *= 1.2;

	if (camaraOrto)
		setOrtoProjection();
}

void Camara::setProjection(GLdouble left, GLdouble right, GLdouble bottom,
                           GLdouble top, GLdouble near, GLdouble far)
{
    if (camaraOrto)
    {
		// near -> posicion mas cercana al observador
		// far -> posicion mas lejana al observador
		// valores positivos de far y near significa que se esta mirando en el
		// sentido negativo de las Z
		// valores positivos de far y near significan que se esta mirando en el
		// sentido positivo de las z

        glOrtho(Observer_distance * left , Observer_distance * right ,
			    Observer_distance * bottom , Observer_distance * top ,
				near, far);
		ortoProjLeft = left;
		ortoProjRight = right;
		ortoProjBottom = bottom;
		ortoProjTop = top;
		ortoProjNear = near;
		ortoProjFar = far;
    }
    else
    {
        glFrustum(left, right, bottom, top, near, far);
    }
}

bool Camara::esCamaraOrto() const { return camaraOrto; }

void Camara::setOrtoProjection()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(Observer_distance * ortoProjLeft, Observer_distance *ortoProjRight,
			Observer_distance * ortoProjBottom, Observer_distance * ortoProjTop,
			ortoProjNear, ortoProjFar);
}
