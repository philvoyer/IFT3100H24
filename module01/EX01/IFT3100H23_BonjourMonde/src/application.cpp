// IFT3100H23_BonjourMonde/application.cpp
// Classe principale de l'application.

#include "application.h"

// fonction appelée à l'initialisation de l'application
void Application::setup()
{
  ofSetWindowTitle("Bonjour Monde");

  ofLog() << "<app::setup>";

  renderer.setup();
}

// fonction appelée à chaque mise à jour du rendu graphique de l'application
void Application::draw()
{
  renderer.draw();
}

// fonction appelée quand une touche du clavier est relachée
void Application::keyReleased(int key)
{
  ofLog() << "<app::keyReleased: " << key << ">";

  // sélectionner une nouvelle couleur au hasard
  renderer.select_random_colors();
}

// fonction appelée quand un bouton d'un périphérique de pointage est relâché
void Application::mouseReleased(int x, int y, int button)
{
  ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";

  // sélectionner une nouvelle couleur au hasard
  renderer.select_random_colors();
}

// fonction appelée juste avant de quitter l'application
void Application::exit()
{
  ofLog() << "<app::exit>";
}
