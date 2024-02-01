// IFT3100H24_BackgroundColor/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// énumération de différents modes pour changer la couleur d'arrière-plan
enum class ClearMode {none, black, white, gray, color, random};

class Renderer
{
public:

  ClearMode clear_mode;

  int clear_color_gray;

  int clear_color_r;
  int clear_color_g;
  int clear_color_b;

  bool has_changed;

  void setup();
  void draw();

  void clear() const;
  void clear_to_black() const;
  void clear_to_white() const;
  void clear_to_gray(int g);
  void clear_to_color(int r, int g, int b);
  void clear_to_random();
};
