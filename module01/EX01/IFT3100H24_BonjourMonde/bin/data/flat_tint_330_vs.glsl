// IFT3100H24 ~ flat_tint_330_vs.glsl

#version 330

// attribut uniforme
uniform mat4 modelViewProjectionMatrix;

// attribut de sommet
in vec4 position;

void main()
{
  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = modelViewProjectionMatrix * position;
}
