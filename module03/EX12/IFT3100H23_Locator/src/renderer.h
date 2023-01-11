// IFT3100H23_Locator/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// structure d'un localisateur de transformation
struct Locator
{
  float position[3];   // 3 * 4 = 12 octets
  float rotation[3];   // 3 * 4 = 12 octets
  float proportion[3]; // 3 * 4 = 12 octets
};                     //       = 36 octets

class Renderer
{
public:

  Locator* locators;

  ofNode node;

  ofVec3f vector_position;
  ofVec3f vector_rotation;
  ofVec3f vector_proportion;

  float center_x;
  float center_y;

  float offset_x;
  float offset_z;

  float delta_x;
  float delta_z;

  float speed;

  int locator_count;

  int locator_buffer_head;

  bool is_flip_axis_y;

  bool is_active_translation;
  bool is_active_rotation;
  bool is_active_proportion;

  void setup();
  void update();
  void draw();

  void reset();

  void dispatch_locators(int count, float range);

  void draw_locator(float scale);

  ~Renderer();
};
