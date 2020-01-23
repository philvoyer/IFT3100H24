// IFT3100H20_AlmostEmptyProject/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  float time_current;
  float time_last;
  float time_elapsed;

  void setup();
  void update();
  void draw();
};
