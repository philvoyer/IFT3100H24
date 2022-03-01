// IFT3100H22_ToneMapping/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofImage image;

  ofShader shader;

  int offset_vertical;
  int offset_horizontal;

  float tone_mapping_exposure;
  float tone_mapping_gamma;

  bool tone_mapping_toggle;

  void setup();
  void draw();
};
