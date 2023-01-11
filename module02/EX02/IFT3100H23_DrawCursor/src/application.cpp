// IFT3100H23_DrawCursor/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("curseur");

  ofLog() << "<app::setup>";

  renderer.setup();

  is_verbose = false;
}

void Application::draw()
{
  renderer.draw();
}

// fonction appelée quand la position du curseur change
void Application::mouseMoved(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  if (is_verbose)
    ofLog() << "<app::mouse moved    at: (" << x << ", " << y << ")>";
}

// fonction appelée quand la position du curseur change pendant qu'un bouton d'un périphérique de pointage est appuyé
void Application::mouseDragged(int x, int y, int button)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  if (is_verbose)
    ofLog() << "<app::mouse dragged  at: (" << x << ", " << y << ") button:" << button <<">";
}

// fonction appelée quand un bouton d'un périphérique de pointage est appuyé
void Application::mousePressed(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = true;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  renderer.mouse_press_x = x;
  renderer.mouse_press_y = y;

  ofLog() << "<app::mouse pressed  at: (" << x << ", " << y << ")>";
}

// fonction appelée quand un bouton d'un périphérique de pointage est relâché
void Application::mouseReleased(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = false;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";
}

// fonction appelée quand le curseur entre dans la fenêtre d'affichage
void Application::mouseEntered(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse entered  at: (" << x << ", " << y << ")>";
}

// fonction appelée quand le curseur sort de la fenêtre d'affichage
void Application::mouseExited(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse exited   at: (" << x << ", " << y << ")>";
}

// fonction appelée quand une touche du clavier est relâchée
void Application::keyReleased(int key)
{
  switch (key)
  {
    case 118: // touche v
      is_verbose = !is_verbose;
      ofLog() << "<verbose mode: " << is_verbose << ">";
      break;

    default:
      ofSetBackgroundAuto(!ofGetBackgroundAuto());
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
