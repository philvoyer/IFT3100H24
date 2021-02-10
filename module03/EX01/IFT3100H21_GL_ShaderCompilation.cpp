// IFT3100H21_GL_ShaderCompilation.cpp
// Exemple de création, de compilation, d'activation, de rendu et de destruction d'un shader avec OpenGL.

// entrée
// • Code source d'un shader sous forme de deux chaines de caractères (un shader de sommets et un shader de fragments).
// sortie
// • Compilation du shader, activation puis destruction.

// 1. création d'un nouveau shader

// code source du shader de sommets et du shader de fragments
GLchar* source_shader_vertex = "...";
GLchar* source_shader_fragment = "...";

// déclaration de variables pour les statuts de compilation et assemblage
GLint status_compile;
GLint status_link;

// déclaration des identifiants uniques pour les instances d'objets OpenGL de type shader
GLuint shader_program;  // identifiant du shader
GLuint shader_vertex;   // shader de sommets
GLuint shader_fragment; // shader de fragments

// instanciation du nouveau programme
shader_program = glCreateProgram();


// 2. création d'un shader de sommets

// instanciation d'un nouveau shader de sommets
shader_vertex = glCreateShader(GL_VERTEX_SHADER);

// assigner le code source du shader de sommets
glShaderSource(shader_vertex, 1, &source_shader_vertex, nullptr);

// compilation du shader de sommets
glCompileShader(shader_vertex);

// extraction du statut de compilation
glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &status_compile);


// 3. création d'un shader de fragments

// instanciation d'un nouveau shader de fragments
shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);

// assigner le code source du shader de fragments
glShaderSource(shader_fragment, 1, &source_shader_fragment, nullptr);

// compilation du shader de fragments
glCompileShader(shader_fragment);

// extraction du statut de compilation
glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &status_compile);


// 4. assemblage d'un shader

// attacher le shader de sommet au programme
glAttachShader(shader_program, shader_vertex);

// attacher le shader de fragment au programme
glAttachShader(shader_program, shader_fragment);

// assembler le programme
glLinkProgram(shader_program);

// extraction du statut d'assemblage
glGetProgramiv(shader_program, GL_LINK_STATUS, &status_link);



// 5. activation d'un shader

// sélection du shader actif
glUseProgram(shader_program);

// configurer les états de rendu (VBO, attributs de sommets, attributs uniformes, matrices de transformation, etc.)
// ...


// 6. rendu avec un shader

// après son activation, toutes les commandes de dessin vont utiliser le shader
glDrawArrays(GL_TRIANGLES, 0, vertex_count);


// 7. destruction d'un shader

// détacher le shader de sommet
glDetachShader(shader_program, shader_vertex);

// détacher le shader de fragment
glDetachShader(shader_program, shader_fragment);

// supprimer le shader de sommet.
glDeleteShader(shader_vertex);

// supprimer le shader de fragment.
glDeleteShader(shader_fragment);

// supprimer le programme
glDeleteProgram(shader_program);
