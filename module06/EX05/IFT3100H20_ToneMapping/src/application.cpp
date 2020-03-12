// IFT3100H20_ToneMapping/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("correction de couleur");

  ofLog() << "<app::setup>";

  renderer.setup();

  slider_exposure.set("exposure", renderer.tone_mapping_exposure, 0.0f, 5.0f);
  slider_gamma.set("gamma", renderer.tone_mapping_gamma, 0.0f, 5.0f);

  if (renderer.tone_mapping_toggle)
    toggle_tone_mapping.set("aces filmic", true);
  else
    toggle_tone_mapping.set("reinhard", false);

  gui.setup();

  group_tone_mapping.setup("tone mapping");

  group_tone_mapping.add(slider_exposure);
  group_tone_mapping.add(slider_gamma);
  group_tone_mapping.add(toggle_tone_mapping);

  gui.add(&group_tone_mapping);
}

void Application::update()
{
  renderer.tone_mapping_exposure = slider_exposure;
  renderer.tone_mapping_gamma = slider_gamma;
  renderer.tone_mapping_toggle = toggle_tone_mapping;

  if (renderer.tone_mapping_toggle)
    toggle_tone_mapping.set("aces filmic", true);
  else
    toggle_tone_mapping.set("reinhard", false);
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
