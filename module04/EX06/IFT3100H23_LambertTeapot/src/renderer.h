// IFT3100H23_LambertTeapot/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"

class Renderer
{
public:

  ofShader shader;

  ofLight light;

  ofxAssimpModelLoader teapot;

  ofxPanel gui;

  ofParameter<ofColor> color_picker;

  float center_x;
  float center_y;

  float scale_teapot;

  bool use_rotation;

  void setup();
  void update();
  void draw();
};
