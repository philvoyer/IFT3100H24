// IFT3100H19 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;

// position d'une source de lumière
uniform vec3 light_position;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(light_position - surface_position);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragment_color = vec4(color_ambient + color_diffuse * reflection_diffuse, 1.0);
}
