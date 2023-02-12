// IFT3100H23_TriangleSoup/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  // paramètres du programme
  triangle_count = 2500;
  triangle_radius = 16.0f;
  soup_proportion = 0.4f;
  bowl_or_ball = true;
  speed = 100;

  // paramètres de rendu
  ofSetFrameRate(60);
  ofEnableDepthTest();

  // initialisation des variables
  offset_x = 0;
  offset_y = 0;
  offset_z = 0;

  delta_x = speed;
  delta_y = speed;
  delta_z = speed;

  triangle_buffer_size = triangle_count;
  triangle_buffer_head = 0;

  // allocation d'un espace mémoire suffisament grand pour contenir les données de l'ensemble des triangles de la soupe
  soup = (Triangle*) std::malloc(triangle_buffer_size * sizeof(Triangle));

  reset();
}

// fonction qui initialise la scène
void Renderer::reset()
{
  // calculer les coordonnées du centre du framebuffer
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;

  // déterminer le rayon de la soupe en fonction des dimensions de la fenêtre
  soup_radius = std::min(ofGetWidth(), ofGetHeight()) * soup_proportion;

  // distribuer les triangles dans l'espace de la scène
  dispatch_random_triangle(triangle_count, soup_radius);

  ofLog() << "<reset>";
}

// fonction qui distribue les triangles dans un hémisphère
void Renderer::dispatch_random_triangle(int count, float range)
{
  // variable temporaire
  float scale;

  // validations
  if (count <= 0 || range <= 0.0f || count > triangle_buffer_size)
    return;

  // configurer le nombre de triangles
  triangle_buffer_head = count;

  for (int index = 0; index < triangle_buffer_head; ++index)
  {
    // déterminer une position au hasard
    vector_origin.x = ofRandom(-1.0f, 1.0f);
    vector_origin.y = ofRandom(-1.0f, 1.0f);
    vector_origin.z = ofRandom(-1.0f, 1.0f);

    // normaliser la position
    vector_origin.normalize();

    // ramener la position dans une hémisphère
    if (bowl_or_ball)
      vector_origin.z = std::abs(vector_origin.z) * -1.0f;

    // proportion de la soupe
    vector_origin *= range;

    // déterminer des valeurs de position aléatoires pour les trois sommets du triangle
    vector_position1.x = vector_origin.x + ofRandom(-triangle_radius, triangle_radius);
    vector_position1.y = vector_origin.y + ofRandom(-triangle_radius, triangle_radius);
    vector_position1.z = vector_origin.z + ofRandom(-triangle_radius, triangle_radius);

    vector_position2.x = vector_origin.x + ofRandom(-triangle_radius, triangle_radius);
    vector_position2.y = vector_origin.y + ofRandom(-triangle_radius, triangle_radius);
    vector_position2.z = vector_origin.z + ofRandom(-triangle_radius, triangle_radius);

    vector_position3.x = vector_origin.x + ofRandom(-triangle_radius, triangle_radius);
    vector_position3.y = vector_origin.y + ofRandom(-triangle_radius, triangle_radius);
    vector_position3.z = vector_origin.z + ofRandom(-triangle_radius, triangle_radius);

    // déterminer une couleur RGB au hasard
    vector_color.r = ofRandom(0, 255);
    vector_color.g = ofRandom(0, 255);
    vector_color.b = ofRandom(0, 255);
    vector_color.a = 255;

    // configurer les attributs de transformation du triangle
    soup[index].position1[0] = vector_position1.x;
    soup[index].position1[1] = vector_position1.y;
    soup[index].position1[2] = vector_position1.z;

    soup[index].position2[0] = vector_position2.x;
    soup[index].position2[1] = vector_position2.y;
    soup[index].position2[2] = vector_position2.z;

    soup[index].position3[0] = vector_position3.x;
    soup[index].position3[1] = vector_position3.y;
    soup[index].position3[2] = vector_position3.z;

    // configurer les attributs de couleur du triangle
    soup[index].color[0] = vector_color.r;
    soup[index].color[1] = vector_color.g;
    soup[index].color[2] = vector_color.b;
    soup[index].color[3] = vector_color.a;
  }
}

void Renderer::draw()
{
  ofBackgroundGradient(ofColor(191), ofColor(63));

  ofPushMatrix();

  ofTranslate(center_x + offset_x, center_y, offset_z);

  // dessiner la soupe de triangles
  draw_soup();

  draw_locator(3.0f);

  ofPopMatrix();
}

// fonction de rendu de la soupe aux triangles
void Renderer::draw_soup()
{
  ofPushMatrix();

  // rotation en Y de la scène
  ofRotateDeg(offset_y, 0.0f, 1.0f, 0.0f);

  // légère rotation en Z de la soupe
  ofRotateDeg(ofGetFrameNum() * 0.1f, 0.0f, 0.0f, 1.0f);

  // dessiner les triangles
  for (int index = 0; index < triangle_buffer_head; ++index)
    draw_triangle(index);

  ofPopMatrix();
}

// fonction qui dessine un des triangles de la soupe
void Renderer::draw_triangle(int index)
{
  ofFill();

  ofSetColor(
    soup[index].color[0],
    soup[index].color[1],
    soup[index].color[2],
    soup[index].color[3]);

  vector_position1.x = soup[index].position1[0];
  vector_position1.y = soup[index].position1[1];
  vector_position1.z = soup[index].position1[2];

  vector_position2.x = soup[index].position2[0];
  vector_position2.y = soup[index].position2[1];
  vector_position2.z = soup[index].position2[2];

  vector_position3.x = soup[index].position3[0];
  vector_position3.y = soup[index].position3[1];
  vector_position3.z = soup[index].position3[2];

  ofDrawTriangle(
    vector_position1,
    vector_position2,
    vector_position3);
}

void Renderer::draw_locator(float scale)
{
  ofFill();
  ofSetColor(191);
  ofPushMatrix();
  ofScale(scale, scale, scale);
  node.setPosition(0.0f, 0.0f, 0.0f);
  node.draw();
  ofPopMatrix();
}

Renderer::~Renderer()
{
  std::free(soup);
}
