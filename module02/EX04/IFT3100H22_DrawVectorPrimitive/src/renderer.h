// IFT3100H22_DrawVectorPrimitive/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// énumération des différents types de primitives vectorielles
enum class VectorPrimitiveType {none, pixel, point, line, rectangle, ellipse};

// structure de primitive vectorielle générique
struct VectorPrimitive
{
  VectorPrimitiveType type;            // 1 * 4 = 4  octets
  float               position1[2];    // 2 * 4 = 8  octets
  float               position2[2];    // 2 * 4 = 8  octets
  float               stroke_width;    // 1 * 4 = 4  octets
  unsigned char       stroke_color[4]; // 4 * 1 = 4  octets
  unsigned char       fill_color[4];   // 4 * 1 = 4  octets
};                                     //       = 32 octets

class Renderer
{
public:

  VectorPrimitiveType draw_mode;

  VectorPrimitive* shapes;

  int index;

  int buffer_count;
  int buffer_stride;
  int buffer_size;
  int buffer_head;

  int mouse_press_x;
  int mouse_press_y;

  int mouse_current_x;
  int mouse_current_y;

  float stroke_width_default;
  float radius;

  unsigned char stroke_color_r;
  unsigned char stroke_color_g;
  unsigned char stroke_color_b;
  unsigned char stroke_color_a;

  unsigned char fill_color_r;
  unsigned char fill_color_g;
  unsigned char fill_color_b;
  unsigned char fill_color_a;

  bool is_mouse_button_pressed;

  void setup();
  void draw();

  void reset();

  void add_vector_shape(VectorPrimitiveType type);

  void draw_pixel(float x, float y) const;
  void draw_point(float x, float y, float radius) const;
  void draw_line(float x1, float y1, float x2, float y2) const;
  void draw_rectangle(float x1, float y1, float x2, float y2) const;
  void draw_ellipse(float x1, float y1, float x2, float y2) const;

  void random_color_stroke();
  void random_color_fill();

  void draw_zone(float x1, float y1, float x2, float y2) const;
  void draw_cursor(float x, float y) const;

  ~Renderer();
};
