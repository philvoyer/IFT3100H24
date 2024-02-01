// IFT3100H24_BonjourMonde/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  // fréquence de rafraîchissement du rendu de la fenêtre d'affichage par seconde
  ofSetFrameRate(60);

  // résolution de la fenêtre d'affichage en fonction de l'image
  ofSetWindowShape(512, 512);

  // configurer le niveau de précision des ellipse
  ofSetCircleResolution(64);

  // chargement du code source des shaders
  shader.load(
    "flat_tint_330_vs.glsl",
    "flat_tint_330_fs.glsl");

  // sélectionner une nouvelle couleur au hasard
  select_random_colors();
}

void Renderer::draw()
{
  // effacer la fenêtre d'affichage et remplir avec la couleur d'arrière-plan
  ofClear(color_background.r, color_background.g, color_background.b);

  // activer le shader
  shader.begin();

  // passer la couleur de la teinte RGBA au shader sous forme d'un attribut uniforme (avec composantes normalisées)
  shader.setUniform4f("tint", color_tint.r / 255.0f, color_tint.g / 255.0f, color_tint.b / 255.0f, 1.0f);

  // dessiner 2 lignes à partir des coins de la fenêtre d'affichage
  ofDrawLine(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
  ofDrawLine(0.0f, ofGetHeight(), ofGetWidth(), 0.0f);

  // activer la zone de remplissage
  ofFill();

  // dessiner une ellipse
  ofDrawEllipse(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, ofGetWidth() / 8.0f, ofGetHeight() / 8.0f);

  // désactiver la zone de remplissage
  ofNoFill();

  // dessiner un rectangle
  ofDrawRectangle(ofGetWidth() / 4.0f, ofGetHeight() / 4.0f, ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);

  // désactiver le shader
  shader.end();
}

// fonction qui permet de sélectionner une nouvelle couleur aléatoire
void Renderer::select_random_colors()
{
  // choisir une nouvelle valeur aléatoire par chaque composante de la couleur
  color_random.set(ofRandom(255), ofRandom(255), ofRandom(255));

  // utiliser la couleur aléatoire comme couleur d'arrière-plan
  color_background.set(color_random.r, color_random.g, color_random.b);

  // utiliser l'inverse de couleur aléatoire comme couleur de tinte
  color_tint.set(255 - color_random.r, 255 - color_random.g, 255 - color_random.b);

  ofLog() << "<renderer::select random colors (" << color_random << ")>";
}
