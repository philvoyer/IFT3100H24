// IFT3100H20_DrawZone/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("zone de sélection");

  ofLog() << "<app::setup>";

  renderer.setup();

  is_verbose = false;
}

void Application::draw()
{
  renderer.draw();
}

void Application::mouseMoved(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  if (is_verbose)
    ofLog() << "<app::mouse moved    at: (" << x << ", " << y << ")>";
}

void Application::mouseDragged(int x, int y, int button)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  if (is_verbose)
    ofLog() << "<app::mouse dragged  at: (" << x << ", " << y << ") button:" << button <<">";
}

void Application::mousePressed(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = true;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  renderer.mouse_press_x = x;
  renderer.mouse_press_y = y;

  ofLog() << "<app::mouse pressed  at: (" << x << ", " << y << ")>";
}

void Application::mouseReleased(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = false;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";
}

void Application::mouseEntered(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse entered  at: (" << x << ", " << y << ")>";
}

void Application::mouseExited(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse exited   at: (" << x << ", " << y << ")>";
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 118: // touche v
      is_verbose = !is_verbose;
      ofLog() << "<verbose mode: " << is_verbose << ">";
      break;

    default:
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
