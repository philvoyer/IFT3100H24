// IFT3100H19_PBR/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(0);
  ofDisableArbTex();
  ofSetLogLevel(OF_LOG_VERBOSE);
  ofSetSphereResolution(32);

  // chargement d'un modèle 3D
  teapot.loadModel("geometry/teapot.obj");

  // désactiver le matériau par défaut du modèle
  teapot.disableMaterials();

  // charger, compiler et linker les sources des shaders
  shader_pbr.load(
    "shader/pbr_330_vs.glsl",
    "shader/pbr_330_fs.glsl");

  // charger les textures du matériau
  texture_diffuse.load("texture/metal_plate_diffuse_1k.jpg");
  texture_metallic.load("texture/metal_plate_metallic_1k.jpg");
  texture_roughness.load("texture/metal_plate_roughness_1k.jpg");
  texture_occlusion.load("texture/metal_plate_ao_1k.jpg");

  // paramètres des textures du matériau
  texture_diffuse.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
  texture_metallic.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
  texture_roughness.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
  texture_occlusion.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
}

void Renderer::reset()
{
  // paramètres de transformation
  speed_motion = 150.0f;
  speed_rotation = 50.0f;
  initial_x = 0.0f;
  initial_y = -100.0f;
  rotation_y = 0.0f;
  scale_cube = 110.0f;
  scale_sphere = 90.0f;
  scale_teapot = 0.618f;

  // positions initiales des maillages géométriques
  position_cube.set(-ofGetWidth() * (1.0f / 4.0f), 0.0f, 0.0f);
  position_sphere.set(0.0f, 0.0f, 0.0f);
  position_teapot.set(ofGetWidth() * (1.0f / 4.0f), 50.0f, 0.0f);

  // paramètres du matériau
  material_color_ambient = ofColor(63, 63, 63);
  material_color_diffuse = ofColor(255, 255, 255);
  material_color_specular = ofColor(255, 255, 255);

  material_metallic = 0.5f;
  material_roughness = 0.5f;
  material_occlusion = 1.0f;
  material_brightness = 1.0f;

  material_fresnel_ior = glm::vec3(0.04f, 0.04f, 0.04f);

  // paramètres de la lumière
  light_color = ofColor(255, 255, 255);
  light_intensity = 10.0f;
  light_motion = true;

  // paramètres de mappage tonal
  tone_mapping_exposure = 1.0f;
  tone_mapping_toggle = true;

  // initialisation des variables
  offset_x = initial_x;
  offset_z = initial_y;

  delta_x = speed_motion;
  delta_y = speed_rotation;
  delta_z = speed_motion;

  // position initiale de la caméra
  offset_x = initial_x;
  offset_z = initial_y;

  ofLog() << "<reset>";
}

void Renderer::update()
{
  // centre de la fenêtre d'affichage
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;

  if (light_motion)
  {
    // transformer la lumière
    light.setGlobalPosition(
      ofMap(ofGetMouseX() / (float) ofGetWidth(), 0.0f, 1.0f, -center_x, center_y),
      ofMap(ofGetMouseY() / (float) ofGetHeight(), 0.0f, 1.0f, -center_y, center_y),
      -offset_z * 1.5f);
  }

  // passer les attributs uniformes au shader de sommets
  shader = &shader_pbr;
  shader->begin();

  shader->setUniform3f("material_color_ambient", material_color_ambient.r/255.0f, material_color_ambient.g/255.0f, material_color_ambient.b/255.0f);
  shader->setUniform3f("material_color_diffuse", material_color_diffuse.r/255.0f, material_color_diffuse.g/255.0f, material_color_diffuse.b/255.0f);
  shader->setUniform3f("material_color_specular", material_color_specular.r/255.0f, material_color_specular.g/255.0f, material_color_specular.b/255.0f);

  shader->setUniform1f("material_brightness", material_brightness);
  shader->setUniform1f("material_metallic", material_metallic);
  shader->setUniform1f("material_roughness", material_roughness);
  shader->setUniform1f("material_occlusion", material_occlusion);

  shader->setUniform3f("material_fresnel_ior", material_fresnel_ior);

  shader->setUniformTexture("texture_diffuse", texture_diffuse.getTexture(), 1);
  shader->setUniformTexture("texture_metallic", texture_metallic.getTexture(), 2);
  shader->setUniformTexture("texture_roughness", texture_roughness.getTexture(), 3);
  shader->setUniformTexture("texture_occlusion", texture_occlusion.getTexture(), 4);

  shader->setUniform1f("light_intensity", light_intensity);
  shader->setUniform3f("light_color", light_color.r/255.0f, light_color.g/255.0f, light_color.b/255.0f);
  shader->setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

  shader->setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
  shader->setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
  shader->setUniform1i("tone_mapping_toggle", tone_mapping_toggle);

  shader->end();
}

void Renderer::draw()
{
  // activer l'occlusion en profondeur
  ofEnableDepthTest();

  // activer l'éclairage dynamique
  ofEnableLighting();

  // activer la lumière dynamique
  light.enable();

  // activer le shader
  shader->begin();

  ofPushMatrix();

    // transformer l'origine de la scène au milieu de la fenêtre d'affichage
    ofTranslate(center_x + offset_x, center_y, offset_z);

    // rotation globale
    ofRotateDeg(rotation_y, 0.0f, 1.0f, 0.0f);

    ofPushMatrix();

      // positionnner le cube
      ofTranslate(
        position_cube.x,
        position_cube.y,
        position_cube.z);

      // rotation locale
      ofRotateDeg(45.0f, 1.0f, 0.0f, 0.0f);

      // dessiner un cube
      ofDrawBox(0.0f, 0.0f, 0.0f, scale_cube);

    ofPopMatrix();

    ofPushMatrix();

      // positionner la sphère
      ofTranslate(
        position_sphere.x,
        position_sphere.y,
        position_sphere.z);

      // dessiner une sphère
      ofDrawSphere(0.0f, 0.0f, 0.0f, scale_sphere);

    ofPopMatrix();

    ofPushMatrix();

      // positionner le teapot
      teapot.setPosition(
        position_teapot.x + 25.0f,
        position_teapot.y + 15.0f,
        position_teapot.z);

      // dimension du teapot
      teapot.setScale(
        scale_teapot,
        scale_teapot,
        scale_teapot);

      // dessiner un teapot
      teapot.draw(OF_MESH_FILL);

    ofPopMatrix();

  ofPopMatrix();

  // désactiver le shader
  shader->end();

  // désactiver la lumière
  light.disable();

  // désactiver l'éclairage dynamique
  ofDisableLighting();

  // désactiver l'occlusion en profondeur
  ofDisableDepthTest();
}
