// IFT3100H19_CameraTransform/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  is_key_press_up = false;
  is_key_press_down = false;
  is_key_press_left = false;
  is_key_press_right = false;

  is_key_press_a = false;
  is_key_press_d = false;
  is_key_press_e = false;
  is_key_press_h = false;
  is_key_press_i = false;
  is_key_press_j = false;
  is_key_press_k = false;
  is_key_press_q = false;
  is_key_press_s = false;
  is_key_press_u = false;
  is_key_press_w = false;
  is_key_press_x = false;
  is_key_press_y = false;
  is_key_press_z = false;

  renderer.setup();
}

void Application::update()
{
  ofSetWindowTitle("camera " + renderer.camera_name + " " + renderer.camera_projection + " (1-6 ↑↓←→ wasdqe uhjkyi zx op fgcvb)");

  renderer.is_camera_move_forward = is_key_press_up || is_key_press_w;
  renderer.is_camera_move_backward = is_key_press_down || is_key_press_s;

  renderer.is_camera_move_left = is_key_press_left || is_key_press_a;
  renderer.is_camera_move_right = is_key_press_right || is_key_press_d;

  renderer.is_camera_move_up = is_key_press_q;
  renderer.is_camera_move_down = is_key_press_e;

  renderer.is_camera_tilt_up = is_key_press_j;
  renderer.is_camera_tilt_down = is_key_press_u;

  renderer.is_camera_pan_left = is_key_press_h;
  renderer.is_camera_pan_right = is_key_press_k;

  renderer.is_camera_roll_left = is_key_press_y;
  renderer.is_camera_roll_right = is_key_press_i;

  renderer.is_camera_fov_narrow = is_key_press_z;
  renderer.is_camera_fov_wide = is_key_press_x;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();
}

void Application::keyPressed(int key)
{
  switch (key)
  {
    case 97: // touche a
      is_key_press_a = true;
      break;

    case 100: // touche d
      is_key_press_d = true;
      break;

    case 101: // touche e
      is_key_press_e = true;
      break;

    case 104: // touche h
      is_key_press_h = true;
      break;

    case 105: // touche i
      is_key_press_i = true;
      break;

    case 106: // touche j
      is_key_press_j = true;
      break;

    case 107: // touche k
      is_key_press_k = true;
      break;

    case 113: // touche q
      is_key_press_q = true;
      break;

    case 115: // touche s
      is_key_press_s = true;
      break;

    case 117: // touche u
      is_key_press_u = true;
      break;

    case 119: // touche w
      is_key_press_w = true;
      break;

    case 120: // touche x
      is_key_press_x = true;
      break;

    case 121: // touche y
      is_key_press_y = true;
      break;

    case 122: // touche z
      is_key_press_z = true;
      break;

    case OF_KEY_LEFT: // touche ←
      is_key_press_left = true;
      break;

    case OF_KEY_UP: // touche ↑
      is_key_press_up = true;
      break;

    case OF_KEY_RIGHT: // touche →
      is_key_press_right = true;
      break;

    case OF_KEY_DOWN: // touche ↓
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
    case 49: // touche 1
      renderer.camera_active = Camera::front;
      renderer.setup_camera();
      break;

    case 50: // touche 2
      renderer.camera_active = Camera::back;
      renderer.setup_camera();
      break;

    case 51: // touche 3
      renderer.camera_active = Camera::left;
      renderer.setup_camera();
      break;

    case 52: // touche 4
      renderer.camera_active = Camera::right;
      renderer.setup_camera();
      break;

    case 53: // touche 5
      renderer.camera_active = Camera::top;
      renderer.setup_camera();
      break;

    case 54: // touche 6
      renderer.camera_active = Camera::down;
      renderer.setup_camera();
      break;

    case 97: // touche a
      is_key_press_a = false;
      break;

    case 98: // touche b
      renderer.is_visible_box = !renderer.is_visible_box;
      ofLog() << "<toggle box:" << renderer.is_visible_box << ">";
      break;

    case 99: // touche c
      renderer.draw_as_checkerboard = !renderer.draw_as_checkerboard;
      ofLog() << "<toggle checkerboard:" << renderer.draw_as_checkerboard << ">";
      break;

    case 100: // touche d
      is_key_press_d = false;
      break;

    case 101: // touche e
      is_key_press_e = false;
      break;

    case 102: // touche f
      renderer.use_color_fill = !renderer.use_color_fill;
      renderer.use_color_fill ? ofFill() : ofNoFill();
      ofLog() << "<color fill:" <<  renderer.use_color_fill << ">";
      break;

    case 103: // touche g
      renderer.is_visible_grid = !renderer.is_visible_grid;
      ofLog() << "<toggle grid:" << renderer.is_visible_grid << ">";
      break;

    case 104: // touche h
      is_key_press_h = false;
      break;

    case 105: // touche i
      is_key_press_i = false;
      break;

    case 106: // touche j
      is_key_press_j = false;
      break;

    case 107: // touche k
      is_key_press_k = false;
      break;

    case 111: // touche o
      renderer.is_camera_perspective = false;
      renderer.setup_camera();
      ofLog() << "<orthographic projection>";
      break;

    case 112: // touche p
      renderer.is_camera_perspective = true;
      renderer.setup_camera();
      ofLog() << "<perpective projection>";
      break;

    case 113: // touche q
      is_key_press_q = false;
      break;

    case 114: // touche r
      renderer.reset();
      break;

    case 115: // touche s
      is_key_press_s = false;
      break;

    case 116: // touche t
      renderer.is_visible_text = !renderer.is_visible_text;
      ofLog() << "<toggle text:" << renderer.is_visible_text << ">";
      renderer.is_visible_camera = !renderer.is_visible_camera;
      ofLog() << "<toggle camera gizmo:" << renderer.is_visible_camera << ">";
      break;

    case 117: // touche u
      is_key_press_u = false;
      break;

    case 118: // touche v
      renderer.is_visible_axes = !renderer.is_visible_axes;
      ofLog() << "<toggle axes gizmo:" << renderer.is_visible_axes << ">";
      break;

    case 119: // touche w
      is_key_press_w = false;
      break;

    case 120: // touche x
      is_key_press_x = false;
      ofLog() << "<fov:" << renderer.camera_fov << ">";
      break;

    case 121: // touche y
      is_key_press_y = false;
      break;

    case 122: // touche z
      ofLog() << "<fov:" << renderer.camera_fov << ">";
      is_key_press_z = false;
      break;

    case OF_KEY_LEFT: // touche ←
      is_key_press_left = false;
      break;

    case OF_KEY_UP: // touche ↑
      is_key_press_up = false;
      break;

    case OF_KEY_RIGHT: // touche →
      is_key_press_right = false;
      break;

    case OF_KEY_DOWN: // touche ↓
      is_key_press_down = false;
      break;

    case ' ':
      renderer.reset();

    default:
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
