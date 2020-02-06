// IFT3100H20_Origin/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofNode node;

  float center_x;
  float center_y;

  void setup();
  void update();
  void draw();

  void draw_locator(float scale);
};
