// IFT3100H23_RegularPolygon/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  renderer.setup();
}

void Application::update()
{
  ofSetWindowTitle("polygone régulier : " + renderer.mode + "(1-9)");
  renderer.update();
}

void Application::draw()
{
  renderer.draw();
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49:  // touche 1
      renderer.side = 3;
      renderer.mode = "triangle";
      break;

    case 50:  // touche 2
      renderer.side = 4;
      renderer.mode = "carré";
      break;

    case 51:  // touche 3
      renderer.side = 5;
      renderer.mode = "pentagone";
      break;

    case 52:  // touche 4
      renderer.side = 6;
      renderer.mode = "hexagone";
      break;

    case 53:  // touche 5
      renderer.side = 7;
      renderer.mode = "heptagone";
      break;

    case 54:  // touche 6
      renderer.side = 8;
      renderer.mode = "octogone";
      break;

    case 55:  // touche 7
      renderer.side = 9;
      renderer.mode = "nonagone";
      break;

    case 56:  // touche 8
      renderer.side = 10;
      renderer.mode = "décagone";
      break;

    case 57:  // touche 9
      renderer.side = 11;
      renderer.mode = "hendécagone";
      break;

    case 48:  // touche 0
      renderer.side = 12;
      renderer.mode = "dodécagone";
      break;

    default:
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
