// IFT3100H21_HelloTriangle/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(1);

  point_radius = 8.0f;
}

void Renderer::update()
{
  framebuffer_width = ofGetWidth();
  framebuffer_height = ofGetHeight();

  // position aléatoire pour chaque sommet
  vertex1_x = ofRandom(0, framebuffer_width);
  vertex1_y = ofRandom(0, framebuffer_height);
  vertex2_x = ofRandom(0, framebuffer_width);
  vertex2_y = ofRandom(0, framebuffer_height);
  vertex3_x = ofRandom(0, framebuffer_width);
  vertex3_y = ofRandom(0, framebuffer_height);

  // couleur aléatoire pour la zone de remplissage
  color_r = ofRandom(0, 256);
  color_g = ofRandom(0, 256);
  color_b = ofRandom(0, 256);

  ofLog() << setprecision(4) << "<triangle: v1:("
          << vertex1_x << ", " << vertex1_y << ") v2:("
          << vertex2_x << ", " << vertex2_y << ") v3:("
          << vertex3_x << ", " << vertex3_y << ") color: >"
          << color_r << ", " << color_g << ", " << color_b << ">";
}

void Renderer::draw()
{
  ofBackgroundGradient(ofColor(191), ofColor(63));

  // dessiner le triangle
  ofSetColor(color_r, color_g, color_b);
  ofDrawTriangle(
    vertex1_x, vertex1_y,
    vertex2_x, vertex2_y,
    vertex3_x, vertex3_y);

  // dessiner les sommets
  ofSetColor(31);
  ofDrawEllipse(vertex1_x, vertex1_y, point_radius, point_radius);
  ofDrawEllipse(vertex2_x, vertex2_y, point_radius, point_radius);
  ofDrawEllipse(vertex3_x, vertex3_y, point_radius, point_radius);
}
