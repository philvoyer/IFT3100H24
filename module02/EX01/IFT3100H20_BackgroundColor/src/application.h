// IFT3100H20_BackgroundColor/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;

  void setup();
  void draw();

  void keyReleased(int key);

  void exit();
};
