// IFT3100H19_ShaderLambert/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
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

void Application::keyReleased(int key)
{
  renderer.use_rotation = !renderer.use_rotation;
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
