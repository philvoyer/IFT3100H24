// IFT3100H21_DrawZone/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(191);

  mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

  radius = 4.0f;

  is_mouse_button_pressed = false;
}

void Renderer::draw()
{
  // afficher la zone de sélection
  if (is_mouse_button_pressed)
  {
    // dessiner la zone de sélection
    draw_zone(
      mouse_press_x,
      mouse_press_y,
      mouse_current_x,
      mouse_current_y);
  }

  // dessiner le curseur
  draw_cursor(mouse_current_x, mouse_current_y);
}

// fonction qui dessine une zone rectangulaire
void Renderer::draw_zone(float x1, float y1, float x2, float y2) const
{
  float x2_clamp = min(max(0.0f, x2), (float) ofGetWidth());
  float y2_clamp = min(max(0.0f, y2), (float) ofGetHeight());

  ofSetLineWidth(radius);
  ofSetColor(255);
  ofNoFill();
  ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
  ofFill();
  ofDrawEllipse(x1, y1, radius, radius);
  ofDrawEllipse(x1, y2_clamp, radius, radius);
  ofDrawEllipse(x2_clamp, y1, radius, radius);
  ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

// fonction qui dessine un curseur
void Renderer::draw_cursor(float x, float y) const
{
  float length = 10.0f;
  float offset = 5.0f;

  ofSetLineWidth(2);
  ofSetColor(31);
  ofDrawLine(x + offset, y, x + offset + length, y);
  ofDrawLine(x - offset, y, x - offset - length, y);
  ofDrawLine(x, y + offset, x, y + offset + length);
  ofDrawLine(x, y - offset, x, y - offset - length);
}
