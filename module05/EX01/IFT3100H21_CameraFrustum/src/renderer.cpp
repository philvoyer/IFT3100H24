// IFT3100H21_CameraFrustum/renderer.cpp
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
  color_frustum_in = ofColor(0, 255, 0);
  color_frustum_out = ofColor(255, 0, 0);

  // attributs de la caméra
  camera_position.z = 0.0f;
  camera_resolution_w = 1920.0f;
  camera_resolution_h = 1080.0f;
  camera_clip_n = 10.0f;
  camera_clip_f = 100.0f;
  camera_fov = 60.0f;
  camera_zoom = 1.0f / tanf(glm::radians(camera_fov) / 2.0f);

  // initialisation du ui
  gui.setup();
  gui.add(ui_camera_clip_n.setup("camera near", camera_clip_n, 0.0f, ofGetHeight()));
  gui.add(ui_camera_clip_f.setup("camera far", camera_clip_f, 0.0f, ofGetHeight()));
  gui.add(ui_camera_fov_h.setup("camera fov", camera_fov, 0.0f, 180.0f));
  gui.add(ui_camera_zoom_h.setup("camera zoom", camera_zoom, 0.0f, 10.0f));
  gui.add(color_stroke.set("color stroke", ofColor(255), ofColor(0, 0), ofColor(255, 255)));
  gui.add(color_fill.set("color fill", (255.0f, 255.0f, 0.0f, 127.0f), ofColor(0, 0), ofColor(255, 255)));
}

void Renderer::update()
{
  // facteur de proportion du frustum par rapport à la fenêtre d'affichage
  scale_factor = ofGetHeight() * 0.005f;

  // calculer le ratio d'aspect de la fenêtre d'affichage
  camera_aspect_ratio = camera_resolution_w / camera_resolution_h;

  // position de la caméra
  camera_position.x = ofGetWidth() / 2.0f;
  camera_position.y = ofGetHeight() / 8.0f;

  // position vers laquelle la caméra est orientée
  camera_target.x = camera_position.x;
  camera_target.y = position_clip_f_c.y;

  // ajustement manuel du plan d'occlusion avant
  if (camera_clip_n != ui_camera_clip_n)
  {
    camera_clip_n = ui_camera_clip_n;
  }

  // ajustement manuel du plan d'occlusion arrière
  if (camera_clip_f != ui_camera_clip_f)
  {
    camera_clip_f = ui_camera_clip_f;
  }

  // ajustement manuel du champ de vision
  if (camera_fov != ui_camera_fov_h)
  {
    camera_fov = ui_camera_fov_h;

    // recalculer le zoom
    camera_zoom = 1.0f / tanf(glm::radians(camera_fov) / 2.0f);
    ui_camera_zoom_h = camera_zoom;
  }

  // ajustement manuel du zoom
  if (camera_zoom != ui_camera_zoom_h)
  {
    camera_zoom = ui_camera_zoom_h;

    // recalculer le champ de vision
    camera_fov = glm::degrees(2.0f * atanf(1.0f / camera_zoom));
    ui_camera_fov_h = camera_fov;
  }

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

  // dessiner l'interface graphique
  gui.draw();
}

// fonction qui construit différentes matrices à partir des états courants du programme
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
