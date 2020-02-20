// IFT3100H20_CameraTransform/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  ofEnableDepthTest();

  // paramètres
  camera_position = {0.0f, 0.0f, 0.0f};
  camera_target = {0.0f, 0.0f, 0.0f};

  camera_near = 50.0f;
  camera_far = 1750.0f;

  camera_fov = 60.0f;
  camera_fov_delta = 16.0f;

  speed_delta = 250.0f;

  offset_cube = 64.0f;

  cube_count = 7;

  is_visible_axes = false;
  is_visible_grid = false;
  is_visible_camera = false;
  is_visible_box = true;
  is_visible_locator = false;
  is_visible_text = false;

  is_camera_move_left = false;
  is_camera_move_right = false;
  is_camera_move_up = false;
  is_camera_move_down = false;
  is_camera_move_forward = false;
  is_camera_move_backward = false;

  is_camera_tilt_up = false;
  is_camera_tilt_down = false;
  is_camera_pan_left = false;
  is_camera_pan_right = false;
  is_camera_roll_left = false;
  is_camera_roll_right = false;

  is_camera_fov_narrow = false;
  is_camera_fov_wide = false;

  is_camera_perspective = true;

  use_color_fill = true;

  draw_as_checkerboard = false;

  reset();

  setup_camera();
}

void Renderer::reset()
{
  // initialisation des variables
  cube_size = offset_cube / 2.0f;
  offset_scene = cube_count * offset_cube / 2.0f * -1.0f + cube_size;
  offset_color = 255.0f / cube_count;
  offset_camera = offset_scene * 3.5f * -1.0f;

  // position initiale de chaque caméra
  camera_front.setPosition(0, 0, -offset_camera);
  camera_back.setPosition(0, 0, offset_camera);
  camera_left.setPosition(-offset_camera, 0, 0);
  camera_right.setPosition(offset_camera, 0, 0);
  camera_top.setPosition(0, offset_camera, 0);
  camera_down.setPosition(0, -offset_camera, 0);

  // orientation de chaque caméra
  camera_front.lookAt(camera_target);
  camera_back.lookAt(camera_target);
  camera_left.lookAt(camera_target);
  camera_right.lookAt(camera_target);
  camera_top.lookAt(camera_target, ofVec3f(1, 0, 0));
  camera_down.lookAt(camera_target, ofVec3f(1, 0, 0));

  // caméra par défaut
  camera_active = Camera::front;

  ofLog() << "<reset>";
}

void Renderer::update()
{
  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

  speed_translation = speed_delta * time_elapsed;
  speed_rotation = speed_translation / 8.0f;

  if (is_camera_move_left)
    camera->truck(-speed_translation);
  if (is_camera_move_right)
    camera->truck(speed_translation);

  if (is_camera_move_up)
    camera->boom(speed_translation);
  if (is_camera_move_down)
    camera->boom(-speed_translation);

  if (is_camera_move_forward)
    camera->dolly(-speed_translation);
  if (is_camera_move_backward)
    camera->dolly(speed_translation);

  if (is_camera_tilt_up)
    camera->tiltDeg(-speed_rotation);
  if (is_camera_tilt_down)
    camera->tiltDeg(speed_rotation);

  if (is_camera_pan_left)
    camera->panDeg(speed_rotation);
  if (is_camera_pan_right)
    camera->panDeg(-speed_rotation);

  if (is_camera_roll_left)
    camera->rollDeg(-speed_rotation);
  if (is_camera_roll_right)
    camera->rollDeg(speed_rotation);

  if (is_camera_perspective)
  {
    if (is_camera_fov_narrow)
    {
      camera_fov = std::max(camera_fov -= camera_fov_delta * time_elapsed, 0.0f);
      camera->setFov(camera_fov);
    }

    if (is_camera_fov_wide)
    {
      camera_fov = std::min(camera_fov += camera_fov_delta * time_elapsed, 180.0f);
      camera->setFov(camera_fov);
    }
  }
}

void Renderer::draw()
{
  // activer la caméra
  camera->begin();

  // dessiner une grille
  if (is_visible_grid)
    ofDrawGrid(64);

  // dessiner un gizmo pour les axes de la scène
  if (is_visible_axes)
    ofDrawRotationAxes(64);

  // dessiner un gizmo pour toutes les caméras sauf celle qui est active
  if (is_visible_camera)
  {
    if (camera_active != Camera::front)
      camera_front.draw();
    if (camera_active != Camera::back)
      camera_back.draw();
    if (camera_active != Camera::left)
      camera_left.draw();
    if (camera_active != Camera::right)
      camera_right.draw();
    if (camera_active != Camera::top)
      camera_top.draw();
    if (camera_active != Camera::down)
      camera_down.draw();
  }

  // dessiner une zone de texte avec le nom des caméras
  if (is_visible_text)
  {
    if (camera_active != Camera::front)
      ofDrawBitmapString(" camera front", camera_front.getPosition());
    if (camera_active != Camera::back)
      ofDrawBitmapString(" camera back", camera_back.getPosition());
    if (camera_active != Camera::left)
      ofDrawBitmapString(" camera left", camera_left.getPosition());
    if (camera_active != Camera::right)
      ofDrawBitmapString(" camera right", camera_right.getPosition());
    if (camera_active != Camera::top)
      ofDrawBitmapString(" camera top", camera_top.getPosition());
    if (camera_active != Camera::down)
      ofDrawBitmapString(" camera down", camera_down.getPosition());
  }

  // dessiner le contenu de la scène
  if (is_visible_box)
  {
    for (index_x = 0; index_x < cube_count; ++index_x)
    {
      for (index_y = 0; index_y < cube_count; ++index_y)
      {
        for (index_z = 0; index_z < cube_count; ++index_z)
        {
          if (index_x % 2 == index_y % 2 == index_z % 2 || !draw_as_checkerboard)
          {
            ofSetColor(
              index_x * offset_color,
              index_y * offset_color,
              index_z * offset_color);

            ofDrawBox(
              offset_scene + index_x * offset_cube,
              offset_scene + index_y * offset_cube,
              offset_scene + index_z * offset_cube,
              cube_size);
          }
        }
      }
    }
  }

  camera->end();
}

// fonction de configuration de la caméra active
void Renderer::setup_camera()
{
  switch (camera_active)
  {
    case Camera::front:
      camera = &camera_front;
      camera_name = "avant";
      break;

    case Camera::back:
      camera = &camera_back;
      camera_name = "arrière";
      break;

    case Camera::left:
      camera = &camera_left;
      camera_name = "gauche";
      break;

    case Camera::right:
      camera = &camera_right;
      camera_name = "droite";
      break;

    case Camera::top:
      camera = &camera_top;
      camera_name = "haut";
      break;

    case Camera::down:
      camera = &camera_down;
      camera_name = "bas";
      break;

    default:
      break;
  }

  camera_position = camera->getPosition();
  camera_orientation = camera->getOrientationQuat();

  // mode de projection de la caméra
  if (is_camera_perspective)
  {
    camera->disableOrtho();
    camera->setupPerspective(false, camera_fov, camera_near, camera_far, ofVec2f(0, 0));
    camera_projection = "perspective";
  }
  else
  {
    camera->enableOrtho();
    camera_projection = "orthogonale";
  }

  camera->setPosition(camera_position);
  camera->setOrientation(camera_orientation);

  ofLog() << "<setup camera: " << camera_name << ">";
}
