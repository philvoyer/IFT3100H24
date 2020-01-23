// IFT3100H19 ~ image_tint_330_fs.glsl

#version 330

// attributs uniformes
uniform sampler2D image;
uniform vec4 tint;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec4 texture_sample = texture(image, surface_texcoord);

  // mixage avec la teinte de couleur
  vec4 filtered_color = mix(texture_sample, tint, 0.25);

  // couleur finale du fragment
  fragment_color = filtered_color;
}
