// IFT3100H23_LambertTeapot/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("teapot avec shader de Lambert");

  renderer.setup();

  gui.setup();

  gui.add(color_picker_background.set("background color", ofColor(15, 15, 15), ofColor(0, 0), ofColor(255, 255)));
  gui.add(color_picker_ambient.set("ambient color", ofColor(63, 63, 63), ofColor(0, 0), ofColor(255, 255)));
  gui.add(color_picker_diffuse.set("diffuse color", ofColor(174, 223, 134), ofColor(0, 0), ofColor(255, 255)));
}

void Application::update()
{
  renderer.color_background = color_picker_background;
  renderer.color_ambient = color_picker_ambient;
  renderer.color_diffuse = color_picker_diffuse;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();
  gui.draw();
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49:  // touche 1
      renderer.shader = renderer.shader_lambert;
      ofLog() << "<select shader: lambert>";
      break;

    case 50:  // touche 2
      renderer.shader = renderer.shader_normal;
      ofLog() << "<select shader: normal>";
      break;

    default:
      renderer.use_rotation = !renderer.use_rotation;
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
