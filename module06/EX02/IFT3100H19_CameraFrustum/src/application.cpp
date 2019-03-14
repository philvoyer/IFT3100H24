// IFT3100H19_CameraFrustum/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("frustum de vision d'une caméra");

  renderer.setup();

  ofLog() << "<app::setup>";
}

void Application::update()
{
  renderer.update();
}

void Application::draw()
{
  renderer.draw();
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
