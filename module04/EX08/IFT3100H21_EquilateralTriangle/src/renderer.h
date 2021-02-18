// IFT3100H21_EquilateralTriangle/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  float viewport_center_x;
  float viewport_center_y;

  float triangle_origin_x;
  float triangle_origin_y;

  float triangle_center_x;
  float triangle_center_y;

  float vertex1_x;
  float vertex1_y;

  float vertex2_x;
  float vertex2_y;

  float vertex3_x;
  float vertex3_y;

  float triangle_edge_diameter;
  float triangle_edge_diameter_half;

  float triangle_perimeter;
  float triangle_altitude;
  float triangle_area;

  float triangle_innercircle_radius;
  float triangle_circumcircle_radius;

  float point_diameter;

  void setup();
  void update();
  void draw();
};
