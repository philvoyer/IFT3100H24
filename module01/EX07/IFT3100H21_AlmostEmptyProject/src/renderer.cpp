// IFT3100H21_AlmostEmptyProject/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

// fonction d'initialisation
void Renderer::setup()
{
  // fréquence de rafraichissement du rendu de la fenêtre d'affichage par seconde
  ofSetFrameRate(60);
}

// fonction de mise à jour
void Renderer::update()
{
  // temps courant en secondes
  time_current = ofGetElapsedTimef();

  // le temps écoulé depuis le dernier frame en secondes
  time_elapsed = time_current - time_last;

  // le temps courant sera le temps précédent du prochain frame
  time_last = time_current;

  // trace des données temporelles dans la console
  ofLog() << std::setprecision(2) << "<frame: " << ofGetFrameNum() << " time current: " << time_current << " time elapsed: " << time_elapsed << " fps: " << 1.0 / time_elapsed << ">";
}

// fonction de rendu
void Renderer::draw()
{
  // couleur d'arrière-plan en niveau de gris en fonction du numéro de frame courant.
  ofClear(ofGetFrameNum() % 255);
}
