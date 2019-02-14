// IFT3100H19_ShaderLambert/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetWindowShape(512, 512);
  ofSetBackgroundColor(15);
  ofSetLogLevel(OF_LOG_VERBOSE);

  // paramètres
  scale_teapot = 1.5f;
  use_rotation = true;

  // chargement du modèle
  teapot.loadModel("teapot.obj");

  // désactiver le matériau par défaut du modèle
  teapot.disableMaterials();

  // chargement du shader
  shader.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");

  // initialisation de l'interface graphique
  gui.setup();
  gui.add(color_picker.set("diffuse color", ofColor(174, 223, 134), ofColor(0, 0), ofColor(255, 255)));
}

void Renderer::update()
{
  // position au centre de la fenêtre d'affichage
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;

  // transformation du teapot
  teapot.setScale(scale_teapot, scale_teapot, scale_teapot);
  teapot.setPosition(center_x, center_y + 90, 0);

  if (use_rotation)
    teapot.setRotation(0, ofGetFrameNum() * 0.3f, 0.0f, 1.0f, 0.0f);

  // configuration de la lumière
  light.setPointLight();
  light.setDiffuseColor(255);
  light.setGlobalPosition(center_x, center_y, 255.0f);

  // passer les attributs uniformes du shader
  shader.begin();
  shader.setUniform3f("color_ambient",  0.1f, 0.1f, 0.1f);
  shader.setUniform3f("color_diffuse",  color_picker->r / 255.0f, color_picker->g / 255.0f, color_picker->b / 255.0f);
  shader.setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

  shader.end();
}

void Renderer::draw()
{
  // activer l'occlusion en profondeur
  ofEnableDepthTest();

  // activer l'éclairage dynamique
  ofEnableLighting();

  // activer la lumière
  light.enable();

  // activer le shader
  shader.begin();

  // dessiner le teapot
  teapot.draw(OF_MESH_FILL);

  // désactiver le shader
  shader.end();

  // désactiver la lumière
  light.disable();

  // désactiver l'éclairage dynamique
  ofDisableLighting();

  // désactiver l'occlusion en profondeur
  ofDisableDepthTest();

  // dessiner l'interface graphique
  gui.draw();
}
