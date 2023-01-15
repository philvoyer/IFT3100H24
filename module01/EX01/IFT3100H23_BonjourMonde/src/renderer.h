// IFT3100H23_BonjourMonde/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofColor color_background;
  ofColor color_tint;
  ofColor color_random;

  ofShader shader;

  void setup();
  void draw();

  void select_random_colors();
};
