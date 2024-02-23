// IFT3100H24_CameraProjection/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "renderer.h"

#include <algorithm>

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  ofxPanel gui;

  ofxGuiGroup ui_group_color;
  ofxGuiGroup ui_group_camera;

  ofParameter<ofColor> ui_color_picker_background;
  ofParameter<ofColor> ui_color_picker_ambient;
  ofParameter<ofColor> ui_color_picker_diffuse;

  ofParameter<float> ui_camera_fov_h;
  ofParameter<float> ui_camera_zoom_h;
  ofParameter<float> ui_camera_clip_n;
  ofParameter<float> ui_camera_clip_f;

  ofTrueTypeFont font;

  float time_current;
  float time_last;
  float time_elapsed;

  float ui_offset;

  float ui_anchor_x;
  float ui_anchor_y;

  bool is_key_press_up;
  bool is_key_press_down;
  bool is_key_press_left;
  bool is_key_press_right;

  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);

  std::string string_format_float_precision(float value, int precision);
  std::string string_format_int_pad(int value, size_t size, char pad);
};
