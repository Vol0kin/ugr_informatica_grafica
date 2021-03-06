

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

// Alumno: Vladislav Nikolov Vasilev

Escena::Escena()
{
    Front_plane = 0.1;
    Back_plane = 2000.0;

    estadoRaton = NADA;

    x_ant = 0.0;
    y_ant = 0.0;
	z_ang = 0.0;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    ply = new ObjPLY("plys/beethoven.ply");
    objRevol = new ObjRevolucion("plys/peon");
    cilindro = new Cilindro(15, 40);
    cono = new Cono(14, 40);
    esfera = new Esfera(18, 40);
    objJer = new ObjJerarquico();
	luz = new Luz();
	skybox = new SkyBox("./img/skybox2.jpg");
	cuadro = new Cuadro("./img/cuadro.jpg");
	chessboard = new ChessBoard("./img/diamond_ore.png");
	estrella = new Estrella();

    num_objetos = 12; // se usa al pulsar la tecla 'O' (rotar objeto actual)

    // creacion de las camaras
    num_camaras = 2;
    camaras.push_back(Camara());
    camaras.push_back(Camara(true));
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );

	std::cout << "Creando texturas..." << std::endl;
	skybox->initTexels();
	cuadro->initTexels();
	chessboard->initTexels();
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo

   glPointSize(5);
   glShadeModel(GL_FLAT);
   glDisable(GL_CULL_FACE);

	// Se comprueba si se usan texturas
	if (!obj_textura && !obj_estrella) {
		switch(modo_actual) {
	       case 0:
	         glColor3f(0.0, 0.0, 0.0);
	         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	         break;
	       case 1:
	         glColor3f(0.0, 0.0, 0.0);
	         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	         break;
	       case 2:
	         glColor3f(0.333, 0.305, 0.305);
	         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	         break;
	       case 3:
	         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	         break;
	 	  case 4:
	 	  case 5:					// Caso en el que las lueces estan activas
	 	  	luz_activa = true;
	 		glEnable(GL_LIGHTING);
	 		glEnable(GL_NORMALIZE);
	 		glEnable(GL_SMOOTH);
	 		luz->activarLuz(0);
	 		luz->activarRotarLuzMagenta((float)angulo_rotacion_luz);
	 		break;
	    }

	    if (luz_activa) {
	 	   switch(material_actual) {
	 		   case 0:
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorAmbienteDifusoAzul);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorEspecularAzul);
	    			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brilloAzul);
	    			break;
	    		case 1:
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbienteOro);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDifusoOro);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorEspecularOro);
	    			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brilloOro);
	    			break;
	    		case 2:
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbientePerla);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDifusoPerla);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorEspecularPerla);
	    			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brilloPerla);
	    			break;
	    		case 3:
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbienteRuby);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDifusoRuby);
	    			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorEspecularRuby);
	    			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brilloRuby);
	    			break;
	 	   }
	    }
	} else {
		// Para pintar la textura, hay que usar GL_FILL
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
      case 0:
         if ( cubo != nullptr ) cubo->draw((ModoVis) modo_actual, modo_diferido);
         break ;
      case 1:
         if (tetraedro != nullptr) tetraedro->draw((ModoVis) modo_actual, modo_diferido);
         break;
      case 2:
          if (ply != nullptr) ply->draw((ModoVis) modo_actual, modo_diferido);
		  break;
      case 3:
          if (objRevol != nullptr) objRevol->draw((ModoVis) modo_actual, modo_diferido);
          break;
      case 4:
          if (cilindro != nullptr) cilindro->draw((ModoVis) modo_actual, modo_diferido);
          break;
      case 5:
          if (cono != nullptr) cono->draw((ModoVis) modo_actual, modo_diferido);
          break;
      case 6:
          if (esfera != nullptr) esfera->draw((ModoVis) modo_actual, modo_diferido);
          break;
      case 7:
	  	  if (objJer != nullptr) objJer->draw((ModoVis) modo_actual, modo_diferido);
          break;
	  case 8:
	  	  if (skybox != nullptr) skybox->draw();
		  break;
	  case 9:
	  	  if (cuadro != nullptr) cuadro->draw();
		  break;
	  case 10:
		  if (chessboard != nullptr) chessboard->draw();
		  break;
	  case 11:
	  	  if ( estrella != nullptr ) estrella->draw();
	  	  break ;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }

	// Desactivar luces despues de dibujar, si estan activas
	if (luz_activa) {
		luz->desactivarLuz(0);
		luz->desactivarLuz(1);
		glDisable(GL_LIGHTING);
		luz_activa = false;
	}
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	ejes.draw();
	dibujar_objeto_actual();

	// si el objeto actual es el objeto estrella, se dibuja
	// el buffer trasero
	if (objeto_actual == NUM_ESTRELLA)
	{
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		change_observer();
		estrella->drawBackBuffer();
		glDrawBuffer(GL_FRONT);
	}
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   switch( toupper(tecla) )
   {
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;

		 // modificar variables booleanas segun el objeto
         if (objeto_actual == NUM_OBJJER)
		 {
            obj_actual_jerarquico = true;
		 }
		 else if (objeto_actual == NUM_SKYBOX ||
			 	  objeto_actual == NUM_CUADRO ||
				  objeto_actual == NUM_CHESSBOARD) {
		 	obj_textura = true;
		 }
		 else if (objeto_actual == NUM_ESTRELLA)
		 {
			 obj_estrella = true;
		 }
		 else
		 {
			 obj_actual_jerarquico = false;
			 obj_textura = false;
			 obj_estrella = false;
		 }

         break ;
      case 'M' :
         z_ang++;
		 cout << "rotacion en Z: " << z_ang << endl;
		 camaras[camara_actual].girar(0.0, 0.0, z_ang);
         break;
      case 'V' :
        modo_diferido = !modo_diferido;

        cout << "modo de dibujado actual == ";

        if (!modo_diferido)
          cout << "inmediato" << endl;
        else
          cout << "diferido" << endl;
        break;
	  case 'R' :
	  	angulo_rotacion_luz = (angulo_rotacion_luz + INCR_ANG_LUZ) % 360;
		cout << "angulo de rotacion de la luz magenta: " << angulo_rotacion_luz << endl;
		break;
	  case 'E' :
	    material_actual = (material_actual + 1) % NUM_MATERIALES;
		cout << "material actual: " << material_actual << endl;
		break;
      case 'C' :
        camara_actual = (camara_actual + 1) % num_camaras;
        cout << "camara actual: " << camara_actual << endl;
        redimensionar(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
        break;
   }

   if (obj_actual_jerarquico) {
	   switch (toupper(tecla)) {
		   case 'P' :
		     objJer->siguienteParametro();
		     cout << "siguiente parametro" << endl;
		     break;
		   case 'A' :
		     animaciones_activas = !animaciones_activas;
		     conmutarAnimaciones();
		     break;
		   case 'Z' :
		     if (tecla == 'Z') {
		   	objJer->incrementaParamAct();
		   	cout << "incrementado parametro actual" << endl;
		    } else {
		   	objJer->decrementaParamAct();
		   	cout << "decrementado parametro actual" << endl;
		    }
		    break;
		   case '>' :
		     objJer->acelerar();
		     cout << "acelerado objeto jerarquico" << endl;
		     break;
		   case '<' :
		     objJer->decelerar();
		     cout << "decelerado objeto jerarquico" << endl;
		     break;
	   }
   }

   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         y_ant--;
         camaras[camara_actual].girar(0.0, -1.0, z_ang);
         break;
	   case GLUT_KEY_RIGHT:
         y_ant++;
          camaras[camara_actual].girar(0.0, 1.0, z_ang);
         break;
	   case GLUT_KEY_UP:
         x_ant--;
         camaras[camara_actual].girar(-1.0, 0.0, z_ang);
         break;
	   case GLUT_KEY_DOWN:
         x_ant++;
         camaras[camara_actual].girar(1.0, 0.0, z_ang);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camara_actual].translateYUp();
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camara_actual].translateYDown();
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

void Escena::conmutarAnimaciones() {
   if (obj_actual_jerarquico) {
      if (animaciones_activas) {
         objJer->inicioAnimaciones();
         glutIdleFunc(funcion_desocupado);
      } else
         glutIdleFunc(nullptr);
   } else
      std::cout << "el objeto actual no es el objeto jerarquico" << std::endl;
}

void Escena::mgeDesocupado() {
   objJer->actualizarEstado();

   // indica que se debe hacer redisplay
   glutPostRedisplay();
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	const float wy = 0.84*Front_plane,
	wx = ratio_xy*wy ;

	if (!camaras[camara_actual].esCamaraOrto())
		camaras[camara_actual].setProjection(-wx, +wx, -wy, +wy, Front_plane, Back_plane);
	else
		camaras[camara_actual].setProjection(-wx, +wx, -wy, +wy, -20.0, 20.0);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
  Width = newWidth;
  Height = newHeight;
  change_projection( float(Width)/float(Height) );
  glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  camaras[camara_actual].setObservador();
}

void Escena::ratonMovido(int x, int y)
{
    if (!camaras[camara_actual].esCamaraOrto())
    {
        if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON)
        {
            camaras[camara_actual].girar(x - x_ant, y - y_ant, z_ang);
            x_ant = x;
            y_ant = y;
        }
    }
}

void Escena::setRatonMovimiento()
{
    estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
}

void Escena::setYUp()
{
    estadoRaton = Y_UP;
}

void Escena::setYDown()
{
    estadoRaton = Y_DOWN;
}

void Escena::setRatonSeleccion()
{
	estadoRaton = SELECCIONAR_OBJETO;
}

void Escena::setRatonNada()
{
	estadoRaton = NADA;
}

void Escena::trasladar()
{
    if (estadoRaton == Y_UP)
    {
        camaras[camara_actual].translateYUp();
    }
    else if (estadoRaton == Y_DOWN)
    {
        camaras[camara_actual].translateYDown();
    }
}

void Escena::setAntXY(int x, int y)
{
    x_ant = x;
    y_ant = y;
}

void Escena::pickColor(int x, int y)
{
	unsigned char pixelLeido[3];
	GLint viewport[4];


	std::cout << "seleccionadas coordenadas (" << x << ", " << y  << ")"
			  << std::endl;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE,
				 (GLubyte *) &pixelLeido[0]);

	estrella->seleccionarPiramide(pixelLeido);

	glutPostRedisplay();
}
