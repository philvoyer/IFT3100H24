// IFT3100H23_Oscillator/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  // fréquence de rafraichissement du rendu de la fenêtre d'affichage par seconde
  ofSetFrameRate(60);

  // résolution de la fenêtre d'affichage en fonction de l'image
  ofSetWindowShape(512, 512);

  // configurer le niveau de précision des ellipse
  ofSetCircleResolution(64);

  // valeurs d'oscillation initiales
  amplitude_x = 127.0f;
  amplitude_y = 63.0f;
  frequency_x = 3.0f;
  frequency_y = 6.0f;

  // initialisation des couleurs
  color_cpu.set(255, 0, 0, 127);
  color_gpu.set(0, 255, 0, 127);

  // chargement du code source des shaders
  shader.load(
    "vertex_oscillator_330_vs.glsl",
    "vertex_oscillator_330_fs.glsl");
}

void Renderer::update()
{
  // calculer le rayon des cercles en fonction de la résolution
  radius = min(ofGetWidth(), ofGetHeight()) / 8.0f;

  // temps courant en secondes
  time_current = ofGetElapsedTimef();

  // calculer la position du cercle animé par le CPU
  position_x = ofGetWidth() / 2.0f - oscillate(time_current, amplitude_x, frequency_x);
  position_y = ofGetHeight() / 2.0f - oscillate(time_current, amplitude_y, frequency_y);
}

void Renderer::draw()
{
  // couleur des lignes
  ofSetColor(255);

  // dessiner 2 lignes à partir des coins de la fenêtre d'affichage
  ofDrawLine(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
  ofDrawLine(0.0f, ofGetHeight(), ofGetWidth(), 0.0f);

  // désactiver la zone de remplissage
  ofNoFill();

  // dessiner un rectangle
  ofDrawRectangle(ofGetWidth() / 4.0f, ofGetHeight() / 4.0f, ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);

  // activer la zone de remplissage
  ofFill();

  // couleur du cercle fixe
  ofSetColor(0, 0, 255, 127);

  // dessiner le cercle fixe
  ofDrawEllipse(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, radius, radius);

  // couleur du cercle animé pour le CPU
  ofSetColor(color_cpu);

  // dessiner le cercle animé par le CPU
  ofDrawEllipse(position_x, position_y, radius, radius);

  // activer le shader
  shader.begin();

  // couleur du cercle animé par le GPU
  shader.setUniform4f("tint", color_gpu.r / 255.0f, color_gpu.g / 255.0f, color_gpu.b / 255.0f, color_gpu.a / 255.0f);

  // passer au shader la valeur courante des attributs d'oscillation
  shader.setUniform1f("amplitude_x", amplitude_x);
  shader.setUniform1f("amplitude_y", amplitude_y);
  shader.setUniform1f("frequency_x", frequency_x);
  shader.setUniform1f("frequency_y", frequency_y);
  shader.setUniform1f("time", time_current);

  // dessiner le cercle animé par le GPU
  ofDrawEllipse(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f, radius, radius);

  // désactiver le shader
  shader.end();
}

// fonction d'oscillation
float Renderer::oscillate(float time, float amplitude, float frequency)
{
  return amplitude * sin(time * 2.0 * PI / frequency);
}
