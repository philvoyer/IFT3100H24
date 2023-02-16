// IFT3100H23_CameraProjection/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetLogLevel(OF_LOG_VERBOSE);

  // paramètres
  scale_teapot = 1.0f;
  rotation_speed = 0.3f;
  use_rotation = true;
  speed = 300.0f;

  // caméra
  camera_setup_perspective(ofGetWidth(), ofGetHeight(), 60.0f, 0.0f, 0.0f);
  camera_is_active = true;

  // mouvement

  delta_x = speed;
  delta_z = speed;
  offset_x = 0.0f;
  offset_z = 0.0f;

  // chargement du modèle
  teapot.load("teapot.obj");

  // désactiver le matériau par défaut du modèle
  teapot.disableMaterials();

  // chargement du shader
  shader_lambert.load("lambert_330_vs.glsl", "lambert_330_fs.glsl");
  shader_normal.load("draw_normal_330_vs.glsl", "draw_normal_330_fs.glsl");
  shader_depth.load("draw_depth_330_vs.glsl", "draw_depth_330_fs.glsl");

  // sélectionner le shader courant
  shader = shader_lambert;
}

void Renderer::update()
{
  // position au centre de la fenêtre d'affichage
  center_x = ofGetWidth() / 2.0f;
  center_y = ofGetHeight() / 2.0f;

  // mise à jour de la caméra (au besoin)
  if (camera_state_change)
    camera_setup_perspective(ofGetWidth(), ofGetHeight(), camera_fov, camera_clip_n, camera_clip_f);

  // transformation du teapot
  teapot.setScale(scale_teapot, scale_teapot, scale_teapot);
  teapot.setPosition(center_x, center_y + 90.0f, 0.0f);

  if (use_rotation)
    teapot.setRotation(0, ofGetFrameNum() * rotation_speed, 0.0f, 1.0f, 0.0f);

  // configuration de la lumière
  light.setPointLight();
  light.setDiffuseColor(255);
  light.setGlobalPosition(center_x, center_y, 255.0f);
}

void Renderer::draw()
{
  if (camera_is_active)
    camera.begin();

  // couleur de l'arrière-plan
  ofSetBackgroundColor(color_background.r, color_background.g, color_background.b);

  ofPushMatrix();

  // mouvement
  ofTranslate(offset_x, 0, offset_z);

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
  shader.setUniform1f("depth_range", camera_depth_range / 10.0f);

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

  ofPopMatrix();

  if (camera_is_active)
    camera.end();
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

// fonction qui permet de configurer les attributs d'une caméra en perspective
void Renderer::camera_setup_perspective(float width, float height, float fov, float near, float far)
{
  camera_projection_persp_or_ortho = true;
  camera_vertical_flip = true;

  camera_viewport_x = width;
  camera_viewport_y = height;
  camera_aspect_ratio = camera_viewport_x / camera_viewport_y;

  camera_fov = fov;
  camera_zoom = compute_zoom_from_fov(camera_fov);

  float minimal_side = std::min(camera_viewport_x, camera_viewport_y);
  float fov_half = ofDegToRad(camera_fov / 2.0f);
  float distance = minimal_side / 2.0f / tanf(fov_half);

  camera_position.x = camera_viewport_x / 2.0f;
  camera_position.y = camera_viewport_y / 2.0f;
  camera_position.z = distance;

  camera_clip_n = near > 0.0f ? near : distance / 10.0f;
  camera_clip_f = far > 0.0f ? far : distance * 10.0f;

  camera_depth_range = camera_clip_f - camera_clip_n;

  // configurer l'instance de caméra de openFrameworks (ofCamera)
  camera.setupPerspective(camera_vertical_flip, camera_fov, camera_clip_n, camera_clip_f);
  camera.setPosition(camera_position.x, camera_position.y, camera_position.z);

  camera_state_change = false;
}

void Renderer::camera_current_state_log()
{
  camera_position.x = camera.getX();
  camera_position.y = camera.getY();
  camera_position.z = camera.getZ();
  camera_fov = camera.getFov();
  camera_clip_n = camera.getNearClip();
  camera_clip_f = camera.getFarClip();
  camera_vertical_flip = camera.isVFlipped();
  camera_zoom = 1.0f / tanf(glm::radians(camera_fov) / 2.0f);
  camera_projection_persp_or_ortho = !camera.getOrtho();

  ofLog() << "\ncamera (" << (camera_projection_persp_or_ortho ? "perspective" : "orthographic") << ")\n"
          << "\tposition:   " << "(" << camera_position.x << ", " << camera_position.y << ", " << camera_position.z << ")\n"
          << "\tnear:       " << camera_clip_n << "\n"
          << "\tfar:        " << camera_clip_n << "\n"
          << "\tfov:        " << camera_fov << "\n"
          << "\tzoom:       " << camera_zoom << "\n"
          << "\tvflip:      " << (camera_vertical_flip ? "true" : "false") << "\n"
          << "\thandedness: " << (ofGetCoordHandedness() == OF_LEFT_HANDED ? "left" : "right");

  glm::mat4 matrix_model_view;
  glm::mat4 matrix_projection;

  if (camera_is_active)
  {
    matrix_model_view = camera.getModelViewMatrix();
    matrix_projection = camera.getProjectionMatrix();
  }
  else
  {
    matrix_model_view = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    matrix_projection = ofGetCurrentMatrix(OF_MATRIX_PROJECTION);
  }

  ofLog() << "matrix model view:\n" << glm::to_string(matrix_model_view);
  ofLog() << "matrix projection:\n" << glm::to_string(matrix_projection);
}
