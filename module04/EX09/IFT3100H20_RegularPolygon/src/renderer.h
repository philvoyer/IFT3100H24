// IFT3100H20_RegularPolygon/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  std::string mode;

  float polygon_center_x;
  float polygon_center_y;

  float position_vertex_x;
  float position_vertex_y;

  float angle;
  float offset;
  float radius;

  float point_diameter;

  int side;
  int index;

  void setup();
  void update();
  void draw();
};
