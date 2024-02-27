// IFT3100H24_LambertTeapot/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetWindowShape(512, 512);
  ofSetLogLevel(OF_LOG_VERBOSE);

  // paramètres
  scale_teapot = 1.5f;
  rotation_speed = 0.3f;
  use_rotation = true;

  // chargement du modèle
  teapot.loadModel("teapot.obj");

  // désactiver le matériau par défaut du modèle
  teapot.disableMaterials();

  // chargement du shader
  shader_lambert.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
  shader_normal.load("draw_normal_330_vs.glsl", "draw_normal_330_fs.glsl");

  // sélectionner le shader courant
  shader = shader_lambert;
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
    teapot.setRotation(0, ofGetFrameNum() * rotation_speed, 0.0f, 1.0f, 0.0f);

  // configuration de la lumière
  light.setPointLight();
  light.setDiffuseColor(255);
  light.setGlobalPosition(center_x, center_y, 255.0f);
}

void Renderer::draw()
{
  // couleur de l'arrière-plan
  ofSetBackgroundColor(color_background.r, color_background.g, color_background.b);

  // activer l'occlusion en profondeur
  ofEnableDepthTest();

  // activer l'éclairage dynamique
  ofEnableLighting();

  // activer la lumière
  light.enable();

  // activer le shader
  shader.begin();

  // passer les attributs uniformes du shader
  shader.setUniform3f("color_ambient",  color_ambient.r / 255.0f, color_ambient.g / 255.0f, color_ambient.b / 255.0f);
  shader.setUniform3f("color_diffuse",  color_diffuse.r / 255.0f, color_diffuse.g / 255.0f, color_diffuse.b / 255.0f);
  shader.setUniform3f("light_position", light.getGlobalPosition());

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
}
