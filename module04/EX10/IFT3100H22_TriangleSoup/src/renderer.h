// IFT3100H22_TriangleSoup/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// structure d'un triangle
struct Triangle
{
  GLfloat position1[3]; // 3 * 4 = 12 octets
  GLfloat position2[3]; // 3 * 4 = 12 octets
  GLfloat position3[3]; // 3 * 4 = 12 octets
  GLubyte color[4];     // 4 * 1 = 4  octets
};                      //       = 40 octets

class Renderer
{
public:

  Triangle* soup;

  ofVec3f vector_origin;

  ofVec3f vector_position1;
  ofVec3f vector_position2;
  ofVec3f vector_position3;

  ofColor vector_color;

  ofLight light;

  ofNode node;

  float center_x;
  float center_y;

  float speed;

  float offset_x;
  float offset_y;
  float offset_z;

  float delta_x;
  float delta_y;
  float delta_z;

  float soup_radius;
  float soup_proportion;

  float triangle_radius;

  int triangle_count;

  int triangle_buffer_size;
  int triangle_buffer_head;

  bool bowl_or_ball;

  void setup();

  void dispatch_random_triangle(int count, float range);

  void reset();

  void draw();

  void draw_scene();

  void draw_soup();

  void draw_triangle(int index);

  void draw_locator(float scale);

  ~Renderer();
};
