// IFT3100H23_CameraProjection/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include <glm/gtx/string_cast.hpp>

class Renderer
{
public:

  ofCamera camera;
  ofCamera cameraPerspective;
  ofCamera cameraOrthographic;

  ofShader shader;
  ofShader shader_lambert;
  ofShader shader_normal;
  ofShader shader_depth;

  ofLight light;

  ofxAssimpModelLoader teapot;

  ofColor color_background;
  ofColor color_ambient;
  ofColor color_diffuse;

  glm::vec3 camera_position;

  bool camera_projection_persp_or_ortho;

  float camera_viewport_x;
  float camera_viewport_y;
  float camera_aspect_ratio;
  float camera_clip_n;
  float camera_clip_f;
  float camera_depth_range;
  float camera_fov;
  float camera_zoom;
  float camera_vertical_flip;

  float speed;
  float center_x;
  float center_y;

  float offset_x;
  float offset_z;

  float delta_x;
  float delta_z;

  float scale_teapot;

  float rotation_speed;

  bool use_rotation;

  bool camera_is_active;

  bool camera_state_change;

  std::string camera_name;

  void setup();
  void update();
  void update_camera();
  void draw();

  float compute_fov_from_zoom(float zoom);
  float compute_zoom_from_fov(float fov);

  void camera_setup_perspective(float width, float height, float fov, float near, float far);
  void camera_current_state_log();
};
