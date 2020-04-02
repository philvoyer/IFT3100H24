// IFT3100H20_CurveHermite/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// énumération de types de courbe
enum class CurveType {bezier_cubic, hermite};

// fonction d'évaluation d'une courbe de hermite (4 points de contrôle)
inline void hermite(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float p4x, float p4y, float p4z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;
  float uu = u * u;
  float uuu = uu * u;
  float tt = t * t;
  float ttt = tt * t;

  x = (2 * ttt - 3 * tt + 1) * p1x + (ttt - 2 * tt + t) * p2x + (ttt - tt) * p3x + (-2 * ttt + 3 * tt) * p4x;
  y = (2 * ttt - 3 * tt + 1) * p1y + (ttt - 2 * tt + t) * p2y + (ttt - tt) * p3y + (-2 * ttt + 3 * tt) * p4y;
  z = (2 * ttt - 3 * tt + 1) * p1z + (ttt - 2 * tt + t) * p2z + (ttt - tt) * p3z + (-2 * ttt + 3 * tt) * p4z;
}

// fonction d'évaluation d'une courbe de Bézier cubique (4 points de contrôle)
inline void bezier_cubic(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float p4x, float p4y, float p4z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;
  float uu = u * u;
  float uuu = uu * u;
  float tt = t * t;
  float ttt = tt * t;

  x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
  y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
  z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
}

class Renderer
{
public:

  CurveType curve_type;

  string  curve_name;

  ofPolyline line_renderer;

  ofVec3f* selected_ctrl_point;

  ofVec3f ctrl_point1;
  ofVec3f ctrl_point2;
  ofVec3f ctrl_point3;
  ofVec3f ctrl_point4;

  ofVec3f initial_position1;
  ofVec3f initial_position2;
  ofVec3f initial_position3;
  ofVec3f initial_position4;
  ofVec3f initial_position5;

  ofVec3f position;

  ofVec3f tangent1;
  ofVec3f tangent2;

  float line_width_outline;
  float line_width_curve;

  float radius;
  float scale;
  float offset;

  float delta_x;
  float delta_y;

  float motion_speed;

  int framebuffer_width;
  int framebuffer_height;

  int line_resolution;

  int index;

  void setup();
  void update();
  void draw();
  void reset();
};
