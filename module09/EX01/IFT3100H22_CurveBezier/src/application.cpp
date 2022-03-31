// IFT3100H22_CurveBezier/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  is_key_press_up = false;
  is_key_press_down = false;
  is_key_press_left = false;
  is_key_press_right = false;

  renderer.setup();
}

void Application::update()
{
  ofSetWindowTitle("courbe " + renderer.curve_name + " (↑↓←→ 1-6 r)");

  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

  if (is_key_press_up)
    renderer.selected_ctrl_point->y -= renderer.delta_y * time_elapsed;
  if (is_key_press_down)
    renderer.selected_ctrl_point->y += renderer.delta_y * time_elapsed;
  if (is_key_press_left)
    renderer.selected_ctrl_point->x -= renderer.delta_x * time_elapsed;
  if (is_key_press_right)
    renderer.selected_ctrl_point->x += renderer.delta_x * time_elapsed;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();
}

void Application::mouseReleased(int x, int y, int button)
{
  renderer.reset();
}

void Application::keyPressed(int key)
{
  switch (key)
  {
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
    case 48: // touche 0
      ofLog() << "<0>";
      break;

    case 49: // touche 1
      renderer.selected_ctrl_point = &renderer.ctrl_point1;
      ofLog() << "<select control point 1>";
      break;

    case 50: // touche 2
      renderer.selected_ctrl_point = &renderer.ctrl_point2;
      ofLog() << "<select control point 2>";
      break;

    case 51: // touche 3
      renderer.selected_ctrl_point = &renderer.ctrl_point3;
      ofLog() << "<select control point 3>";
      break;

    case 52: // touche 4
      renderer.selected_ctrl_point = &renderer.ctrl_point4;
      ofLog() << "<select control point 4>";
      break;

    case 53: // touche 5
      ofLog() << "<select curve type : bezier quadratic>";
      renderer.curve_type = CurveType::bezier_quadratic;
      renderer.reset();
      break;

    case 54: // touche 6
      ofLog() << "<select curve type : bezier cubic>";
      renderer.curve_type = CurveType::bezier_cubic;
      renderer.reset();
      break;

    case 55: // touche 7
      ofLog() << "<select interpolation type : lerp>";
      renderer.interpolation_type = InterpolationType::lerp;
      break;

    case 56: // touche 8
      ofLog() << "<select interpolation type : smoothstep>";
      renderer.interpolation_type = InterpolationType::smoothstep;
      break;

    case 114: // touche r
      renderer.reset();
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

    case ' ' : // touche spacebar
      renderer.isAnimationActive = !renderer.isAnimationActive;
      break;

    default:
      break;
  }
}

void Application::windowResized(int w, int h)
{
  renderer.reset();

  ofLog() << "<app::windowResized: (" << w << ", " << h << ")>";
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
