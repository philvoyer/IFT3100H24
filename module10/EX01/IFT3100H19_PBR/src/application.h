// IFT3100H20_PBR/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

class Application : public ofBaseApp
{
  Renderer renderer;

  ofxPanel gui;

  ofxGuiGroup group_material_color;
  ofxGuiGroup group_material_factor;
  ofxGuiGroup group_light;
  ofxGuiGroup group_tone_mapping;

  ofParameter<ofColor> color_picker_ambient;
  ofParameter<ofColor> color_picker_diffuse;
  ofParameter<ofColor> color_picker_specular;

  ofParameter<float> slider_metallic;
  ofParameter<float> slider_roughness;
  ofParameter<float> slider_occlusion;
  ofParameter<float> slider_brightness;

  ofParameter<glm::vec3> slider_fresnel_ior;

  ofParameter<ofColor> color_picker_light_color;

  ofParameter<float> slider_light_intensity;

  ofParameter<float> slider_exposure;
  ofParameter<float> slider_gamma;
  ofParameter<bool> toggle_tone_mapping;

  ofParameter<bool> toggle_ui;
  ofParameter<bool> toggle_light_motion;

  ofxButton button_reset;

  float time_current;
  float time_last;
  float time_elapsed;

  bool is_key_press_up;
  bool is_key_press_down;
  bool is_key_press_left;
  bool is_key_press_right;

  bool is_key_press_w;
  bool is_key_press_a;
  bool is_key_press_s;
  bool is_key_press_d;
  bool is_key_press_q;
  bool is_key_press_e;

  void setup();
  void reset();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);

  void button_reset_pressed();

  void exit();
};
