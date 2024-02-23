// IFT3100H24_CameraFrustum/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("frustum de vision d'une caméra");

  renderer.setup();

  // initialisation du ui
  gui.setup();
  gui.add(ui_camera_clip_n.setup("camera near", renderer.camera_clip_n, 0.01f, ofGetHeight() / 10.0f));
  gui.add(ui_camera_clip_f.setup("camera far", renderer.camera_clip_f, 0.0f, ofGetHeight() / 3.0f));
  gui.add(ui_camera_fov_h.setup("camera fov", renderer.camera_fov, 0.0f, 180.0f));
  gui.add(ui_camera_zoom_h.setup("camera zoom", renderer.camera_zoom, 0.0f, 10.0f));
  gui.add(ui_color_stroke.set("color stroke", ofColor(255), ofColor(0, 0), ofColor(255, 255)));
  gui.add(ui_color_fill.set("color fill", ofColor(255, 255, 0, 127), ofColor(0, 0), ofColor(255, 255)));

  ofLog() << "<app::setup>";
}

void Application::update()
{
  // ajustement manuel du plan d'occlusion avant
  if (renderer.camera_clip_n != ui_camera_clip_n)
    renderer.camera_clip_n = ui_camera_clip_n;

  // ajustement manuel du plan d'occlusion arrière
  if (renderer.camera_clip_f != ui_camera_clip_f)
    renderer.camera_clip_f = ui_camera_clip_f;

  // ajustement manuel du champ de vision
  if (renderer.camera_fov != ui_camera_fov_h)
  {
    renderer.camera_fov = ui_camera_fov_h;

    // recalculer le zoom
    renderer.camera_zoom = renderer.compute_zoom_from_fov(renderer.camera_fov);
    ui_camera_zoom_h = renderer.camera_zoom;
  }

  // ajustement manuel du zoom
  if (renderer.camera_zoom != ui_camera_zoom_h)
  {
    renderer.camera_zoom = ui_camera_zoom_h;

    // recalculer le champ de vision
    renderer.camera_fov = renderer.compute_fov_from_zoom(renderer.camera_zoom);
    ui_camera_fov_h = renderer.camera_fov;
  }

  // ajustement manuel des couleurs de dessin
  renderer.color_fill = ui_color_fill;
  renderer.color_stroke = ui_color_stroke;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();
  gui.draw();
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
