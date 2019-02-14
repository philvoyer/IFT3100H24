// IFT3100H19_Teapot/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  ofEnableDepthTest();
  ofEnableLighting();

  // paramètres du programme
  mesh_render_mode = MeshRenderMode::fill;

  teapot_count = 100;

  speed = 100;

  light.setAmbientColor(ofColor(0, 255, 0));
  light.setDiffuseColor(ofColor(255, 255, 255));
  light.setPosition(0.0f, 0.0f, 1000.0f);
  light.enable();

  // initialisation des variables
  offset_x = 0;
  offset_z = 0;

  delta_x = speed;
  delta_z = speed;

  is_flip_axis_y = false;

  is_active_translation = true;
  is_active_rotation = true;
  is_active_proportion = true;

  locator_buffer_head = 0;

  // allocation d'un espace mémoire suffisamment grand pour contenir les données de l'ensemble des localisateurs de teapot
  locators = (Locator*) std::malloc(teapot_count * sizeof(Locator));

  // chargement du modèle 3D en mémoire
  teapot.loadModel("teapot.obj");

  reset();
}

void Renderer::update()
{
  // calculer les coordonnées du centre du framebuffer
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;
}

void Renderer::draw()
{
  ofFill();
  ofSetLineWidth(1.0f);
  ofSetColor(127);

  ofPushMatrix();

  ofScale(1.0f, is_flip_axis_y ? -1.0f : 1.0f);

  ofTranslate(center_x + offset_x, is_flip_axis_y ? -center_y : center_y, offset_z);

  ofRotateDeg(ofGetFrameNum() * 0.1f, 0.0f, 1.0f, 0.0f);

  for (int index = 0; index < locator_buffer_head; ++index)
  {
    ofPushMatrix();

    if (is_active_translation)
    {
      vector_position.x = locators[index].position[0];
      vector_position.y = locators[index].position[1];
      vector_position.z = locators[index].position[2];
    }
    else
    {
      vector_position.x = 0.0f;
      vector_position.y = 0.0f;
      vector_position.z = 0.0f;
    }

    node.setPosition(
      vector_position.x,
      vector_position.y,
      vector_position.z);

    teapot.setPosition(
      vector_position.x,
      vector_position.y,
      vector_position.z);

    if (is_active_rotation)
    {
      vector_rotation.x = locators[index].rotation[0];
      vector_rotation.y = locators[index].rotation[1];
      vector_rotation.z = locators[index].rotation[2];
    }
    else
    {
      vector_rotation.x = 0.0f;
      vector_rotation.y = 0.0f;
      vector_rotation.z = 0.0f;
    }

    node.setOrientation(vector_rotation);
    teapot.setRotation(0.0f, vector_rotation.y, 0.0f, 1.0f, 0.0f);

    if (is_active_proportion)
    {
      vector_proportion.x = locators[index].proportion[0];
      vector_proportion.y = locators[index].proportion[1];
      vector_proportion.z = locators[index].proportion[2];
    }
    else
    {
      vector_proportion.x = 1.0f;
      vector_proportion.y = 1.0f;
      vector_proportion.z = 1.0f;
    }

    node.setScale(
      vector_proportion.x,
      vector_proportion.y,
      vector_proportion.z);

    teapot.setScale(
      vector_proportion.x,
      vector_proportion.y,
      vector_proportion.z);

    node.draw();

    // dessiner une instance du teapot
    switch (mesh_render_mode)
    {
      case MeshRenderMode::fill:
        teapot.draw(OF_MESH_FILL);
        break;

      case MeshRenderMode::wireframe:
        teapot.draw(OF_MESH_WIREFRAME);
        break;

      case MeshRenderMode::vertex:
        teapot.draw(OF_MESH_POINTS);
        break;
    }

    ofPopMatrix();
  }

  // dessiner l'origine de la scène
  draw_locator(1.0f);

  ofPopMatrix();
}

void Renderer::reset()
{
  // distribuer les localisateurs dans l'espace visible de la scène
  dispatch_random_locator(teapot_count, min(ofGetWidth() * 0.6f, ofGetHeight() * 0.6f));

  ofLog() << "<reset>";
}

// fonction qui distribue les localisateurs dans un espace cubique
void Renderer::dispatch_random_locator(int count, float range)
{
  float scale;

  if (count <= 0 || range <= 0 || count > teapot_count)
    return;

  float halfRange = range / 2.0f;

  locator_buffer_head = count;

  for (int index = 0; index < locator_buffer_head; ++index)
  {
    vector_position.x = ofRandom(-halfRange, halfRange);
    vector_position.y = ofRandom(-halfRange, halfRange);
    vector_position.z = ofRandom(-halfRange, halfRange);

    vector_rotation.x = 0.0f;
    vector_rotation.y = ofRandom(0.0f, 360.0f);
    vector_rotation.z = 0.0f;

    scale = ofRandom(0.05f, 0.35f);

    vector_proportion.x = scale;
    vector_proportion.y = scale;
    vector_proportion.z = scale;

    // configurer les attributs de transformation du teapot
    locators[index].position[0] = vector_position.x;
    locators[index].position[1] = vector_position.y;
    locators[index].position[2] = vector_position.z;

    locators[index].rotation[0] = vector_rotation.x;
    locators[index].rotation[1] = vector_rotation.y;
    locators[index].rotation[2] = vector_rotation.z;

    locators[index].proportion[0] = vector_proportion.x;
    locators[index].proportion[1] = vector_proportion.y;
    locators[index].proportion[2] = vector_proportion.z;
  }
}

void Renderer::draw_locator(float scale)
{
  ofFill();
  ofSetColor(127);
  ofPushMatrix();
  ofScale(scale, scale);
  node.setPosition(0.0f, 0.0f, 0.0f);
  node.draw();
  ofPopMatrix();
}

Renderer::~Renderer()
{
  std::free(locators);
}
