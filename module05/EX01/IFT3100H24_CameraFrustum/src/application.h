// IFT3100H24_CameraFrustum/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

class Application : public ofBaseApp
{
public:

  ofxPanel gui;

  ofxFloatSlider ui_camera_fov_h;
  ofxFloatSlider ui_camera_zoom_h;
  ofxFloatSlider ui_camera_clip_n;
  ofxFloatSlider ui_camera_clip_f;

  ofParameter<ofColor> ui_color_stroke;
  ofParameter<ofColor> ui_color_fill;

  Renderer renderer;

  void setup();
  void update();
  void draw();
  void exit();
};
