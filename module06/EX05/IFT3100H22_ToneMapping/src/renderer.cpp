 // IFT3100H22_ToneMapping/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofDisableArbTex();

  tone_mapping_exposure = 1.0f;
  tone_mapping_gamma = 2.2f;
  tone_mapping_toggle = true;

  offset_vertical = 32;
  offset_horizontal = 32;

  image.load("teapot.jpg");

  ofSetWindowShape(
    image.getWidth() * 2 + offset_horizontal * 3,
    image.getHeight() * 1 + offset_vertical * 2);

  shader.load("tone_mapping_330_vs.glsl", "tone_mapping_330_fs.glsl");
}

void Renderer::draw()
{
  // dessiner l'image sur la première moitié de la surface de la fenêtre
  image.draw(offset_horizontal, offset_vertical, image.getWidth(), image.getHeight());

  // activer le filtre
  shader.begin();

  // passer les attributs uniformes au shader
  shader.setUniformTexture("image", image.getTexture(), 1);

  shader.setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
  shader.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
  shader.setUniform1i("tone_mapping_toggle", tone_mapping_toggle);

  // dessiner l'image sur la seconde moitié de la surface de la fenêtre
  image.draw(image.getWidth() + offset_horizontal * 2, offset_vertical, image.getWidth(), image.getHeight());

 // désactiver le filtre
  shader.end();
}
