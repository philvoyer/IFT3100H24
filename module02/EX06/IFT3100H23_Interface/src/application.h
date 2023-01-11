// IFT3100H23_Interface/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

class Application : public ofBaseApp
{
  Renderer renderer;

  ofxPanel gui;

  ofxGuiGroup group_draw;

  ofParameter<ofColor> color_picker_background;
  ofParameter<ofColor> color_picker_stroke;

  ofParameter<float> slider_stroke_weight;

  ofParameter<string> textbox;

  ofParameter<bool> checkbox;

  ofxButton button;

  void setup();
  void update();
  void draw();
  void exit();

  void keyReleased(int key);

  void windowResized(int w, int h);

  void button_pressed();
};
