// IFT3100H24_GL_VertexBufferDraw.cpp
// Exemple de différentes approches pour dessiner un buffer de géométrie.

// entrée
// • Identifiant unique d'un buffer de géométrie déjà initialisé.
// sortie
// • Rendu graphique du contenu du buffer de géométrie dans un framebuffer.

// identifiant d'un buffer de géométrie
GLuint vbo;

// index du premier sommet à rendre
int start;

// nombre de sommets à rendre
int count;

// tableau d'index de sommet
int* index;

// sélectionner le buffer de géométrie
glBindBuffer(GL_ARRAY_BUFFER, vbo);

// exemples de commande de rendu avec différents types de primitives topologiques :

// 1. dessiner un ensemble de points
glDrawArrays(GL_POINTS, start, count);

// 2. dessiner un ensemble de lignes
glDrawArrays(GL_LINE_LOOP, start, count);

// 3. dessiner un quad à partir de deux triangles connexes
glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

// 4. dessiner une série de triangles connexes
glDrawArrays(GL_TRIANGLE_STRIP, start, count);

// 5. dessiner un élément à partir d'un buffer d'index
glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_SHORT, index);
