// IFT3100H20_EquilateralTriangle/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(1);

  ofSetCircleResolution(64);

  point_diameter = 16.0f;

  update();

  ofLog() << setprecision(4) << "<triangle: " <<
  "v1:("  << vertex1_x << ", " << vertex1_y << ") " <<
  "v2:("  << vertex2_x << ", " << vertex2_y << ") " <<
  "v3:("  << vertex3_x << ", " << vertex3_y << ") " <<
  "ri:"   << triangle_innercircle_radius  << " " <<
  "rc:"   << triangle_circumcircle_radius << " " <<
  "edge:" << triangle_edge_diameter << " " <<
  "alti:" << triangle_altitude << " " <<
  "peri:" << triangle_perimeter << " " <<
  "area:" << (int)triangle_area << ">";
}

void Renderer::update()
{
  // calculer la position du centre de la fenêtre d'affichage
  viewport_center_x = ofGetWidth() / 2.0f;
  viewport_center_y = ofGetHeight() / 2.0f;

  // calculer la position du centre du triangle
  triangle_center_x = viewport_center_x;
  triangle_center_y = viewport_center_y;

  // calculer la longueur de la moitié d'une arête du triangle
  triangle_edge_diameter_half = min(ofGetWidth(), ofGetHeight()) / 3.0f;

  // calculer la longueur des arêtes du triangle
  triangle_edge_diameter = triangle_edge_diameter_half * 2.0f;

  // calculer les rayons du cercle intérieur et extérieur du triangle
  triangle_innercircle_radius =  triangle_edge_diameter * sqrt(3.0f) / 6.0f;
  triangle_circumcircle_radius = triangle_edge_diameter * sqrt(3.0f) / 3.0f;

  // calculer l'altitude du triangle
  triangle_altitude = triangle_edge_diameter_half * sqrt(3.0f);

  // calculer le périmètre de la surface du triangle
  triangle_perimeter = triangle_edge_diameter * 3.0f;

  // calculer l'aire de la surface du triangle
  triangle_area = triangle_edge_diameter * triangle_edge_diameter * (sqrt(3.0f) / 4.0f);

  // calculer la position du point d'intersection de la ligne médiane du premier sommet avec l'arête opposée du triangle
  triangle_origin_x = viewport_center_x;
  triangle_origin_y = viewport_center_y + triangle_innercircle_radius;

  // calculer la position des 3 sommets du triangle
  vertex1_x = triangle_origin_x;
  vertex1_y = triangle_origin_y - triangle_altitude;
  vertex2_x = triangle_origin_x + triangle_edge_diameter_half;
  vertex2_y = triangle_origin_y;
  vertex3_x = triangle_origin_x - triangle_edge_diameter_half;
  vertex3_y = triangle_origin_y;
}

void Renderer::draw()
{
  ofBackgroundGradient(ofColor(191), ofColor(63));

  // dessiner une grille sur le plan XY
  ofDrawGrid(max(ofGetWidth(), ofGetHeight()) / 8.0f, 8, false, false, false, true);

  // dessiner la zone de remplissage du triangle
  ofFill();
  ofSetColor(255);
  ofDrawTriangle(
    vertex1_x, vertex1_y,
    vertex2_x, vertex2_y,
    vertex3_x, vertex3_y);

  // dessiner les cercles internes et externes du triangle
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(191);
  ofDrawEllipse(
    viewport_center_x,
    viewport_center_y,
    triangle_innercircle_radius * 2,
    triangle_innercircle_radius * 2);
  ofDrawEllipse(
    viewport_center_x,
    viewport_center_y,
    triangle_circumcircle_radius * 2,
    triangle_circumcircle_radius * 2);

  // dessiner la ligne de contour du triangle
  ofNoFill();
  ofSetColor(31);
  ofSetLineWidth(3);
  ofDrawTriangle(
    vertex1_x, vertex1_y,
    vertex2_x, vertex2_y,
    vertex3_x, vertex3_y);

  // dessiner les trois sommets du triangle dans l'ordre
  ofFill();
  ofSetColor(191, 0, 0);
  ofDrawEllipse(vertex1_x, vertex1_y, point_diameter, point_diameter);
  ofSetColor(0, 191, 0);
  ofDrawEllipse(vertex2_x, vertex2_y, point_diameter, point_diameter);
  ofSetColor(0, 0, 191);
  ofDrawEllipse(vertex3_x, vertex3_y, point_diameter, point_diameter);

  // dessiner le centre du triangle
  ofSetColor(63);
  ofDrawEllipse(triangle_center_x, triangle_center_y, point_diameter, point_diameter);

  // dessiner le point d'intersection de la ligne médiane du premier sommet avec l'arête opposée du triangle
  ofSetColor(191);
  ofDrawEllipse(triangle_origin_x, triangle_origin_y, point_diameter, point_diameter);
}
