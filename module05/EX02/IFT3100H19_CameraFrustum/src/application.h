// IFT3100H19_CameraFrustum/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  void setup();
  void update();
  void draw();
  void exit();
};
