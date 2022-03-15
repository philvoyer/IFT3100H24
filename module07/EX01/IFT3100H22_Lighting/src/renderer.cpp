// IFT3100H22_Lighting/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofEnableDepthTest();
  ofSetSphereResolution(32);

  // paramètres
  camera_offset = 350.0f;
  speed_motion = 150.0f;
  oscillation_frequency = 7500.0f;
  oscillation_amplitude = 45.0;
  initial_x = 0.0f;
  initial_z = -100.0f;
  scale_cube = 100.0f;
  scale_sphere = 80.0f;
  scale_teapot = 0.618f;

  // chargement du modèle 3D
  teapot.loadModel("teapot.obj");

  // initialisation de la scène
  reset();
}

void Renderer::reset()
{
  // initialisation des variables
  offset_x = initial_x;
  offset_z = initial_z;

  delta_x = speed_motion;
  delta_z = speed_motion;

  use_smooth_lighting = true;

  is_active_ligh_ambient = true;
  is_active_light_directional = true;
  is_active_light_point = true;
  is_active_light_spot = true;

  // centre du framebuffer
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;

  // déterminer la position des géométries
  position_cube.set(-ofGetWidth() * (1.0f / 4.0f), 0.0f, 0.0f);
  position_sphere.set(0.0f, 0.0f, 0.0f);
  position_teapot.set(ofGetWidth() * (1.0f / 4.0f), 50.0f, 0.0f);

  // configurer le matériau du cube
  material_cube.setAmbientColor(ofColor(63, 63, 63));
  material_cube.setDiffuseColor(ofColor(127, 0, 0));
  material_cube.setEmissiveColor(ofColor( 31, 0, 0));
  material_cube.setSpecularColor(ofColor(127, 127, 127));
  material_cube.setShininess(16.0f);

  // configurer le matériau de la sphère
  material_sphere.setAmbientColor(ofColor(63, 63, 63));
  material_sphere.setDiffuseColor(ofColor(191, 63, 0));
  material_sphere.setEmissiveColor(ofColor(0, 31, 0));
  material_sphere.setSpecularColor(ofColor(255, 255, 64));
  material_sphere.setShininess(8.0f);

  // configurer le matériau du teapot
  material_teapot.setAmbientColor(ofColor(63, 63, 63));
  material_teapot.setDiffuseColor(ofColor(63, 0, 63));
  material_teapot.setEmissiveColor(ofColor(0, 0, 31));
  material_teapot.setSpecularColor(ofColor(191, 191, 191));
  material_teapot.setShininess(8.0f);

  // configurer la lumière ambiante
  light_ambient.set(127, 127, 127);

  // configurer la lumière directionnelle
  light_directional.setDiffuseColor(ofColor(31, 255, 31));
  light_directional.setSpecularColor(ofColor(191, 191, 191));
  light_directional.setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
  light_directional.setDirectional();

  // configurer la lumière ponctuelle
  light_point.setDiffuseColor(ofColor(255, 255, 255));
  light_point.setSpecularColor(ofColor(191, 191, 191));
  light_point.setPointLight();

  // configurer la lumière projecteur
  light_spot.setDiffuseColor(ofColor(191, 191, 191));
  light_spot.setSpecularColor(ofColor(191, 191, 191));
  light_spot.setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
  light_spot.setSpotConcentration(2);
  light_spot.setSpotlightCutOff(30);
  light_spot.setSpotlight();

  ofLog() << "<reset>";
}

void Renderer::update()
{
  ofPushMatrix();

  if (is_active_light_directional)
  {
    // transformer la lumière directionnelle
    orientation_directional.makeRotate(int(ofGetElapsedTimeMillis() * 0.1f) % 360, 0, 1, 0);

    light_directional.setPosition(center_x, center_y + 60, camera_offset * 0.75f);
    light_directional.setOrientation(orientation_directional);
  }

  if (is_active_light_point)
  {
    // transformer la lumière ponctuelle
    light_point.setPosition(ofGetMouseX(), ofGetMouseY(), camera_offset * 0.75f);
  }

  if (is_active_light_spot)
  {
    // transformer la lumière projecteur
    oscillation = oscillate(ofGetElapsedTimeMillis(), oscillation_frequency, oscillation_amplitude);

    orientation_spot.makeRotate(30.0f, ofVec3f(1, 0, 0), oscillation, ofVec3f(0, 1, 0), 0.0f, ofVec3f(0, 0, 1));

    light_spot.setOrientation(orientation_spot);

    light_spot.setPosition (center_x, center_y - 75.0f, camera_offset * 0.75f);
  }

  ofPopMatrix();
}

void Renderer::draw()
{
  ofBackground(0);

  ofPushMatrix();

    // afficher un repère visuel pour les lumières
    if (is_active_light_point)
      light_point.draw();
    if (is_active_light_directional)
      light_directional.draw();
    if (is_active_light_spot)
      light_spot.draw();

  ofPopMatrix();

  // activer l'éclairage dynamique
  ofEnableLighting();

  // activer les lumières
  lighting_on();

  ofPushMatrix();

    // transformer l'origine de la scène au milieu de la fenêtre d'affichage
    ofTranslate(center_x + offset_x, center_y, offset_z);

    // légère rotation de la scène
    ofRotateDeg(ofGetFrameNum() * 0.25f, 0, 1, 0);

    ofPushMatrix();

      // position
      ofTranslate(
        position_cube.x,
        position_cube.y,
        position_cube.z);

      // rotation locale
      ofRotateDeg(ofGetFrameNum() * 1.0f, 0, 1, 0);

      // activer le matériau
      material_cube.begin();

      // dessiner un cube
      ofDrawBox(0, 0, 0, scale_cube);

      // désactiver le matériau
      material_cube.end();

    ofPopMatrix();

    ofPushMatrix();

      // position
      ofTranslate(
        position_sphere.x,
        position_sphere.y,
        position_sphere.z);

      // rotation locale
      ofRotateDeg(ofGetFrameNum() * 1.0f, 0, 1, 0);

      // activer le matériau
      material_sphere.begin();

      // dessiner une sphère
      ofDrawSphere(0, 0, 0, scale_sphere);

      // désactiver le matériau
      material_sphere.end();

    ofPopMatrix();

    ofPushMatrix();

      // position
      teapot.setPosition(
        position_teapot.x,
        position_teapot.y + 15,
        position_teapot.z);

      // rotation locale
      teapot.setRotation(0, ofGetFrameNum() * -1.0f, 0, 1, 0);

      // dimension
      teapot.setScale(
        scale_teapot,
        scale_teapot,
        scale_teapot);

      // désactiver le matériau par défaut du modèle
      teapot.disableMaterials();

      // activer le matériau
      material_teapot.begin();

      // dessiner un teapot
      teapot.draw(OF_MESH_FILL);

      // désactiver le matériau
      material_teapot.end();
    ofPopMatrix();

  ofPopMatrix();

  // désactiver les lumières
  lighting_off();

  // désactiver l'éclairage dynamique
  ofDisableLighting();
}

// désactivation des lumières dynamiques
void Renderer::lighting_on()
{
  if (is_active_ligh_ambient)
    ofSetGlobalAmbientColor(light_ambient);
  else
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));

  if (is_active_light_directional)
    light_directional.enable();

  if (is_active_light_point)
    light_point.enable();

  if (is_active_light_spot)
    light_spot.enable();
}

// activation des lumières dynamiques
void Renderer::lighting_off()
{
  ofSetGlobalAmbientColor(ofColor(0, 0, 0));
  light_directional.disable();
  light_point.disable();
  light_spot.disable();
}

// fonction d'oscillation
float Renderer::oscillate(float time, float frequency, float amplitude)
{
  return sinf(time * 2.0f * PI / frequency) * amplitude;
}
