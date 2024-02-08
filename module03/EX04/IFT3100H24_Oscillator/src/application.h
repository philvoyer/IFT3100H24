// IFT3100H24_Oscillator/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "renderer.h"

class Application : public ofBaseApp
{
public:

  ofxPanel gui;

  ofxGuiGroup gui_group;

  ofParameter<float> slider_amplitude_x;
  ofParameter<float> slider_amplitude_y;
  ofParameter<float> slider_frequency_x;
  ofParameter<float> slider_frequency_y;

  Renderer renderer;

  void setup();
  void update();
  void draw();
};
