// IFT3100H21_DrawVectorPrimitive/main.cpp
// Dessiner des primitives vectorielles dans une zone de dessin (pixel, point, ligne, rectangle et ellipse)
// avec des couleurs aléatoires pour les lignes de contour et les zones de remplissage.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(1024, 1024, OF_WINDOW);
  ofRunApp(new Application());
}
