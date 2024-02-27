// IFT3100H23_GL_Mesh.cpp
// Exemple de types minimaliste pour stocker les données des sommets d'un maillage triangulaire.

// entrée
// • Une structure de sommet, une structure de triangle et données initiales du maillage triangulaire.
// sortie
// • Classe qui contient des triangles indexés par leurs sommets.

// structure de sommet
struct Vertex
{
  GLfloat position[3]; // 3 * 4 = 12 octets
  GLfloat normal  [3]; // 3 * 4 = 12 octets
  GLfloat texcoord[2]; // 2 * 4 = 8  octets
  GLubyte color   [4]; // 4 * 1 = 4  octets
};                     //       = 36 octets

// structure d'un triangle
struct Triangle
{
  // indices des 3 sommets
  int vertex_index[3];
};

// classe d'un maillage géométrique
class Mesh
{
  // nombre de sommets
  int vertex_count;

  // séquence des sommets
  Vertex* vertex_array;

  // nombre des triangles
  int triangle_count;

  // séquence des triangles
  Triangle* triangle_array;

  // tableau d'indices
  int* indice_array;

  mesh()
  {
    // allocation d'une séquence de sommets
    vertex_array = (Vertex*) std::malloc(vertex_count * sizeof(Vertex));

    // allocation d'un tableau de triangles
    triangle_array = (Triangle*) std::malloc(triangle_count * sizeof(Triangle));

    // allocation d'un tableau d'indices de sommet
    indice_array = (int*) std::malloc(vertex_count);

    // ...
  }

  ~Mesh()
  {
    std::delete vertex_array;
    std::delete triangle_array;
    std::delete indice_array;
  }
};
