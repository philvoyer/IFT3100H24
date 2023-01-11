// IFT3100H23_BackgroundColor/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("couleur d'arrière-plan (1-6)");

  ofLog() << "<app::setup>";

  renderer.setup();
}

void Application::draw()
{
  renderer.draw();
}

void Application::keyReleased(int key)
{
  switch(key)
  {
    case 49: // touche 1
      renderer.clear_mode = ClearMode::none;
      ofLog() << "<mode: none>";
      break;

    case 50: // touche 2
      renderer.clear_mode = ClearMode::black;
      ofLog() << "<mode: black>";
      break;

    case 51: // touche 3
      renderer.clear_mode = ClearMode::white;
      ofLog() << "<mode: white>";
      break;

    case 52: // touche 4
      renderer.clear_mode = ClearMode::gray;
      ofLog() << "<mode: gray>";
      break;

    case 53: // touche 5
      renderer.clear_mode = ClearMode::color;
      ofLog() << "<mode: color>";
      break;

    case 54: // touche 6
    default: // et autre
      renderer.clear_mode = ClearMode::random;
      ofLog() << "<mode: random>";
      break;
  }

  renderer.has_changed = true;
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
