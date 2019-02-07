// IFT3100H19_Origin/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
}

void Renderer::update()
{
  // calculer les coordonnées du centre du framebuffer
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;
}

void Renderer::draw()
{
  // rendre l'origine de la scène avant transformation du système de coordonnées
  draw_locator(10.0f);

  // copier la matrice de transformation courante sur le dessus de la pile
  ofPushMatrix();

  // transformer l'origine de la scène au milieu de la fenêtre d'affichage
  ofTranslate(center_x, center_y, 0.0f);

  // rendre l'origine de la scène après transformation du système de coordonnées
  draw_locator(10.0f);

  // revenir à la matrice de transformation précédente dans la pile
  ofPopMatrix();

  // rendre l'origine de la scène après transformation du système de coordonnées
  draw_locator(10.0f);
}

// fonction qui dessine un localisateur à l'origine de la scène
void Renderer::draw_locator(float scale)
{
  ofSetLineWidth(4);
  ofSetColor(127);
  ofFill();
  ofPushMatrix();
  ofScale(scale, scale);
  node.setPosition(0.0f, 0.0f, 0.0f);
  node.draw();
  ofPopMatrix();
}
