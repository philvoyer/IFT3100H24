// IFT3100H23_CameraFrustum/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);

  reset();
}

void Renderer::reset()
{
  // pamamètres de dessin
  circle_radius = 5.0f;
  stroke_width = 3.0f;

  // attributs de la caméra
  camera_position.z = 0.0f;
  camera_viewport_x = 1920.0f;
  camera_viewport_y = 1080.0f;
  camera_clip_n = 10.0f;
  camera_clip_f = 100.0f;
  camera_fov = 60.0f;
  camera_zoom = compute_zoom_from_fov(camera_fov);
}

void Renderer::update()
{
  // facteur de proportion du frustum par rapport à la fenêtre d'affichage
  scale_factor = ofGetHeight() * 0.005f;

  // calculer le ratio d'aspect de la fenêtre d'affichage
  camera_aspect_ratio = camera_viewport_x / camera_viewport_y;

  // position de la caméra
  camera_position.x = ofGetWidth() / 2.0f;
  camera_position.y = ofGetHeight() / 8.0f;

  // position vers laquelle la caméra est orientée
  camera_target.x = camera_position.x;
  camera_target.y = position_clip_f_c.y;

  // calculer la position de l'intersection entre la ligne de vue et les plans d'occlusion avant et arrière
  position_clip_n_c.x = camera_position.x;
  position_clip_f_c.x = camera_position.x;
  position_clip_n_c.y = camera_position.y + camera_clip_n * scale_factor;
  position_clip_f_c.y = camera_position.y + camera_clip_f * scale_factor;

  // calculer la largeur des plans d'occlusion avant et arrière
  clip_half_width_n = camera_clip_n * tanf(glm::radians(camera_fov / 2.0f));
  clip_half_width_f = camera_clip_f * tanf(glm::radians(camera_fov / 2.0f));
  clip_width_n = clip_half_width_n * 2.0f;
  clip_width_f = clip_half_width_f * 2.0f;

  // calculer la position de l'intersection entre le champ de vision et les plans d'occlusion avant et arrière
  position_clip_n_l.x = position_clip_n_c.x - clip_half_width_n * scale_factor;
  position_clip_n_l.y = position_clip_n_c.y;
  position_clip_n_r.x = position_clip_n_c.x + clip_half_width_n * scale_factor;
  position_clip_n_r.y = position_clip_n_c.y;
  position_clip_f_l.x = position_clip_f_c.x - clip_half_width_f * scale_factor;
  position_clip_f_l.y = position_clip_f_c.y;
  position_clip_f_r.x = position_clip_f_c.x + clip_half_width_f * scale_factor;
  position_clip_f_r.y = position_clip_f_c.y;

  // ligne de contour du frustum
  camera_frustum_outline.clear();
  camera_frustum_outline.addVertex(position_clip_n_l.x, position_clip_n_l.y);
  camera_frustum_outline.addVertex(position_clip_n_r.x, position_clip_n_r.y);
  camera_frustum_outline.addVertex(position_clip_f_r.x, position_clip_f_r.y);
  camera_frustum_outline.addVertex(position_clip_f_l.x, position_clip_f_l.y);
  camera_frustum_outline.close();

  // générer des matrices à partir de l'état courant des attributs de caméra
  generate_matrix();
}

void Renderer::draw()
{
  // transformation
  ofPushMatrix();
  ofTranslate(0.0f, ofGetHeight(), 0.0f);
  ofScale(1.0f, -1.0f, 1.0f);

  // dessiner la zone de remplissage du frustum
  ofSetColor(color_fill);
  ofBeginShape();
  ofVertex(position_clip_n_l.x, position_clip_n_l.y);
  ofVertex(position_clip_n_r.x, position_clip_n_r.y);
  ofVertex(position_clip_f_r.x, position_clip_f_r.y);
  ofVertex(position_clip_f_l.x, position_clip_f_l.y);
  ofEndShape();

  // dessiner la ligne de contour du frustum
  ofSetColor(color_stroke);
  ofSetLineWidth(stroke_width);
  camera_frustum_outline.draw();

  // dessiner les lignes du frustum
  ofSetLineWidth(1.0f);
  ofDrawLine(camera_position.x, camera_position.y, camera_position.x, position_clip_f_c.y + 32);
  ofDrawLine(camera_position.x, camera_position.y, position_clip_f_l.x, position_clip_f_c.y);
  ofDrawLine(camera_position.x, camera_position.y, position_clip_f_r.x, position_clip_f_r.y);
  ofDrawLine(position_clip_n_l.x, position_clip_n_l.y, position_clip_n_r.x, position_clip_n_r.y);
  ofDrawLine(position_clip_f_l.x, position_clip_f_l.y, position_clip_f_r.x, position_clip_f_r.y);

  // dessiner la position de la caméra
  ofDrawCircle(camera_position.x, camera_position.y, circle_radius);

  // dessiner la position de la position observée par la caméra
  ofDrawCircle(camera_target.x, camera_target.y, circle_radius);

  // dessiner la position de l'intersection entre la ligne de vue et les plans d'occlusion avant et arrière
  ofDrawCircle(position_clip_n_c.x, position_clip_n_c.y, circle_radius * 0.618f);
  ofDrawCircle(position_clip_f_c.x, position_clip_f_c.y, circle_radius * 0.618f);

  // dessiner la position de l'intersection entre le champ de vision et les plans d'occlusion avant et arrière
  ofDrawCircle(position_clip_n_l.x, position_clip_n_c.y, circle_radius);
  ofDrawCircle(position_clip_n_r.x, position_clip_n_c.y, circle_radius);
  ofDrawCircle(position_clip_f_l.x, position_clip_f_c.y, circle_radius);
  ofDrawCircle(position_clip_f_r.x, position_clip_f_c.y, circle_radius);

  ofPopMatrix();
}

// fonction qui construit différentes matrices à partir de l'état courant des attributs de caméra
void Renderer::generate_matrix()
{
  // construire une matrice de modèle
  glm::mat4 matrix_model = glm::translate(glm::mat4(1.0f), camera_position);

  // construire une matrice de vue
  glm::mat4 matrix_view = glm::inverse(matrix_model);

  // construire une matrice de projection
  glm::mat4 matrix_projection = glm::perspective(glm::radians(camera_fov), camera_aspect_ratio,  camera_clip_n, camera_clip_f);

  // construire une matrice de modèle-vue
  glm::mat4 matrix_model_view = matrix_view * matrix_model;

  // construire une matrice de modèle-vue-projection
  glm::mat4 matrix_model_view_projection = matrix_projection * matrix_view * matrix_model;

  // ces matrices peuvent ensuite être passées à un shader de sommets sous forme d'attributs uniformes
}

// fonction qui calcul un angle de champs de vision à partir d'un facteur de zoom
float Renderer::compute_fov_from_zoom(float zoom)
{
  return glm::degrees(2.0f * atanf(1.0f / camera_zoom));;
}

// fonction qui calcul un facteur de zoom à partir d'una ngle de champs de vision
float Renderer::compute_zoom_from_fov(float fov)
{
  return 1.0f / tanf(glm::radians(camera_fov) / 2.0f);;
}
