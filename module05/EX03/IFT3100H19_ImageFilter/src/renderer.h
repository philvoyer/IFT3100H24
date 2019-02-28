// IFT3100H19_ImageFilter/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  float mix_factor;

  ofColor tint;

  ofImage image;

  ofShader shader;

  int offset_vertical;
  int offset_horizontal;

  void setup();
  void draw();
};
