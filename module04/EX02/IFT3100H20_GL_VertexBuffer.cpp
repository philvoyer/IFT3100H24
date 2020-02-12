// IFT3100H20_GL_VertexBufferCreate.cpp
// Exemple d'une section de code pour créer d'un buffer de géométrie (vbo).

// entrée
// • Les données des attributs de chaque sommet d'un modèle.
// sortie
// • Un buffer de géométrie mis en cache en mémoire GPU et prêt à l'utilisation, en version statique et dynamique, puis destruction.

// 1. initialisation des données du modèle

// une structure de sommet avec une taille fixe pour chaque attribut
struct Vertex {...};

// nombre de sommets à stocker dans le buffer de géométrie
int vertex_count;

// calculer la taille de la structure de sommet en nombre d'octets
int vertex_structure_size = sizeof(Vertex);

// calculer le nombre d'octets à allouer en mémoire pour contenir le buffer de géométrie
int vertex_buffer_size = vertex_count * vertex_structure_size;

// déclarer un pointeur sur un espace mémoire du même type que la structure de sommet
Vertex* vertex_array;

// allocation d'un espace mémoire suffisament grand pour contenir les données des attributs de tous les sommets
vertex_array = (Vertex*) std::malloc(vertex_buffer_size);

// assigner les données de chaque attribut pour chaque sommet
for (int index = 0; index < vertex_count; ++index)
{
  vertex_array[index].position[0] = ...;
  vertex_array[index].position[1] = ...;
  vertex_array[index].position[2] = ...;
  vertex_array[index].normal  [0] = ...;
  vertex_array[index].normal  [1] = ...;
  vertex_array[index].normal  [2] = ...;
  vertex_array[index].texcoord[0] = ...;
  vertex_array[index].texcoord[1] = ...;
  vertex_array[index].color   [0] = ...;
  vertex_array[index].color   [1] = ...;
  vertex_array[index].color   [2] = ...;
  vertex_array[index].color   [3] = ...;
  ...
}

// 2. création d'un buffer de géométrie statique

// déclarer un identifiant pour référencer un nouveau buffer de géométrie
GLuint vbo1;

// création d'un nouveau buffer de géométrie dont l'identifiant unique sera retourné par OpenGL
glGenBuffers(1, &vbo1);

// sélectionner le nouveau buffer de géométrie
glBindBuffer(GL_ARRAY_BUFFER, vbo1);

// transférer les données de la mémoire RAM vers buffer de géométrie en mémoire du GPU
glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, vertex_array, GL_STATIC_DRAW);

// déselectionner le buffer
glBindBuffer(GL_ARRAY_BUFFER, 0);

// les données en mémoire RAM peuvent être supprimées si le buffer de géométrie est statique
std::free(vertex_array);


// 3. création d'un buffer de géométrie dynamique

// déclarer un identifiant pour référencer un nouveau buffer de géométrie
GLuint vbo2;

// création d'un nouveau buffer de géométrie dont l'identifiant unique sera retourné par OpenGL
glGenBuffers(1, &vbo2);

// sélectionner le nouveau buffer de géométrie
glBindBuffer(GL_ARRAY_BUFFER, vbo2);

// lors de l'initialisation :

// transférer les données de la mémoire RAM vers buffer de géométrie en mémoire du GPU
glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, vertex_array, GL_DYNAMIC_DRAW);

// après mise à jour des données du buffer de géométrie :

// valeur de décalage pour atteindre le premier sommet qui a été modifié
int vertex_offset = ...;

// nombre de sommets qui ont été modifiés
int updated_vertex_count = ...;

// téléverser un intervalle continu de sommets de la mémoire RAM vers le buffer de géométrie en mémoire GPU
glBufferSubData(GL_ARRAY_BUFFER, vertex_offset * sizeof(Vertex), updated_vertex_count * sizeof(Vertex), vertex_array);

// déselectionner le buffer
glBindBuffer(GL_ARRAY_BUFFER, 0);


// 4. destruction d'un buffer de géométrie
glDeleteBuffers(1, &vbo1);
glDeleteBuffers(1, &vbo2);
