// IFT3100H21_ImageFilter/application.h
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

  ofParameter<ofColor> color_picker;
  ofParameter<float> slider;

  void setup();
  void update();
  void draw();
  void exit();

  void dragEvent(ofDragInfo dragInfo);
};
