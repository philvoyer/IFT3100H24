// IFT3100H23_GL_VertexBufferBindModernPipeline.cpp
// Exemple d'une section de code pour assigner les pointeurs vers chaque attribut de la structure de sommet d'un buffer de géométrie (pipeline moderne).

// entrée
// • Identifiant unique d'un buffer de géométrie déjà initialisé.
// • Identifiant unique d'un programme de shader.
// sortie
// • Un buffer de géométrie prêt à l'utilisation où chaque attribut est adéquatement configuré.

GLuint vbo = ...;
GLuint shader_program = ...;

// définir l'ordre de localisation des attributs de sommet
const GLuint location_vertex_attribute_position = 0;
const GLuint location_vertex_attribute_normal   = 1;
const GLuint location_vertex_attribute_texcoord = 2;
const GLuint location_vertex_attribute_color    = 3;

// sélectionner le shader
glUseProgram(shader_program);

// sélectionner le buffer de géométrie
glBindBuffer(GL_ARRAY_BUFFER, vbo);

// configurer la localisation des attributs du programme et leurs noms en GLSL
glBindAttribLocation(shader_program, location_vertex_attribute_position, "position");
glBindAttribLocation(shader_program, location_vertex_attribute_normal,   "normal");
glBindAttribLocation(shader_program, location_vertex_attribute_texcoord, "texcoord");
glBindAttribLocation(shader_program, location_vertex_attribute_color,    "color");

// assigner les pointeurs vers chaque attribut de la structure de sommet du buffer de géométrie
glVertexAttribPointer(location_vertex_attribute_position, 2, GL_FLOAT,         GL_FALSE, sizeof(VertexStructure), (void*) offsetof(VertexStructure, position));
glVertexAttribPointer(location_vertex_attribute_normal,   2, GL_FLOAT,         GL_FALSE, sizeof(VertexStructure), (void*) offsetof(VertexStructure, normal));
glVertexAttribPointer(location_vertex_attribute_texcoord, 2, GL_FLOAT,         GL_FALSE, sizeof(VertexStructure), (void*) offsetof(VertexStructure, texcoord));
glVertexAttribPointer(location_vertex_attribute_color,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(VertexStructure), (void*) offsetof(VertexStructure, color));

// activer les pointeurs d'attributs
glEnableVertexAttribArray(location_vertex_attribute_position);
glEnableVertexAttribArray(location_vertex_attribute_normal);
glEnableVertexAttribArray(location_vertex_attribute_texcoord);
glEnableVertexAttribArray(location_vertex_attribute_color);
