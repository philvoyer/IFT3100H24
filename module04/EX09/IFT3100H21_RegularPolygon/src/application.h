// IFT3100H21_RegularPolygon/application.h
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

  void keyReleased(int key);

  void exit();
};
