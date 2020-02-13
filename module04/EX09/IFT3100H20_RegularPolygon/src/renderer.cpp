// IFT3100H20_RegularPolygon/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(10);

  // paramètres
  point_diameter = 16;
  side = 3;

  // variable
  mode = "triangle";
}

void Renderer::update()
{
  // déterminer la position du centre du polygone régulier
  polygon_center_x = ofGetWidth() / 2.0f;
  polygon_center_y = ofGetHeight() / 2.0f;

  // configurer l'angle de départ pour le premier sommet du polygone régulier
  angle = ofDegToRad(-90.0f);

  // calculer l'angle qui sépare chaque sommet du polygone
  offset = ofDegToRad(360.0f / side);

  // déterminer le rayon du polygone régulier
  radius = min(ofGetWidth(), ofGetHeight()) / 3.0f;
}

void Renderer::draw()
{
  ofBackgroundGradient(ofColor(191), ofColor(63));

  // 1. dessiner la zone de remplissage du polygone régulier
  ofFill();
  ofSetColor(255);

  // débuter un nouveau polygone régulier
  ofBeginShape();

  // une itération pour chaque sommet du polygone régulier
  for (index = 0; index < side; ++index)
  {
    // calculer la position du sommet
    position_vertex_x = polygon_center_x + cos(angle) * radius;
    position_vertex_y = polygon_center_y + sin(angle) * radius;

    // ajouter un sommet au polygone régulier
    ofSetColor(255);
    ofVertex(position_vertex_x, position_vertex_y);

    // incrémenter l'angle pour le prochain sommet
    angle += offset;
  }

  // terminer et rendre le polygone régulier
  ofEndShape();

  ofSetColor(191);
  ofSetLineWidth(2);

  // 2. dessiner une arête entre chaque sommet et le centre du polygone régulier
  for (index = 0; index < side; ++index)
  {
    // calculer la position du sommet
    position_vertex_x = polygon_center_x + cos(angle) * radius;
    position_vertex_y = polygon_center_y + sin(angle) * radius;

    // ajouter un sommet au polygone régulier
    ofDrawLine(position_vertex_x, position_vertex_y, polygon_center_x, polygon_center_y);

    // incrémenter l'angle pour le prochain sommet
    angle += offset;
  }

  ofSetColor(63);

  // 3. dessiner chaque sommet du polygone régulier
  for (index = 0; index < side; ++index)
  {
    // calculer la position du sommet
    position_vertex_x = polygon_center_x + cos(angle) * radius;
    position_vertex_y = polygon_center_y + sin(angle) * radius;

    // ajouter un sommet au polygone régulier
    ofDrawEllipse(position_vertex_x, position_vertex_y, point_diameter, point_diameter);

    // incrémenter l'angle pour le prochain sommet
    angle += offset;
  }

  // dessiner le centre du polygone régulier
  ofDrawEllipse(polygon_center_x, polygon_center_y, point_diameter, point_diameter);
}
