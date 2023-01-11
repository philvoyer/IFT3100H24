// IFT3100H23_CameraFrustum/main.cpp
// Exemple qui permet de visualiser et paramétrer la forme d'un frustum de vision d'une caméra en vue de haut.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
