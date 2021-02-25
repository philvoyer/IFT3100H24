// IFT3100H21_CameraTransform/main.cpp
// Exemple d'une scène avec différentes caméras interactives.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
