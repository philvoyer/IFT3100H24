// IFT3100H19 ~ image_filter_330_fs.glsl

#version 330

// attributs uniformes
uniform sampler2D image;
uniform vec3 tint;
uniform float factor;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec3 texture_sample = texture(image, surface_texcoord).rgb;

  // mixage avec la teinte de couleur
  vec3 filtered_color = mix(texture_sample, tint, factor);

  // couleur finale du fragment
  fragment_color = vec4(filtered_color, 1.0);
}
