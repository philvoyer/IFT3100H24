// IFT3100H23_BonjourTriangle/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  float vertex1_x;
  float vertex1_y;
  float vertex2_x;
  float vertex2_y;
  float vertex3_x;
  float vertex3_y;

  float color_r;
  float color_g;
  float color_b;

  float point_radius;

  int framebuffer_width;
  int framebuffer_height;

  void setup();
  void update();
  void draw();
};
