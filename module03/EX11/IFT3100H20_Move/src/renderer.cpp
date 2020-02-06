// IFT3100H20_Move/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);

  speed = 100.0f;

  delta_x = speed;
  delta_z = speed;

  reset();
}

void Renderer::update()
{
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;
}

void Renderer::draw()
{
  // copier la matrice de transformation courante sur le dessus de la pile
  ofPushMatrix();

  // transformer l'origine de la scène
  ofTranslate(center_x + offset_x, center_y, offset_z);

  // dessiner l'origine de la scène
  draw_locator(10.0f);

  // revenir à la matrice de transformation précédente dans la pile
  ofPopMatrix();
}

void Renderer::reset()
{
  offset_x = 0.0f;
  offset_z = 0.0f;

  ofLog() << "<reset>";
}

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
