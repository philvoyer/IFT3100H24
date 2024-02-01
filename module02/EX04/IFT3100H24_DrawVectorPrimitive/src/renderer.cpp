// IFT3100H24_DrawVectorPrimitive/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(191);

  // nombre maximal de primitives vectorielles dans le tableau
  buffer_count = 100;

  // position de la prochaine primitive
  buffer_head = 0;

  // calculer la taille de la structure générique commune à toutes les primitives vectorielles
  buffer_stride = sizeof(VectorPrimitive);

  // calculer le nombre d'octets à allouer en mémoire pour contenir le tableau de primitives vectorielles
  buffer_size = buffer_count * buffer_stride;

  // allocation d'un espace mémoire suffisamment grand pour contenir les données de l'ensemble des primitives vectorielles
  shapes = (VectorPrimitive*) std::malloc(buffer_size);

  // mode de dessin par défaut
  draw_mode = VectorPrimitiveType::rectangle;

  // largeur de la ligne de contour
  stroke_width_default = 2;

  // couleur de la ligne de contour
  random_color_stroke();

  // couleur de la zone de remplissage
  random_color_fill();

  mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;

  is_mouse_button_pressed = false;

  radius = 4.0f;
}

void Renderer::draw()
{
  for (index = 0; index < buffer_count; ++index)
  {
    switch (shapes[index].type)
    {
      case VectorPrimitiveType::pixel:

        ofFill();
        ofSetLineWidth(0);
        ofSetColor(
          shapes[index].stroke_color[0],
          shapes[index].stroke_color[1],
          shapes[index].stroke_color[2]);
        draw_pixel(
          shapes[index].position2[0],
          shapes[index].position2[1]);
        break;

      case VectorPrimitiveType::point:

        ofFill();
        ofSetLineWidth(0);
        ofSetColor(
          shapes[index].stroke_color[0],
          shapes[index].stroke_color[1],
          shapes[index].stroke_color[2]);
        draw_point(
          shapes[index].position2[0],
          shapes[index].position2[1],
          shapes[index].stroke_width);
        break;

      case VectorPrimitiveType::line:

        ofNoFill();
        ofSetLineWidth(shapes[index].stroke_width);
        ofSetColor(
          shapes[index].stroke_color[0],
          shapes[index].stroke_color[1],
          shapes[index].stroke_color[2]);
        draw_line(
          shapes[index].position1[0],
          shapes[index].position1[1],
          shapes[index].position2[0],
          shapes[index].position2[1]);
        break;

      case VectorPrimitiveType::rectangle:

        ofFill();
        ofSetLineWidth(0);
        ofSetColor(
          shapes[index].fill_color[0],
          shapes[index].fill_color[1],
          shapes[index].fill_color[2]);
        draw_rectangle(
          shapes[index].position1[0],
          shapes[index].position1[1],
          shapes[index].position2[0],
          shapes[index].position2[1]);
        ofNoFill();
        ofSetLineWidth(shapes[index].stroke_width);
        ofSetColor(
          shapes[index].stroke_color[0],
          shapes[index].stroke_color[1],
          shapes[index].stroke_color[2]);
        draw_rectangle(
          shapes[index].position1[0],
          shapes[index].position1[1],
          shapes[index].position2[0],
          shapes[index].position2[1]);
        break;

      case VectorPrimitiveType::ellipse:

        ofFill();
        ofSetLineWidth(0);
        ofSetCircleResolution(48);
        ofSetColor(
          shapes[index].fill_color[0],
          shapes[index].fill_color[1],
          shapes[index].fill_color[2]);
        draw_ellipse(
          shapes[index].position1[0],
          shapes[index].position1[1],
          shapes[index].position2[0],
          shapes[index].position2[1]);
        ofNoFill();
        ofSetLineWidth(shapes[index].stroke_width);
        ofSetColor(
          shapes[index].stroke_color[0],
          shapes[index].stroke_color[1],
          shapes[index].stroke_color[2]);
        draw_ellipse(
          shapes[index].position1[0],
          shapes[index].position1[1],
          shapes[index].position2[0],
          shapes[index].position2[1]);
        break;

      default:
        break;
    }
  }

  // afficher la zone de sélection
  if (is_mouse_button_pressed)
  {
    draw_zone(
      mouse_press_x,
      mouse_press_y,
      mouse_current_x,
      mouse_current_y);
  }

  draw_cursor(mouse_current_x, mouse_current_y);
}

// fonction qui vide le tableau de primitives vectorielles
void Renderer::reset()
{
  for (index = 0; index < buffer_count; ++index)
    shapes[index].type = VectorPrimitiveType::none;

  buffer_head = 0;

  ofLog() << "<reset>";
}

// fonction qui ajoute une primitive vectorielle au tableau
void Renderer::add_vector_shape(VectorPrimitiveType type)
{
  shapes[buffer_head].type = type;

  shapes[buffer_head].position1[0] = mouse_press_x;
  shapes[buffer_head].position1[1] = mouse_press_y;

  shapes[buffer_head].position2[0] = mouse_current_x;
  shapes[buffer_head].position2[1] = mouse_current_y;

  shapes[buffer_head].stroke_color[0] = stroke_color_r;
  shapes[buffer_head].stroke_color[1] = stroke_color_g;
  shapes[buffer_head].stroke_color[2] = stroke_color_b;
  shapes[buffer_head].stroke_color[3] = stroke_color_a;

  shapes[buffer_head].fill_color[0] = fill_color_r;
  shapes[buffer_head].fill_color[1] = fill_color_g;
  shapes[buffer_head].fill_color[2] = fill_color_b;
  shapes[buffer_head].fill_color[3] = fill_color_a;

  switch (shapes[buffer_head].type)
  {
    case VectorPrimitiveType::point:
      shapes[buffer_head].stroke_width = ofRandom(1, 64);
      break;

    case VectorPrimitiveType::line:
      shapes[buffer_head].stroke_width = ofRandom(1, 16);
      break;

    case VectorPrimitiveType::rectangle:
      shapes[buffer_head].stroke_width = stroke_width_default;
      break;

    case VectorPrimitiveType::ellipse:
      shapes[buffer_head].stroke_width = stroke_width_default;
      break;

    default:
      shapes[buffer_head].stroke_width = stroke_width_default;
      break;
  }

  ofLog() << "<new primitive at index: " << buffer_head << ">";

  buffer_head = ++buffer_head >= buffer_count ? 0: buffer_head; // boucler sur le tableau si plein
}

// fonction qui dessine un pixel
void Renderer::draw_pixel(float x, float y) const
{
  int pixel_x = floorf(x);
  int pixel_y = floorf(y);

  ofDrawRectangle(pixel_x, pixel_y, 1, 1);
}

// fonction qui dessine un point
void Renderer::draw_point(float x, float y, float radius) const
{
  ofDrawEllipse(x, y, radius, radius);
}

// fonction qui dessine une ligne
void Renderer::draw_line(float x1, float y1, float x2, float y2) const
{
  ofDrawLine(x1, y1, x2, y2);
}

// fonction qui dessine un rectangle
void Renderer::draw_rectangle(float x1, float y1, float x2, float y2) const
{
  ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

// fonction qui dessine une ellipse
void Renderer::draw_ellipse(float x1, float y1, float x2, float y2) const
{
  float diameter_x = x2 - x1;
  float diameter_y = y2 - y1;

  ofDrawEllipse(x1 + diameter_x / 2.0f, y1 + diameter_y / 2.0f, diameter_x, diameter_y);
}

// fonction qui détermine une couleur aléatoire pour les lignes de contour
void Renderer::random_color_stroke()
{
  stroke_color_r = (int) ofRandom(0, 255);
  stroke_color_g = (int) ofRandom(0, 255);
  stroke_color_b = (int) ofRandom(0, 255);
  stroke_color_a = 255;

  ofLog() << "<random color stroke>";
}

// fonction qui détermine une couleur aléatoire pour les zones de remplissage
void Renderer::random_color_fill()
{
  fill_color_r = (int) ofRandom(0, 255);
  fill_color_g = (int) ofRandom(0, 255);
  fill_color_b = (int) ofRandom(0, 255);
  fill_color_a = 255;

  ofLog() << "<random color fill>";
}

void Renderer::draw_zone(float x1, float y1, float x2, float y2) const
{
  float x2_clamp = min(max(0.0f, x2), (float) ofGetWidth());
  float y2_clamp = min(max(0.0f, y2), (float) ofGetHeight());

  ofSetLineWidth(radius);
  ofSetColor(255);
  ofNoFill();
  ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
  ofFill();
  ofDrawEllipse(x1, y1, radius, radius);
  ofDrawEllipse(x1, y2_clamp, radius, radius);
  ofDrawEllipse(x2_clamp, y1, radius, radius);
  ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

void Renderer::draw_cursor(float x, float y) const
{
  float length = 10.0f;
  float offset = 5.0f;

  ofSetLineWidth(2);
  ofSetColor(31);
  ofDrawLine(x + offset, y, x + offset + length, y);
  ofDrawLine(x - offset, y, x - offset - length, y);
  ofDrawLine(x, y + offset, x, y + offset + length);
  ofDrawLine(x, y - offset, x, y - offset - length);
}

Renderer::~Renderer()
{
  std::free(shapes);
}
