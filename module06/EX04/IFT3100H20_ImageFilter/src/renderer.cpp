 // IFT3100H20_ImageFilter/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableArbTex();

  tint.set(255, 255, 255);
  mix_factor = 0.618f;
  offset_vertical = 32;
  offset_horizontal = 32;

  image.load("teapot.jpg");

  ofSetWindowShape(
    image.getWidth() * 2 + offset_horizontal * 3,
    image.getHeight() * 1 + offset_vertical * 2);

  shader.load("image_filter_330_vs.glsl", "image_filter_330_fs.glsl");
}

void Renderer::draw()
{
  // dessiner l'image sur la première moitié de la surface de la fenêtre
  image.draw(offset_horizontal, offset_vertical, image.getWidth(), image.getHeight());

  // activer le filtre
  shader.begin();

  // passer les attributs uniformes au shader
  shader.setUniformTexture("image", image.getTexture(), 1);
  shader.setUniform3f("tint", tint.r / 255.0f, tint.g / 255.0f, tint.b / 255.0f);
  shader.setUniform1f("factor", mix_factor);

  // dessiner l'image sur la seconde moitié de la surface de la fenêtre
  image.draw(image.getWidth() + offset_horizontal * 2, offset_vertical, image.getWidth(), image.getHeight());

 // désactiver le filtre
  shader.end();
}
