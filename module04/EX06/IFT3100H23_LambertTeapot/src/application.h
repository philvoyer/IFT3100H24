// IFT3100H23_LambertTeapot/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  ofxPanel gui;

  ofParameter<ofColor> color_picker_background;
  ofParameter<ofColor> color_picker_ambient;
  ofParameter<ofColor> color_picker_diffuse;

  void setup();
  void update();
  void draw();
  void exit();

  void keyReleased(int key);
};
