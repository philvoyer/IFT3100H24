// IFT3100H23_CameraFrustum/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
public:

  ofPolyline camera_frustum_outline;

  ofColor color_stroke;
  ofColor color_fill;

  float camera_viewport_x;
  float camera_viewport_y;

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

  float compute_fov_from_zoom(float zoom);
  float compute_zoom_from_fov(float fov);
};
