// IFT3100H23_DrawCursor/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(191);

  mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

  is_mouse_button_pressed = false;
}

void Renderer::draw()
{
  // épaisseur du trait
  ofSetLineWidth(2);

  // afficher le curseur
  draw_cursor(mouse_current_x, mouse_current_y);
}

// fonction qui dessine un curseur
void Renderer::draw_cursor(float x, float y) const
{
  // paramètres de dessin
  float length = 10.0f;
  float offset = 5.0f;

  // dessiner le curseur en rouge si un des boutons du périphérique de pointage est appuyé
  if (is_mouse_button_pressed)
    ofSetColor(255, 0, 0);
  else
    ofSetColor(0);

  // dessiner la forme vectorielle
  ofDrawLine(x + offset, y, x + offset + length, y);
  ofDrawLine(x - offset, y, x - offset - length, y);
  ofDrawLine(x, y + offset, x, y + offset + length);
  ofDrawLine(x, y - offset, x, y - offset - length);
}
