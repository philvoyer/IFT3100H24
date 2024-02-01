// IFT3100H24_DrawFatLine/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// énumération de différents états que peut avoir un gros pixel
enum class PixelState {none, on, off, start, end, preview};

// énumération de différents algorithmes de rastérisation de ligne
enum class LineRenderer {none, dda, bresenham};

// structure de primitive vectorielle générique
struct FatPixel
{
  PixelState    state;       // 1 * 4 = 4  octets
  float         position[2]; // 2 * 4 = 8  octets
  unsigned char color[4];    // 4 * 1 = 4  octets
};                           //       = 16 octets

class Renderer
{
public:

  LineRenderer line_renderer;

  FatPixel* fat_pixels;

  int pixel_count;

  int fat_pixel_resolution;

  int fat_pixel_grid_width;
  int fat_pixel_grid_height;

  int buffer_count;
  int buffer_size;
  int buffer_stride;

  int mouse_press_x;
  int mouse_press_y;

  int mouse_current_x;
  int mouse_current_y;

  int framebuffer_width;

  int framebuffer_height;

  int index;

  float stroke_width_default;

  float radius;

  unsigned char stroke_color_on_r;
  unsigned char stroke_color_on_g;
  unsigned char stroke_color_on_b;
  unsigned char stroke_color_on_a;

  unsigned char stroke_color_off_r;
  unsigned char stroke_color_off_g;
  unsigned char stroke_color_off_b;
  unsigned char stroke_color_off_a;

  unsigned char stroke_color_preview_r;
  unsigned char stroke_color_preview_g;
  unsigned char stroke_color_preview_b;
  unsigned char stroke_color_preview_a;

  bool is_mouse_button_pressed;

  void setup();

  void draw();

  void reset();

  void change_fat_pixel_state(int index, PixelState state);

  bool is_position_inside_rectangle(int x, int y, int x1, int y1, int x2, int y2) const;

  int fat_pixel_index_by_coord(int x, int y) const;

  int fat_pixel_index_by_position(int x, int y) const;

  void raster_line_dda(int x1, int y1, int x2, int y2);

  void raster_line_bresenham(int x1, int y1, int x2, int y2);

  void draw_fat_pixel(float x, float y, float diameter) const;

  void draw_grid(int cell_size) const;

  void draw_line(float x1, float y1, float x2, float y2) const;

  void draw_rectangle(float x1, float y1, float x2, float y2) const;

  void draw_zone(float x1, float y1, float x2, float y2) const;

  void draw_cursor(float x, float y) const;

  ~Renderer();
};
