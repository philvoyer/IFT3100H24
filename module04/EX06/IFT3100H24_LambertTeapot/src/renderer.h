// IFT3100H23_LambertTeapot/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Renderer
{
public:

  ofShader shader;
  ofShader shader_lambert;
  ofShader shader_normal;

  ofLight light;

  ofxAssimpModelLoader teapot;

  ofColor color_background;
  ofColor color_ambient;
  ofColor color_diffuse;

  float center_x;
  float center_y;

  float scale_teapot;

  float rotation_speed;

  bool use_rotation;

  void setup();
  void update();
  void draw();
};
