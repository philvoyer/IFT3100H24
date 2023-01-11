// IFT3100H23_DrawCursor/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  int mouse_press_x;
  int mouse_press_y;

  int mouse_current_x;
  int mouse_current_y;

  bool is_mouse_button_pressed;

  void setup();
  void draw();

  void draw_cursor(float x, float y) const;
};
