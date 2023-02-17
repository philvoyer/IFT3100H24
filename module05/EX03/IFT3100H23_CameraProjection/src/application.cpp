// IFT3100H23_CameraProjection/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  is_key_press_up = false;
  is_key_press_down = false;
  is_key_press_left = false;
  is_key_press_right = false;

  renderer.setup();

  ofSetWindowTitle("camera projection (1234 ↑↓←→) with " + renderer.camera_name);

  gui.setup();

  ui_group_color.setup("color");

  ui_color_picker_background.set("background", ofColor(15, 15, 15), ofColor(0, 0), ofColor(255, 255));
  ui_color_picker_ambient.set("ambient", ofColor(31, 31, 31), ofColor(0, 0), ofColor(255, 255));
  ui_color_picker_diffuse.set("diffuse", ofColor(63, 31, 127), ofColor(0, 0), ofColor(255, 255));

  ui_group_color.add(ui_color_picker_background);
  ui_group_color.add(ui_color_picker_ambient);
  ui_group_color.add(ui_color_picker_diffuse);

  gui.add(&ui_group_color);

  ui_group_camera.setup("camera");

  ui_camera_clip_n.set("near", renderer.camera_clip_n, 0.0001f, 1000.0f);
  ui_camera_clip_f.set("far", renderer.camera_clip_f, 1.0f, 10000.0f);
  ui_camera_fov_h.set("fov", renderer.camera_fov, 0.0f, 180.0f);
  ui_camera_zoom_h.set("zoom", renderer.camera_zoom, 0.0f, 10.0f);

  ui_group_camera.add(ui_camera_clip_n);
  ui_group_camera.add(ui_camera_clip_f);
  ui_group_camera.add(ui_camera_fov_h);
  ui_group_camera.add(ui_camera_zoom_h);

  gui.add(&ui_group_camera);

  font.load("Consolas Bold.ttf", 12, true, true);
}

void Application::update()
{
  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

  if (is_key_press_up)
    renderer.offset_z -= renderer.delta_z * time_elapsed;
  if (is_key_press_down)
    renderer.offset_z += renderer.delta_z * time_elapsed;
  if (is_key_press_left)
    renderer.offset_x -= renderer.delta_x * time_elapsed;
  if (is_key_press_right)
    renderer.offset_x += renderer.delta_x * time_elapsed;

  // ancrage pour le texte dans la fenêtre d'affichage
  ui_offset = ofGetHeight() / 32.0f;
  ui_anchor_x = ofGetWidth() / 32.0f;
  ui_anchor_y = ofGetHeight() - ui_offset;

  // ajustement manuel des couleurs
  renderer.color_background = ui_color_picker_background;
  renderer.color_ambient = ui_color_picker_ambient;
  renderer.color_diffuse = ui_color_picker_diffuse;

  // ajustement manuel du plan d'occlusion avant
  if (renderer.camera_clip_n != ui_camera_clip_n)
  {
    renderer.camera_clip_n = ui_camera_clip_n;
    renderer.camera_state_change = true;
  }

  // ajustement manuel du plan d'occlusion arrière
  if (renderer.camera_clip_f != ui_camera_clip_f)
  {
    renderer.camera_clip_f = ui_camera_clip_f;
    renderer.camera_state_change = true;
  }

  // ajustement manuel du champ de vision
  if (renderer.camera_fov != ui_camera_fov_h)
  {
    renderer.camera_fov = ui_camera_fov_h;

    // recalculer le zoom
    renderer.camera_zoom = renderer.compute_zoom_from_fov(renderer.camera_fov);
    ui_camera_zoom_h = renderer.camera_zoom;

    renderer.camera_state_change = true;
  }

  // ajustement manuel du zoom
  if (renderer.camera_zoom != ui_camera_zoom_h)
  {
    renderer.camera_zoom = ui_camera_zoom_h;

    // recalculer le champ de vision
    renderer.camera_fov = renderer.compute_fov_from_zoom(renderer.camera_zoom);
    ui_camera_fov_h = renderer.camera_fov;

    renderer.camera_state_change = true;
  }

  renderer.update();
}

void Application::draw()
{
  renderer.draw();
  gui.draw();

  glm::mat4 matrix_model_view;
  glm::mat4 matrix_projection;

  if (renderer.camera_is_active)
  {
    matrix_model_view = renderer.camera.getModelViewMatrix();
    matrix_projection = renderer.camera.getProjectionMatrix();
  }
  else
  {
    matrix_model_view = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    matrix_projection = ofGetCurrentMatrix(OF_MATRIX_PROJECTION);
  }

  std::string str_matrix_model_view_row_1 = "[ ";
  str_matrix_model_view_row_1 += string_format_float_precision(matrix_model_view[0][0], 2) + "\t";
  str_matrix_model_view_row_1 += string_format_float_precision(matrix_model_view[1][0], 2) + "\t";
  str_matrix_model_view_row_1 += string_format_float_precision(matrix_model_view[2][0], 2) + "\t";
  str_matrix_model_view_row_1 += string_format_float_precision(matrix_model_view[3][0], 2);
  str_matrix_model_view_row_1 += " ]";

  std::string str_matrix_model_view_row_2 = "[ ";
  str_matrix_model_view_row_2 += string_format_float_precision(matrix_model_view[0][1], 2) + "\t";
  str_matrix_model_view_row_2 += string_format_float_precision(matrix_model_view[1][1], 2) + "\t";
  str_matrix_model_view_row_2 += string_format_float_precision(matrix_model_view[2][1], 2) + "\t";
  str_matrix_model_view_row_2 += string_format_float_precision(matrix_model_view[3][1], 2);
  str_matrix_model_view_row_2 += " ]";

  std::string str_matrix_model_view_row_3 = "[ ";
  str_matrix_model_view_row_3 += string_format_float_precision(matrix_model_view[0][2], 2) + "\t";
  str_matrix_model_view_row_3 += string_format_float_precision(matrix_model_view[1][2], 2) + "\t";
  str_matrix_model_view_row_3 += string_format_float_precision(matrix_model_view[2][2], 2) + "\t";
  str_matrix_model_view_row_3 += string_format_float_precision(matrix_model_view[3][2], 2);
  str_matrix_model_view_row_3 += " ]";

  std::string str_matrix_model_view_row_4 = "[ ";
  str_matrix_model_view_row_4 += string_format_float_precision(matrix_model_view[0][3], 2) + "\t";
  str_matrix_model_view_row_4 += string_format_float_precision(matrix_model_view[1][3], 2) + "\t";
  str_matrix_model_view_row_4 += string_format_float_precision(matrix_model_view[2][3], 2) + "\t";
  str_matrix_model_view_row_4 += string_format_float_precision(matrix_model_view[3][3], 2);
  str_matrix_model_view_row_4 += " ]";

  std::string str_matrix_projection_row_1 = "[ ";
  str_matrix_projection_row_1 += string_format_float_precision(matrix_projection[0][0], 2) + "\t";
  str_matrix_projection_row_1 += string_format_float_precision(matrix_projection[1][0], 2) + "\t";
  str_matrix_projection_row_1 += string_format_float_precision(matrix_projection[2][0], 2) + "\t";
  str_matrix_projection_row_1 += string_format_float_precision(matrix_projection[3][0], 2);
  str_matrix_projection_row_1 += " ]";

  std::string str_matrix_projection_row_2 = "[ ";
  str_matrix_projection_row_2 += string_format_float_precision(matrix_projection[0][1], 2) + "\t";
  str_matrix_projection_row_2 += string_format_float_precision(matrix_projection[1][1], 2) + "\t";
  str_matrix_projection_row_2 += string_format_float_precision(matrix_projection[2][1], 2) + "\t";
  str_matrix_projection_row_2 += string_format_float_precision(matrix_projection[3][1], 2);
  str_matrix_projection_row_2 += " ]";

  std::string str_matrix_projection_row_3 = "[ ";
  str_matrix_projection_row_3 += string_format_float_precision(matrix_projection[0][2], 2) + "\t";
  str_matrix_projection_row_3 += string_format_float_precision(matrix_projection[1][2], 2) + "\t";
  str_matrix_projection_row_3 += string_format_float_precision(matrix_projection[2][2], 2) + "\t";
  str_matrix_projection_row_3 += string_format_float_precision(matrix_projection[3][2], 2);
  str_matrix_projection_row_3 += " ]";

  std::string str_matrix_projection_row_4 = "[ ";
  str_matrix_projection_row_4 += string_format_float_precision(matrix_projection[0][3], 2) + "\t";
  str_matrix_projection_row_4 += string_format_float_precision(matrix_projection[1][3], 2) + "\t";
  str_matrix_projection_row_4 += string_format_float_precision(matrix_projection[2][3], 2) + "\t";
  str_matrix_projection_row_4 += string_format_float_precision(matrix_projection[3][3], 2);
  str_matrix_projection_row_4 += " ]";

  font.drawString("matrix model view", ui_anchor_x, ui_anchor_y - ui_offset * 10);
  font.drawString(str_matrix_model_view_row_1, ui_anchor_x, ui_anchor_y - ui_offset * 9);
  font.drawString(str_matrix_model_view_row_2, ui_anchor_x, ui_anchor_y - ui_offset * 8);
  font.drawString(str_matrix_model_view_row_3, ui_anchor_x, ui_anchor_y - ui_offset * 7);
  font.drawString(str_matrix_model_view_row_4, ui_anchor_x, ui_anchor_y - ui_offset * 6);

  font.drawString("matrix projection (perspective)", ui_anchor_x, ui_anchor_y - ui_offset * 4);
  font.drawString(str_matrix_projection_row_1, ui_anchor_x, ui_anchor_y - ui_offset * 3);
  font.drawString(str_matrix_projection_row_2, ui_anchor_x, ui_anchor_y - ui_offset * 2);
  font.drawString(str_matrix_projection_row_3, ui_anchor_x, ui_anchor_y - ui_offset * 1);
  font.drawString(str_matrix_projection_row_4, ui_anchor_x, ui_anchor_y - ui_offset * 0);
}

void Application::keyPressed(int key)
{
  switch (key)
  {
    case OF_KEY_LEFT: // key ←
      is_key_press_left = true;
      break;

    case OF_KEY_UP: // key ↑
      is_key_press_up = true;
      break;

    case OF_KEY_RIGHT: // key →
      is_key_press_right = true;
      break;

    case OF_KEY_DOWN: // key ↓
      is_key_press_down = true;
      break;

    default:
      break;
  }
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49:  // touche 1
      renderer.shader = renderer.shader_lambert;
      ofLog() << "<select shader: lambert>";
      break;

    case 50:  // touche 2
      renderer.shader = renderer.shader_normal;
      ofLog() << "<select shader: normal>";
      break;

    case 51:  // touche 3
      renderer.shader = renderer.shader_depth;
      ofLog() << "<select shader: depth>";
      break;

    case 52:  // touche 4
      renderer.camera_is_active = !renderer.camera_is_active;
      renderer.camera_name = renderer.camera_is_active ? "ofCamera" : "default camera";
      ofSetWindowTitle("camera projection (1234 ↑↓←→) with " + renderer.camera_name);
      ofLog() << "<select camera: " << renderer.camera_name << ">";
      break;

    case OF_KEY_LEFT: // key ←
      is_key_press_left = false;
      break;

    case OF_KEY_UP: // key ↑
      is_key_press_up = false;
      break;

    case OF_KEY_RIGHT: // key →
      is_key_press_right = false;
      break;

    case OF_KEY_DOWN: // key ↓
      is_key_press_down = false;
      break;

    case ' ':
      renderer.camera_current_state_log();
      break;

    default:
      renderer.use_rotation = !renderer.use_rotation;
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}

std::string Application::string_format_float_precision(float value, int precision)
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << value;
  return oss.str();
}

std::string Application::string_format_int_pad(int value, size_t size, char pad)
{
  std::string str = std::to_string(value);
  int count = size - std::min(size, str.size());
  str.insert(0, count, pad);
  return str;
}
