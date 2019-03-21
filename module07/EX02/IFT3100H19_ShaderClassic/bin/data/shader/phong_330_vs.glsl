// IFT3100H19 ~ phong_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec4 normal;

// attributs en sortie
out vec3 surface_position;
out vec3 surface_normal;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  surface_normal = vec3(normalMatrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  surface_position = vec3(modelViewMatrix * position);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
