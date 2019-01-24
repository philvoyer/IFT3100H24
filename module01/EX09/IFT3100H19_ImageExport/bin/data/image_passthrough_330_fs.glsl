// IFT3100H19 ~ image_passthrough_330_fs.glsl

#version 330

// attribut uniforme
uniform sampler2D image;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec4 texture_sample = texture(image, surface_texcoord);

  // couleur finale du fragment
  fragment_color = texture_sample;
}
