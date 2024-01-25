// IFT3100H24_ImageExport/application.h
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

  void windowResized(int w, int h);

  void dragEvent(ofDragInfo dragInfo);

  void exit();
};
