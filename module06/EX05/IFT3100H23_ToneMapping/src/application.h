// IFT3100H23_ToneMapping/application.h
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

  ofxGuiGroup group_tone_mapping;
  ofParameter<float> slider_exposure;
  ofParameter<float> slider_gamma;
  ofParameter<bool> toggle_tone_mapping;

  void setup();
  void update();
  void draw();
  void exit();

  void dragEvent(ofDragInfo dragInfo);
};
