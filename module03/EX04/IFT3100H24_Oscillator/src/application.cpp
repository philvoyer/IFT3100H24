// IFT3100H24_Oscillator/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("oscillateur");

  ofLog() << "<app::setup>";

  renderer.setup();

  slider_amplitude_x.set("amplitude x", renderer.amplitude_x, 0.0f, 256.0f);
  slider_amplitude_y.set("amplitude y", renderer.amplitude_y, 0.0f, 256.0f);
  slider_frequency_x.set("frequency x", renderer.frequency_x, 0.0f, 10.0f);
  slider_frequency_y.set("frequency y", renderer.frequency_y, 0.0f, 10.0f);

  gui.setup("attributs");

  gui.add(slider_amplitude_x);
  gui.add(slider_amplitude_y);
  gui.add(slider_frequency_x);
  gui.add(slider_frequency_y);
}

void Application::update()
{
  renderer.amplitude_x = slider_amplitude_x;
  renderer.amplitude_y = slider_amplitude_y;
  renderer.frequency_x = slider_frequency_x;
  renderer.frequency_y = slider_frequency_y;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();

  gui.draw();
}
