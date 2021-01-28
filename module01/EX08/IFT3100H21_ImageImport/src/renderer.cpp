// IFT3100H21_ImageImport/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  // importer une image située dans ./bin/data
  image.load("teapot.jpg");

  // redimensionner la fenêtre selon la résolution de l'image
  ofSetWindowShape(image.getWidth(), image.getHeight());
}

void Renderer::draw()
{
  // afficher l'image sur toute la surface de la fenêtre d'affichage
  image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}
