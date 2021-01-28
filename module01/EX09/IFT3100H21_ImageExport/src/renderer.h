// IFT3100H21_ImageExport/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

  ofImage image;

  ofShader shader;
  ofShader shader_passthrough;
  ofShader shader_invert;

  bool filter;

  void setup();
  void draw();

  void image_export(const string name, const string extension) const;
};
