// IFT3100H24_ShaderClassic/main.cpp
// Démonstration de 5 modèles d'illumination classiques implémentés avec des shaders :
// - couleur de remplissage uniforme sur toute la surface,
// - modèle d'illumination de Lambert,
// - modèle d'illumination de Gouraud,
// - modèle d'illumination de Phong et
// - modèle d'illumination de Blinn-Phong.
// Pour les modèles avec réflexion spéculaire, le facteur de brillance est animé par oscillation.
// La position de la source de lumière est déterminée en fonction de la position du curseur.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofGLWindowSettings windowSettings;
  windowSettings.setSize(1024, 512);
  windowSettings.setGLVersion(3, 3);
  ofCreateWindow(windowSettings);
  ofRunApp(new Application());
}
