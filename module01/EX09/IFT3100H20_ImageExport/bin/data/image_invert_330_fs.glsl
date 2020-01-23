// IFT3100H19 ~ image_invert_330_fs.glsl

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

  // inverser la valeur de chaque composante de couleur
  vec4 inverted_color;
  inverted_color.r = 1.0 - texture_sample.r;
  inverted_color.g = 1.0 - texture_sample.g;
  inverted_color.b = 1.0 - texture_sample.b;
  inverted_color.a = texture_sample.a;

  // couleur finale du fragment
  fragment_color = inverted_color;
}
