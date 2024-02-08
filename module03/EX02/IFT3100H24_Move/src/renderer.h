// IFT3100H24_Move/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofNode node;

  float center_x;
  float center_y;

  float offset_x;
  float offset_z;

  float delta_x;
  float delta_z;

  float speed;

  void setup();
  void update();
  void draw();

  void reset();

  void draw_locator(float scale);
};
