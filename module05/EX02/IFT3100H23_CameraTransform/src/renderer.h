// IFT3100H23_CameraTransform/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

enum class Camera {front, back, left, right, top, down};

class Renderer
{
public:

  Camera camera_active;

  ofCamera camera_front;
  ofCamera camera_back;
  ofCamera camera_left;
  ofCamera camera_right;
  ofCamera camera_top;
  ofCamera camera_bottom;

  ofCamera* camera;

  ofQuaternion camera_orientation;

  ofVec3f camera_position;
  ofVec3f camera_target;

  string camera_name;
  string camera_projection;

  float camera_near;
  float camera_far;

  float camera_fov;
  float camera_fov_delta;

  float offset_camera;
  float offset_color;
  float offset_scene;
  float offset_cube;

  float speed_delta;
  float speed_translation;
  float speed_rotation;

  float time_current;
  float time_last;
  float time_elapsed;

  float cube_size;

  int cube_count;

  int index_x;
  int index_y;
  int index_z;

  bool is_visible_axes;
  bool is_visible_grid;
  bool is_visible_camera;
  bool is_visible_frustum;
  bool is_visible_box;
  bool is_visible_locator;
  bool is_visible_text;

  bool is_camera_move_left;
  bool is_camera_move_right;
  bool is_camera_move_up;
  bool is_camera_move_down;
  bool is_camera_move_forward;
  bool is_camera_move_backward;

  bool is_camera_tilt_up;
  bool is_camera_tilt_down;
  bool is_camera_pan_left;
  bool is_camera_pan_right;
  bool is_camera_roll_left;
  bool is_camera_roll_right;

  bool is_camera_fov_narrow;
  bool is_camera_fov_wide;

  bool is_camera_perspective;

  bool use_color_fill;

  bool draw_as_checkerboard;

  void setup();
  void reset();
  void update();
  void draw();

  void setup_camera();
};
