// IFT3100H19_PBR/main.cpp
// Dans cet exemple, différents maillages géométriques sont rendus avec un modèle d'illumination de type PBR.
// Le modèle d'illumination est celui qui est couramment appelé GGX.
// La fonction BRDF est celle de Cook-Torrance.
// La fonction de distribution des microfacettes est celle de Trowbridge-Reitz.
// La fonction géométrique qui permet de calculer l'impact de l'occlusion et de l'ombrage des microfacettes est celle de Schlick-Beckmann et elle est utilisée par la méthode de Smith.
// La fonction qui calcule l'effet de Fresnel est celle de Schlick-Fresnel.
// L'éclairage de la scène provient d'une lumière ponctuelle qui est transformée en fonction de la position du curseur.
// Le matériau utilise 4 textures : une texture diffuse pour la couleur de base et une texture pour la rugosité, la métallicité et l'occlusion ambiante (source : https://texturehaven.com/).
// Différents attributs du matériau peuvent être configurés à partir d'une interface graphique (ex. couleurs ambiante, diffuse et spéculaire du matériau, facteur de rugosité et métallicité, couleur et intensité de la lumière, paramètres de mappage tonal, correction gamma, etc.).

#include "ofMain.h"
#include "application.h"

int main()
{
  ofGLFWWindowSettings window_settings;
  window_settings.setSize(1024, 512);
  window_settings.setGLVersion(3, 3);
  window_settings.numSamples = 4;
  window_settings.doubleBuffering = true;
  ofCreateWindow(window_settings);
  ofRunApp(new Application());
}
