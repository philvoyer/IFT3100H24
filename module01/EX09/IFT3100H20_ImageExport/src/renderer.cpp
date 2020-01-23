// IFT3100H20_ImageExport/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);

  // mode d'échantillonage des coordonnées de texture
  ofDisableArbTex();

  // chargement du code source des shaders
  shader_passthrough.load(
    "image_passthrough_330_vs.glsl",
    "image_passthrough_330_fs.glsl");

  shader_invert.load(
    "image_invert_330_vs.glsl",
    "image_invert_330_fs.glsl");

  // shader actif au lancement de l'application
  shader = shader_passthrough;

  image.load("teapot.jpg");

  ofSetWindowShape(image.getWidth(), image.getHeight());

  filter = false;
}

void Renderer::draw()
{
  // sélectionner le shader
  shader.begin();

  // passer la texture au shader sous forme d'un attribut uniforme
  shader.setUniformTexture("image", image.getTexture(), 1);

  // afficher l'image sur toute la surface de la fenêtre d'affichage
  image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

  // désélectionner le shader
  shader.end();
}

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::image_export(const string name, const string extension) const
{
  ofImage image;

  // extraire des données temporelles formatées
  string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

  // générer un nom de fichier unique et ordonné
  string file_name = name + time_stamp + "." + extension;

  // capturer le contenu du framebuffer actif
  image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

  // sauvegarder le fichier image
  image.save(file_name);

  ofLog() << "<export image: " << file_name << ">";
}
