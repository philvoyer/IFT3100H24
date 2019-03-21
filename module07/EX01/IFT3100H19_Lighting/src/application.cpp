// IFT3100H19_Lighting/application.cpp
// Classe principale de l'application.

#include "application.h"

Application::Application()
{
  is_key_press_up = false;
  is_key_press_down = false;
  is_key_press_left = false;
  is_key_press_right = false;
}

void Application::setup()
{
  ofLog() << "<app::setup>";

  ofSetWindowTitle("éclairage dynamique (1-4 ↑↓←→ s r)");

  renderer.setup();
}

void Application::update()
{
  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

  if (is_key_press_up)
    renderer.offset_z += renderer.delta_z * time_elapsed;
  if (is_key_press_down)
    renderer.offset_z -= renderer.delta_z * time_elapsed;
  if (is_key_press_left)
    renderer.offset_x += renderer.delta_x * time_elapsed;
  if (is_key_press_right)
    renderer.offset_x -= renderer.delta_x * time_elapsed;

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
    case 49: // key 1
      renderer.is_active_ligh_ambient = !renderer.is_active_ligh_ambient;
      ofLog() << "<light ambient: " << renderer.is_active_ligh_ambient << ">";
      break;

    case 50: // key 2
      renderer.is_active_light_directional = !renderer.is_active_light_directional;
      ofLog() << "<light directional: " << renderer.is_active_light_directional << ">";
      break;

    case 51: // key 3
      renderer.is_active_light_point = !renderer.is_active_light_point;
      ofLog() << "<light point: " << renderer.is_active_light_point << ">";
      break;

    case 52: // key 4
      renderer.is_active_light_spot = !renderer.is_active_light_spot;
      ofLog() << "<light spot: " << renderer.is_active_light_spot << ">";
      break;

    case 114: // key r
      renderer.reset();
      break;

    case 115: // key s
      renderer.use_smooth_lighting = !renderer.use_smooth_lighting;
      ofSetSmoothLighting(renderer.use_smooth_lighting);
      ofLog() << "<smooth lighting: " << renderer.use_smooth_lighting << ">";
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
