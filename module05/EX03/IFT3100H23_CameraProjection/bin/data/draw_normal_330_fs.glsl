// IFT3100H23 ~ draw_normal_330_fs.glsl

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
  vec3 normal = normalize(surface_normal);

  // déterminer la couleur du fragment
  fragment_color = vec4(normal.x, normal.y, normal.z, 1.0);
}
