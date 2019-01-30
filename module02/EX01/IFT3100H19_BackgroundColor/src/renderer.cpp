// IFT3100H19_BackgroundColor/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);

  // mode initial
  clear_mode = ClearMode::none;

  // couleur initiale
  clear_color_r = 127;
  clear_color_g = 63;
  clear_color_b = 31;

  // changement d'état
  has_changed = true;

  // 1. couleur d'arrière-plan fixe et automatique

  // efface automatiquement le framebuffer et le rempli avec la couleur d'arrière-plan courante au début de chaque appel de la fonction draw (actif par défaut)
  ofSetBackgroundAuto(true);

  // si la couleur d'arrière-plan de ne change pas et est en mode automatique, elle peut être configurée et appliquée en une seule étape dans la fonction d'initialisation
  ofSetBackgroundColor(clear_color_r, clear_color_g, clear_color_b);

  // 2. couleur d'arrière-plan variable et/ou changée explicitement

  // désactiver l'application automatique de la couleur d'arrière-plan à chaque appel de la fonction draw
  ofSetBackgroundAuto(false);

  // 2.1 sélectionne la couleur d'arrière-plan courante, mais ne l'applique pas immédiatement
  ofSetBackgroundColor(clear_color_r, clear_color_g, clear_color_b);

  // 2.2 sélectionne la couleur d'arrière-plan courante et l'applique immédiatement
  ofBackground(clear_color_r, clear_color_g, clear_color_b);
}

void Renderer::draw()
{
  // 3. appliquer la couleur d'arrière-plan selon le mode courant
  switch (clear_mode)
  {
    case ClearMode::none:
      clear();
      break;

    case ClearMode::black:
      clear_to_black();
      break;

    case ClearMode::white:
      clear_to_white();
      break;

    case ClearMode::gray:
      clear_to_gray(223);
      break;

    case ClearMode::color:
      clear_to_color(127, 0, 63);
      break;

    case ClearMode::random:
      clear_to_random();
      break;

    default:
      clear_to_color(255, 0, 0);
      break;
  }
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
void Renderer::clear() const
{
  ofBackground(clear_color_r, clear_color_g, clear_color_b);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par la couleur noir
void Renderer::clear_to_black() const
{
  ofBackground(0);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par la couleur blanc
void Renderer::clear_to_white() const
{
  ofBackground(255);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par un ton de gris passé en paramètre
void Renderer::clear_to_gray(int g)
{
  if (has_changed)
  {
    has_changed = false;
    clear_color_gray = g;
  }

  ofBackground(clear_color_gray);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur RGB passée en paramètre
void Renderer::clear_to_color(int r, int g, int b)
{
  if (has_changed)
  {
    has_changed = false;

    clear_color_r = r;
    clear_color_g = g;
    clear_color_b = b;
  }

  clear();
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur RGB aléatoire
void Renderer::clear_to_random()
{
  if (has_changed)
  {
    has_changed = false;

    clear_color_r = (int) ofRandom(0, 256);
    clear_color_g = (int) ofRandom(0, 256);
    clear_color_b = (int) ofRandom(0, 256);
  }

  clear();
}
