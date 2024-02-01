// IFT3100H24_Interface/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofTrueTypeFont font;

  ofColor background_color;

  ofColor stroke_color;

  ofRectangle bounding_box;

  string text;

  float stroke_weight;

  float line_offset;

  int font_size;

  void setup();
  void update();
  void draw();
};
