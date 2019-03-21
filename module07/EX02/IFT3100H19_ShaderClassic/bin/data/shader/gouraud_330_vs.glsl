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
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer le niveau de réflexion diffuse (n • l)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // réflexion spéculaire par défaut
  float reflection_specular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflection_diffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (v)
    vec3 v = normalize(-surface_position);

    // calculer la direction de la réflection (v) du rayon incident (-l) en fonction de la normale (n)
    vec3 r = reflect(-l, n);

    // calculer le niveau de réflexion spéculaire (r • v)
    reflection_specular = pow(max(dot(v, r), 0.0), brightness);
  }

  // calculer la couleur du fragment
  surface_color = vec3(
    color_ambient +
    color_diffuse * reflection_diffuse +
    color_specular * reflection_specular);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = projectionMatrix * modelViewMatrix * position;
}
