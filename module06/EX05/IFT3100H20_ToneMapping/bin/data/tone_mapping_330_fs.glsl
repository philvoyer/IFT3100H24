// IFT3100H20 ~ tone_mapping_330_fs.glsl

#version 330

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

// attributs uniformes
uniform sampler2D image;

// facteur d'exposition
uniform float tone_mapping_exposure;

// mode de mappage tonal (reinhard ou aces filmic)
uniform bool tone_mapping_toggle;

// facteur gamma
uniform float tone_mapping_gamma;

// mappage tonal de la couleur hdr vers ldr (reinhard tone mapping)
vec3 tone_mapping_reinhard(vec3 x)
{
  return x / (x + vec3(1.0));
}

// mappage tonal de la couleur hdr vers ldr (approximation de la courbe du ACES filmic tone mapping)
vec3 tone_mapping_aces_filmic(vec3 x)
{
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

void main()
{
  // variable qui va contenir la couleur à corriger
  vec3 color;

  // échantillonner la texture
  vec3 texture_sample = texture(image, surface_texcoord).rgb;

  // valeur initiale de la couleur
  color = texture_sample;

  // conversion de la couleur de l'espace gamma vers l'espace linéaire
  color = pow(color, vec3(tone_mapping_gamma));

  // ajustement de l'exposition
  color = vec3(1.0) - exp(-color * tone_mapping_exposure);

  // mappage tonal de la couleur hdr vers ldr
  if (tone_mapping_toggle)
    color = tone_mapping_aces_filmic(color);
  else
    color = tone_mapping_reinhard(color);

  // conversion de couleur de l'espace linéaire vers l'espace gamma
  color = pow(color, vec3(1.0 / tone_mapping_gamma));

  // couleur du fragment
  fragment_color = vec4(color, 1.0);
}
