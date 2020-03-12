// IFT3100H20_ImageFilter/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("filtre d'image (teinte)");

  ofLog() << "<app::setup>";

  renderer.setup();

  gui.setup();
  gui.add(color_picker.set("teinte", renderer.tint, ofColor(0, 0), ofColor(255, 255)));
  gui.add(slider.set("mix", renderer.mix_factor, 0.0f, 1.0f));
}

void Application::update()
{
  renderer.tint = color_picker;
  renderer.mix_factor = slider;
}

void Application::draw()
{
  renderer.draw();

  gui.draw();
}

void Application::dragEvent(ofDragInfo dragInfo)
{
  ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
          << " at : " << dragInfo.position << ">";

  renderer.image.load(dragInfo.files.at(0));

  if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
    ofSetWindowShape(renderer.image.getWidth() * 2, renderer.image.getHeight());
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
