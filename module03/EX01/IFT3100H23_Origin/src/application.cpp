// IFT3100H23_Origin/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  ofSetWindowTitle("origine");

  renderer.setup();
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
