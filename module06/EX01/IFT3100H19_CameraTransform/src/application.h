// IFT3100H19_CameraTransform/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  bool is_key_press_up;
  bool is_key_press_down;
  bool is_key_press_left;
  bool is_key_press_right;

  bool is_key_press_a;
  bool is_key_press_d;
  bool is_key_press_e;
  bool is_key_press_h;
  bool is_key_press_i;
  bool is_key_press_j;
  bool is_key_press_k;
  bool is_key_press_q;
  bool is_key_press_s;
  bool is_key_press_u;
  bool is_key_press_w;
  bool is_key_press_x;
  bool is_key_press_y;
  bool is_key_press_z;

  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
};
