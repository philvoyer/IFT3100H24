// IFT3100H21_ImageImport/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("importation d'une image");

  ofLog() << "<app::setup>";

  renderer.setup();
}

void Application::draw()
{
  renderer.draw();
}

void Application::windowResized(int w, int h)
{
  ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
}

// fonction invoquée quand une sélection de fichiers est déposée sur la fenêtre de l'application
void Application::dragEvent(ofDragInfo dragInfo)
{
  ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
          << " at : " << dragInfo.position << ">";

  // importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
  renderer.image.load(dragInfo.files.at(0));

  // redimensionner la fenêtre selon la résolution de l'image
  if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
    ofSetWindowShape(renderer.image.getWidth(), renderer.image.getHeight());
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
