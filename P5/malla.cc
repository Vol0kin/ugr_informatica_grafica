#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// Alumno: Vladislav Nikolov Vasilev

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());
  glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, triangulos.data());
  glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido()
{
  // Si los identificadores de los VBO son nulos significa que ese bloque
  // aun no se encuentra en la memoria de la GPU, y por tanto se tendran
  // que pasar
  if (id_vbo_ver == 0)
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3 * vertices.size() * sizeof(float), vertices.data());

  if (id_vbo_tri == 0)
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3 * triangulos.size() * sizeof(unsigned), triangulos.data());

  glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);      // activar VBO vertices
  glVertexPointer(3, GL_FLOAT, 0, 0);             // especificar formato
  glBindBuffer(GL_ARRAY_BUFFER, 0);               // desactivar VBO vertices

  glEnableClientState(GL_VERTEX_ARRAY);           // habilitar tabla de vertices

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);    // activar VBO triangulos
  glDrawElements(GL_TRIANGLES, 3 * triangulos.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);             // desactivar VBO triangulos

  glDisableClientState(GL_VERTEX_ARRAY);          // desactivar tabla de vertices
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(ModoVis modo_visualiz, bool modo_diferido)
{
 	if (modo_visualiz == ajedrez)
		dibujar_modo_ajedrez();
	else if (modo_visualiz == luz_suave)
		dibujar_luz_suave();
	else if (modo_visualiz == luz_plana)
		dibujar_luz_plana();
 	else {
		if (!modo_diferido)
			draw_ModoInmediato();
		else
			draw_ModoDiferido();
	}
}

GLuint ObjMallaIndexada::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram) {
  GLuint id_vbo;                    // ID del VBO creado

  glGenBuffers(1, &id_vbo);         // Crear nuevo VBO
  glBindBuffer(tipo_vbo, id_vbo);   // activar VBO mediante ID

  // transferencia de datos de RAM hacia GPU
  glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

  glBindBuffer(tipo_vbo, 0);        // desactivar VBO
  return id_vbo;                    // devolver ID
}

void ObjMallaIndexada::dibujar_modo_ajedrez() {
  std::vector<Tupla3i> triangulos_pares,
                       triangulos_impares;

  for (int i = 0; i < triangulos.size(); i += 2)
    triangulos_pares.push_back(triangulos[i]);

  for (int i = 1; i < triangulos.size(); i += 2)
    triangulos_impares.push_back(triangulos[i]);


  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());

  glColor3f(1, 0.682, 0.019);
  glDrawElements(GL_TRIANGLES, triangulos_pares.size() * 3, GL_UNSIGNED_INT, triangulos_pares.data());

  glColor3f(0.0, 0.0, 1.0);
  glDrawElements(GL_TRIANGLES, triangulos_impares.size() * 3, GL_UNSIGNED_INT, triangulos_impares.data());

  glDisableClientState(GL_VERTEX_ARRAY);
}

void ObjMallaIndexada::dibujar_luz_suave() {
	if (normalesVertices.empty())
		calcular_normales();

	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glNormalPointer(GL_FLOAT, 0, normalesVertices.data());

	glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, triangulos.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void ObjMallaIndexada::dibujar_luz_plana() {
	if (normalesVertices.empty())
		calcular_normales();

	glShadeModel(GL_FLAT);

	// Se indica que se van a dibujar triangulos
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < normalesCaras.size(); i++) {
		// Normal de cara a utilizar
		glNormal3fv(normalesCaras[i]);

		// Se especifican los 3 vertices que usaran la normal
		glVertex3fv(vertices[triangulos[i](X)]);
		glVertex3fv(vertices[triangulos[i](Y)]);
		glVertex3fv(vertices[triangulos[i](Z)]);
	}

	glEnd();
}


// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 2)
   Tupla3f v1, v2, prod_vect;

   normalesCaras.resize(triangulos.size());
   normalesVertices = std::vector<Tupla3f>(vertices.size(), Tupla3f(0.0, 0.0, 0.0));

   for (int i = 0; i < triangulos.size(); i++) {
	   v1 = vertices[triangulos[i](Y)] - vertices[triangulos[i](X)];
	   v2 = vertices[triangulos[i](Z)] - vertices[triangulos[i](Y)];

	   prod_vect = v1.cross(v2);

	   normalesCaras[i] = prod_vect;
	   normalesVertices[triangulos[i](X)] = normalesVertices[triangulos[i](X)] + prod_vect;
	   normalesVertices[triangulos[i](Y)] = normalesVertices[triangulos[i](Y)] + prod_vect;
	   normalesVertices[triangulos[i](Z)] = normalesVertices[triangulos[i](Z)] + prod_vect;
   }
}

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{
    const float POS_VERTEX = 0.5;

   // inicializar la tabla de vértices
   vertices =  {  { -POS_VERTEX * 1, -POS_VERTEX * 1, -POS_VERTEX * 1 }, // 0
                  { -POS_VERTEX * 1, -POS_VERTEX * 1, +POS_VERTEX * 1 }, // 1
                  { -POS_VERTEX * 1, +POS_VERTEX * 1, -POS_VERTEX * 1 }, // 2
                  { -POS_VERTEX * 1, +POS_VERTEX * 1, +POS_VERTEX * 1 }, // 3
                  { +POS_VERTEX * 1, -POS_VERTEX * 1, -POS_VERTEX * 1 }, // 4
                  { +POS_VERTEX * 1, -POS_VERTEX * 1, +POS_VERTEX * 1 }, // 5
                  { +POS_VERTEX * 1, +POS_VERTEX * 1, -POS_VERTEX * 1 }, // 6
                  { +POS_VERTEX * 1, +POS_VERTEX * 1, +POS_VERTEX * 1 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = {{ 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro() {
  const float LADO = 1.0;     // Longitud de un lado

  // Inicializacion tabla vertices inicial (se le aplicará un movimiento mas adelante)
  // Se crea un tetraedro perfecto centrado en el origen de coordenadas
  // con base sobre el plano horizontal
  // La posicion de los vertices viene dada por la longitud del lado
  vertices = {  {-LADO / 2.0, 0.0, -LADO / (2.0 * sqrt(3.0))},  // 0
                { LADO / 2.0, 0.0, -LADO / (2.0 * sqrt(3.0))},  // 1
                {0.0, 0.0, LADO / sqrt(3.0)                 },  // 2
                {0.0, sqrt((2 * LADO * LADO) / 3), 0.0      },  // 3
             };

  // Se calcula el centroide del tetraedro anterior (su centro de gravedad), para poder
  // desplazarlo a donde le corresponda
  Tupla3f centroid( (vertices[0][0] + vertices[1][0] + vertices[2][0] + vertices[3][0]) / 4.0,
                    (vertices[0][1] + vertices[1][1] + vertices[2][1] + vertices[3][1]) / 4.0,
                    (vertices[0][2] + vertices[1][2] + vertices[2][2] + vertices[3][2]) / 4.0
                  );

  // Se aplica la transformacion a cada vertice para situar el centroide
  // en el origen (0, 0, 0)
  for (auto iter = vertices.begin(); iter != vertices.end(); iter++)
    *iter = *iter - centroid;

  // Inicializacion tabla triangulos
  triangulos = { {3, 2, 1}, {3, 1, 0},
                 {3, 0, 2}, {2, 1, 0}
               };
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil )
{
  std::vector<Tupla3f> perfil;
  const int N = 20;              // Numero de perfiles

  // Se leen los vertices del perfil
  ply::read_vertices(nombre_ply_perfil, perfil);

  crear(perfil, N);
}

void ObjRevolucion::crear(const std::vector<Tupla3f> & perfil_original,
                          const int num_instancias_perf,
                          bool tapa_sur,
                          bool tapa_norte) {

  Tupla3f vertice;                                          // Nuevo vertice a insertar
  const float parte = (2 * M_PI) / num_instancias_perf;     // Porcion de radian que corresponde a cada vertice
  const int M = perfil_original.size();                     // Numero de vertices en un perfil
  int a, b;                                                 // Variables auxiliares en el calculo de caras

  // Calculo de los vertices
  for (int i = 0; i < num_instancias_perf; i++) {
      for (int j = 0; j < M; j++) {
          vertice(X) = perfil_original[j](X) * cos(parte * i);
          vertice(Y) = perfil_original[j](Y);
          vertice(Z) = perfil_original[j](X) * sin(parte * i);

          vertices.push_back(vertice);
      }
  }

  // Calculo de las caras
  for (int i = 0; i < num_instancias_perf; i++) {
      for (int j = 0; j < M - 1; j++) {
        a = M * i + j;
        b = M * ( ( i + 1) % num_instancias_perf ) + j;

        // Se insertan los vertices en el orden superior izda, inferior izda, superior dcha
        triangulos.push_back(Tupla3i(b, a, b + 1));

        // Se insertan los vertices en el orden superior dcha, inferior izda, inferior dcha
        triangulos.push_back(Tupla3i(b + 1, a, a + 1));
      }
  }

  // Las caras de la tapa se generan en sentido horario si se mira desde
  // el eje de las Y

  if (tapa_sur) {
    // Se inserta el vertice de la tapa sur
    vertices.push_back(Tupla3f(0.0, vertices[0](Y), 0.0));

    // Se insertan las caras de la tapa sur
    // Primero el actual, luego el siguiente y finalmente el vertice de la tapa
    for (int i = 0; i < num_instancias_perf; i++) {
      triangulos.push_back(Tupla3i(M*i,
                                   M * ((i+1) % num_instancias_perf),
                                   num_instancias_perf * M )
                          );
    }
  }


    if (tapa_norte) {
    // Se inserta el vertice de la tapa norte
    vertices.push_back(Tupla3f(0.0, vertices[perfil_original.size() - 1](Y), 0.0));

    // Se insertan las caras de la tapa norte
    // Primero el vertice de la tapa, luego el siguiente, y despues el actual
    for (int i = 0; i < num_instancias_perf; i++) {
      triangulos.push_back(Tupla3i(num_instancias_perf * M + 1,
                                   M + M*((i+1) % num_instancias_perf) - 1,
                                   M*(i + 1) - 1)
                          );
    }
  }

}

// *****************************************************************************
//
// Clase Cilindro (práctica 2)
//
// *****************************************************************************

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf) {

  Tupla3f vertice;
  std::vector<Tupla3f> perfil_original;
  const float RADIO = 1.0,
              INCREMENTO_Y = 1.0 / num_vert_perfil;


  // Se inserta un vertice mas, habiendo por tanto num_vert_perfil+1 vertices
  // El vertice se encuentra en la altura Y = 1.0

  for (int i = 0; i <= num_vert_perfil; i++) {
    vertice(X) = RADIO;
    vertice(Y) = INCREMENTO_Y * i;
    vertice(Z) = 0.0;

    perfil_original.push_back(vertice);
  }

  // Se crea el cilindro con las tapas
  crear(perfil_original, num_instancias_perf);
}

// *****************************************************************************
//
// Clase Cono (práctica 2)
//
// *****************************************************************************

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf) {

  Tupla3f vertice;
  std::vector<Tupla3f> perfil_original;
  const float RADIO = 1.0,
              INCREMENTO = RADIO / num_vert_perfil;


  // Se inserta un vertice mas, habiendo por tanto num_vert_perfil+1 vertices
  // El vertice extra representa la punta superior del cono

  for (int i = 0; i <= num_vert_perfil; i++) {
    vertice(X) = INCREMENTO * (num_vert_perfil - i);
    vertice(Y) = INCREMENTO * i;
    vertice(Z) = 0.0;

    perfil_original.push_back(vertice);
  }

  // Se crea cono solo con la tapa sur
  crear(perfil_original, num_instancias_perf, true, false);
}

// *****************************************************************************
//
// Clase Esfera (práctica 2)
//
// *****************************************************************************

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf) {

  Tupla3f vertice;
  std::vector<Tupla3f> perfil_original;
  const float ANGULO = M_PI / (float) num_vert_perfil;


  // Se inserta un vertice mas, habiendo por tanto num_vert_perfil+1 vertices
  // El vertice extra representa la punta superior de la esfera

  for (int i = 0; i <= num_vert_perfil; i++) {
    vertice(X) = cos(-M_PI / 2.0 + i*ANGULO);
	vertice(Y) = sin(-M_PI / 2.0 + i*ANGULO);
    vertice(Z) = 0.0;

    perfil_original.push_back(vertice);
  }

  // Se crea la esfera sin las tapas
  crear(perfil_original, num_instancias_perf, false, false);

  // Calculo de las normales para la esfera
  calcular_normales();
}

void Esfera::calcular_normales() {
	const Tupla3f ORIGEN = {0.0, 0.0, 0.0};
	Tupla3f v1, v2, prod_vect;

	normalesCaras.resize(triangulos.size());
	normalesVertices.resize(vertices.size());

	for (int i = 0; i < vertices.size(); i++)
		normalesVertices[i] = vertices[i] - ORIGEN;

    for (int i = 0; i < triangulos.size(); i++) {
 	   v1 = vertices[triangulos[i](Y)] - vertices[triangulos[i](X)];
 	   v2 = vertices[triangulos[i](Z)] - vertices[triangulos[i](Y)];

 	   prod_vect = v1.cross(v2);

 	   normalesCaras[i] = prod_vect;
   }
}

Piramide::Piramide()
{
	vertices = { {0.5, 0.0, 0.5}, {-0.5, 0.0, 0.5},
				 {-0.5, 0.0, -0.5}, {0.5, 0.0, -0.5},
			 	 {0.0, 1.0, 0.0} };

	triangulos = { {4, 0, 3}, {4, 1, 0}, {4, 2, 1}, {4, 3, 2},
				   {1, 2, 3}, {1, 3, 0} };
}
