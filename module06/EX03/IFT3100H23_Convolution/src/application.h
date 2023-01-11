// IFT3100H23_Convolution/application.cpp
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
