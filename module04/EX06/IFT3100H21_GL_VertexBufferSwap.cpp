// IFT3100H21_GL_VertexBufferSwap.cpp
// Exemple d'une section de code qui inverse en alternance deux buffers de géométrie utilisés pour la mise à jour et le rendu afin d'éviter de bloquer le pipeline de rendu.

// entrée
// • Deux buffers de géométrie indépendants avec une structure identique mais des données distinctes.
// sortie
// • Le buffer de géométrie utilisé pour le rendu n'est pas celui dans lequel il y a mise à jour durant le même frame.

// deux buffers de géométrie déjà initialisés
GLuint vbo_alpha;
GLuint vbo_beta;

// buffer de géométrie utilisé pour la mise à jour (écriture)
GLuint vbo_update;

// buffer de géométrie utilisé pour le rendu (lecture)
GLuint vbo_draw;

// booléen qui indique si on est prêt pour une inversion des buffers de géométrie
bool is_ready_to_swap;

// booléen qui indique si les buffers de géométrie sont dans l'ordre initiale ou non
bool is_in_order;

if (is_ready_to_swap)
{
  if (is_in_order)
  {
    vbo_update = vbo_alpha;
    vbo_draw = vbo_beta;

    is_in_order = false;
  }
  else
  {
    vbo_update = vbo_beta;
    vbo_draw = vbo_alpha;

    is_in_order = true;
  }

  is_ready_to_swap = false;
}

if (/* mise à jour du modèle */)
{
  // sélectionner le vbo de mise à jour
  glBindBuffer(GL_ARRAY_BUFFER, vbo_update);

  // mise à jour du buffer de géométrie
  // ...

  // inverser les buffers de géométrie lors du prochain frame
  is_ready_to_swap = true;
}

// sélectionner le vbo de mise à jour
glBindBuffer(GL_ARRAY_BUFFER, vbo_draw);

// rendre le buffer de géométrie avec une commande de rendu
// ex. glDrawArrays ou glDrawElements
