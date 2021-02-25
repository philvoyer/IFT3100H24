// IFT3100H21_CameraFrustum/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
public:

  ofxPanel gui;

  ofParameter<ofColor> color_stroke;
  ofParameter<ofColor> color_fill;
  ofParameter<ofColor> color_frustum_in;
  ofParameter<ofColor> color_frustum_out;

  ofxFloatSlider ui_camera_fov_h;
  ofxFloatSlider ui_camera_zoom_h;
  ofxFloatSlider ui_camera_clip_n;
  ofxFloatSlider ui_camera_clip_f;

  ofPolyline camera_frustum_outline;

  float camera_clip_n;
  float camera_clip_f;

  float camera_fov;

  float camera_zoom;

  float clip_half_width_n;
  float clip_half_width_f;

  float clip_width_n;
  float clip_width_f;

  float camera_resolution_w;
  float camera_resolution_h;

  float camera_aspect_ratio;

  float circle_radius;
  float stroke_width;
  float scale_factor;

  glm::vec3 camera_position;
  glm::vec3 camera_target;

  glm::vec3 position_clip_n_l;
  glm::vec3 position_clip_n_c;
  glm::vec3 position_clip_n_r;
  glm::vec3 position_clip_f_l;
  glm::vec3 position_clip_f_c;
  glm::vec3 position_clip_f_r;

  void setup();
  void reset();
  void update();
  void draw();

  void generate_matrix();
};
