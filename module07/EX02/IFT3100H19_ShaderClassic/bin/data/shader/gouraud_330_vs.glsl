// IFT3100H19 ~ gouraud_330_vs.glsl

#version 330

// attributs de sommet
in vec4 position;
in vec4 normal;

// attributs en sortie
out vec3 surface_color;

// attributs uniformes
uniform mat4x4 modelViewMatrix;
uniform mat4x4 projectionMatrix;

// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;
uniform vec3 color_specular;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 light_position;

void main()
{
  // calculer la matrice normale
  mat4x4 normalMatrix = transpose(inverse(modelViewMatrix));

  // transformation de la normale du sommet dans l'espace de vue
  vec3 surface_normal = vec3(normalMatrix * normal);

  // transformation de la position du sommet dans l'espace de vue
  vec3 surface_position = vec3(modelViewMatrix * position);

  // re-normaliser la normale
  vec3 N = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 L = normalize(light_position - surface_position);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflection_specular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflection_diffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-surface_position);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflection_specular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  surface_color = vec3(
    color_ambient +
    color_diffuse * reflection_diffuse +
    color_specular * reflection_specular);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
