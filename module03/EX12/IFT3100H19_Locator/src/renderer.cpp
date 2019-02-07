// IFT3100H19_Locator/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  ofEnableDepthTest();

  // initialisation des variables
  speed = 100.0f;

  offset_x = 0.0f;
  offset_z = 0.0f;

  delta_x = speed;
  delta_z = speed;

  is_flip_axis_y = false;

  is_active_translation = true;
  is_active_rotation = false;
  is_active_proportion = false;

  locator_count = 100;
  locator_buffer_size = locator_count;
  locator_buffer_head = 0;

  // allocation d'un espace mémoire suffisamment grand pour contenir les données de l'ensemble des localisateurs
  locators = (Locator*) std::malloc(locator_buffer_size * sizeof(Locator));

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
  // copier la matrice de transformation courante sur le dessus de la pile
  ofPushMatrix();

  // inverser l'axe Y pour qu'il pointe vers le haut
  ofScale(1.0f, is_flip_axis_y ? -1.0f : 1.0f);

  // transformer l'origine de la scène au milieu de la fenêtre d'affichage
  ofTranslate(center_x + offset_x, is_flip_axis_y ? -center_y : center_y, offset_z);

  for (index = 0; index < locator_buffer_head; ++index)
  {
    ofPushMatrix();

    if (is_active_translation)
    {
      // extraction des attributs de translation
      vector_position.x = locators[index].position[0];
      vector_position.y = locators[index].position[1];
      vector_position.z = locators[index].position[2];
    }
    else
    {
      // attributs de translation par défaut
      vector_position.x = 0.0f;
      vector_position.y = 0.0f;
      vector_position.z = 0.0f;
    }

    // assignation des attributs de translation
    node.setPosition(
                     vector_position.x,
                     vector_position.y,
                     vector_position.z);

    if (is_active_rotation)
    {
      // extraction des attributs de rotation
      vector_rotation.x = locators[index].rotation[0];
      vector_rotation.y = locators[index].rotation[1];
      vector_rotation.z = locators[index].rotation[2];
    }
    else
    {
      // attributs de rotation par défaut
      vector_rotation.x = 0.0f;
      vector_rotation.y = 0.0f;
      vector_rotation.z = 0.0f;
    }

    // assignation des attributs de rotation
    node.setOrientation(vector_rotation);

    if (is_active_proportion)
    {
      // extraction des attributs de proportion
      vector_proportion.x = locators[index].proportion[0];
      vector_proportion.y = locators[index].proportion[1];
      vector_proportion.z = locators[index].proportion[2];
    }
    else
    {
      // attributs de proportion par défaut
      vector_proportion.x = 1.0f;
      vector_proportion.y = 1.0f;
      vector_proportion.z = 1.0f;
    }

    // assignation des attributs de proportion
    node.setScale(
                  vector_proportion.x,
                  vector_proportion.y,
                  vector_proportion.z);

    // dessiner le localisateur
    node.draw();

    ofPopMatrix();
  }

  // dessiner l'origine de la scène
  draw_locator(10.0f);

  // revenir à la matrice de transformation précédente dans la pile
  ofPopMatrix();
}

// fonction qui initialise la scène
void Renderer::reset()
{
  // distribuer les localisateurs dans l'espace visible de la scène
  dispatch_locators(locator_count, std::min(ofGetWidth(), ofGetHeight()));

  ofLog() << "<reset>";
}

// fonction qui distribue les localisateurs dans un espace cubique
void Renderer::dispatch_locators(int count, float range)
{
  // variable temporaire
  float scale;

  // validations
  if (count <= 0 || range <= 0 || count > locator_buffer_size)
    return;

  // calculer la valeur de la moitié du diamètre du cube
  float halfRange = range / 2.0f;

  // configurer le nombre de localisateurs
  locator_buffer_head = count;

  for (index = 0; index < locator_buffer_head; ++index)
  {
    // déterminer des valeurs de position aléatoires dans le cube
    vector_position.x = ofRandom(-halfRange, halfRange);
    vector_position.y = ofRandom(-halfRange, halfRange);
    vector_position.z = ofRandom(-halfRange, halfRange);

    // déterminer une rotation aléatoire sur l'axe Y
    vector_rotation.x = 0;
    vector_rotation.y = ofRandom(0, 360);
    vector_rotation.z = 0;

    // déterminer une proportion uniforme au hasard entre 10% et 200%
    scale = ofRandom(0.1f, 2.0f);
    vector_proportion.x = scale;
    vector_proportion.y = scale;
    vector_proportion.z = scale;

    // configurer les attributs de transformation du localisateur
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
  ofSetLineWidth(4);
  ofSetColor(127);
  ofFill();
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
