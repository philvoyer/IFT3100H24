// IFT3100H22_ImageFilter/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofImage image;

  ofShader shader;

  float mix_factor;

  ofColor tint;

  int offset_vertical;
  int offset_horizontal;

  void setup();
  void draw();
};
