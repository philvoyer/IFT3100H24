// IFT3100H21_ImageExport/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("exportation d'une image (espace)");

  ofLog() << "<app::setup>";

  renderer.setup();
}

void Application::draw()
{
  renderer.draw();
}

// fonction appelée quand une touche du clavier est relachée
void Application::keyReleased(int key)
{
  ofLog() << "<app::keyReleased: " << key << ">";

  // valider si la touche du clavier est la barre d'espacement (spacebar)
  if (key == ' ')
    renderer.image_export("render", "png");
  else
  {
    renderer.filter = !renderer.filter;

    if (renderer.filter)
      renderer.shader = renderer.shader_invert;
    else
      renderer.shader = renderer.shader_passthrough;
  }
}

void Application::windowResized(int w, int h)
{
  ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
}

void Application::dragEvent(ofDragInfo dragInfo)
{
  ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
  << " at : " << dragInfo.position << ">";

  renderer.image.load(dragInfo.files.at(0));

  if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
    ofSetWindowShape(renderer.image.getWidth(), renderer.image.getHeight());
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
