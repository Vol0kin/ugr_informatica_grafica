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

void ObjMallaIndexada::draw(int modo, bool ajedrez, int inicio)
{
  if (ajedrez)
    dibujar_modo_ajedrez(inicio);
  else {
    if (modo == 0) 
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

void ObjMallaIndexada::dibujar_modo_ajedrez(int inicio) {
  std::vector<Tupla3i> triangulos_ajedrez;

  for (int i = inicio; i < triangulos.size(); i += 2)
    triangulos_ajedrez.push_back(triangulos[i]);


  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());
  glDrawElements(GL_TRIANGLES, triangulos_ajedrez.size() * 3, GL_UNSIGNED_INT, triangulos_ajedrez.data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 2)
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
                               const int num_instancias_perf) {
  
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

  // Se insertan los vertices de las tapas (primero el sur y luego el norte)
  vertices.push_back(Tupla3f(0.0, vertices[0](Y), 0.0));
  vertices.push_back(Tupla3f(0.0, vertices[perfil_original.size() - 1](Y), 0.0));

  // Las caras de la tapa se generan en sentido horario si se mira desde
  // el eje de las Y

  // Se insertan las caras de la tapa sur
  // Primero el actual, luego el siguiente y finalmente el vertice origen
  for (int i = 0; i < num_instancias_perf; i++) {
    triangulos.push_back(Tupla3i(M*i,
                                 M * ((i+1) % num_instancias_perf),
                                 num_instancias_perf * M )
                        );
  }

  // Se insertan las caras de la tapa norte
  // Primero el vertice origen, luego el siguiente, y despues el actual
  for (int i = 0; i < num_instancias_perf; i++) {
    triangulos.push_back(Tupla3i(num_instancias_perf * M + 1,
                                 M + M*((i+1) % num_instancias_perf) - 1,
                                 M*(i + 1) - 1)
                        );
  }
  
}