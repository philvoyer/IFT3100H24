// IFT3100H24_BonjourMonde/application.h
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

  void mouseReleased(int x, int y, int button);

  void exit();
};
