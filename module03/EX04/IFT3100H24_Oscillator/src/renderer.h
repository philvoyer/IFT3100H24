// IFT3100H24_Oscillator/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  float position_x;
  float position_y;

  float amplitude_x;
  float amplitude_y;

  float frequency_x;
  float frequency_y;

  float radius;

  float time_current;

  ofColor color_cpu;
  ofColor color_gpu;

  ofShader shader;

  void setup();
  void update();
  void draw();

  float oscillate(float time, float amplitude, float frequency);
};
