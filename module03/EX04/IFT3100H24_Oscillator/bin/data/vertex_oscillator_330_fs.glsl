// IFT3100H24 ~ vertex_oscillator_330_fs.glsl

#version 330

// attribut uniforme
uniform vec4 tint;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // couleur finale du fragment
  fragment_color = tint;
}
