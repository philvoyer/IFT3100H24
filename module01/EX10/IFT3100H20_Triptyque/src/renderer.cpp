// IFT3100H20_Triptyque/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(0);

  // couleur de l'arrière-plan
  ofSetBackgroundColor(31);

  // mode d'échantillonage des coordonnées de texture
  ofDisableArbTex();

  // définir la valeur de l'espacement vertical et horizontal
  offset_vertical = 32;
  offset_horizontal = 32;

  // définir la résolution des images de destination
  image_width = 256;
  image_height = 256;

  // importer l'image source
  image_source.load("forest.jpg");

  // ajuster la résolution de la fenêtre en fonction de la résolution de l'image source et des espacements
  ofSetWindowShape(
    image_source.getWidth() + offset_horizontal * 4,
    image_source.getHeight() + offset_vertical * 2);

  // copier les pixels de la section de l'image source vers les images de destination
  image_left.cropFrom(image_source, image_width * 0, 0, image_width, image_height);
  image_center.cropFrom(image_source, image_width * 1, 0, image_width, image_height);
  image_right.cropFrom(image_source, image_width * 2, 0, image_width, image_height);

  // chargement du code source des shaders
  shader.load(
    "image_tint_330_vs.glsl",
    "image_tint_330_fs.glsl");
}

void Renderer::draw()
{
  shader.begin();

  shader.setUniformTexture("image", image_left.getTexture(), 1);
  shader.setUniform4f("tint", 1.0f, 0.0f, 0.0f, 1.0f);

  // dessiner l'image de gauche
  image_left.draw(
    offset_horizontal,
    offset_vertical,
    image_width,
    image_height);

  shader.setUniformTexture("image", image_center.getTexture(), 1);
  shader.setUniform4f("tint", 0.0f, 1.0f, 0.0f, 1.0f);

  // dessiner l'image du centre
  image_center.draw(
    image_width * 1 + offset_horizontal * 2,
    offset_vertical,
    image_width,
    image_height);

  shader.setUniformTexture("image", image_right.getTexture(), 1);
  shader.setUniform4f("tint", 0.0f, 0.0f, 1.0f, 1.0f);

  // dessiner l'image de droite
  image_right.draw(
    image_width * 2 + offset_horizontal * 3,
    offset_vertical,
    image_width,
    image_height);

  shader.end();
}
