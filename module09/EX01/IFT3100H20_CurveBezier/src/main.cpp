// IFT3100H20_CurveBezier/main.cpp
// Exemple d'une courbe de Bézier quadratique et d'une courbe de Bézier cubique.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofGLWindowSettings windowSettings;
  windowSettings.setSize(1920/2.0f, 1080/2.0f);
  windowSettings.setGLVersion(2, 1);
  ofCreateWindow(windowSettings);
  ofRunApp(new Application());
}
