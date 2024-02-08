// IFT3100H24 ~ vertex_oscillator_330_vs.glsl

#version 330

// attributs uniformes
uniform mat4 modelViewProjectionMatrix;

uniform float amplitude_x;
uniform float amplitude_y;

uniform float frequency_x;
uniform float frequency_y;

uniform float time;

// attribut de sommet
in vec4 position;

// constantes
const float PI = 3.1415926535897932384626433832795;

// fonction d'oscillation
float oscillate(float time, float amplitude, float frequency)
{
  return amplitude * sin(time * 2.0 * PI / frequency);
}

void main()
{
  // copier la position d'origine du sommet
  vec4 oscillated_position = position;

  // calculer l'oscillation sur l'axe X
  oscillated_position.x += oscillate(time, amplitude_x, frequency_x);

  // calculer l'oscillation sur l'axe Y
  oscillated_position.y += oscillate(time, amplitude_y, frequency_y);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = modelViewProjectionMatrix * oscillated_position;
}
