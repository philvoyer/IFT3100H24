// IFT3100H20_DrawFatLine/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(191);

  // prendre une copie de la résolution du framebuffer
  framebuffer_width = ofGetWidth();
  framebuffer_height = ofGetHeight();

  // nombre de pixels en largeur et en hauteur
  pixel_count = 16;

  // déterminer la résolution des gros pixels
  fat_pixel_resolution = framebuffer_width / pixel_count;

  // déterminer la résolution de la grille de gros pixels
  fat_pixel_grid_width = framebuffer_width / fat_pixel_resolution;

  // déterminer la résolution de la grille de gros pixels
  fat_pixel_grid_height = framebuffer_height / fat_pixel_resolution;

  // nombre maximal de gros pixels dans l'image
  buffer_count = fat_pixel_grid_width * fat_pixel_grid_height;

  // calculer la taille de la structure commune à tous les gros pixels
  buffer_stride = sizeof(FatPixel);

  // calculer le nombre d'octets à allouer pour un tableau contenant tous les gros pixels de l'image
  buffer_size = buffer_count * buffer_stride;

  // allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des gros pixels de l'image
  fat_pixels = (FatPixel*) std::malloc(buffer_size);

  // initialisation des variables

  line_renderer = LineRenderer::bresenham;

  stroke_color_on_r = 255;
  stroke_color_on_g = 255;
  stroke_color_on_b = 255;
  stroke_color_on_a = 255;

  stroke_color_off_r = 63;
  stroke_color_off_g = 63;
  stroke_color_off_b = 63;
  stroke_color_off_a = 255;

  stroke_color_preview_r = 127;
  stroke_color_preview_g = 127;
  stroke_color_preview_b = 127;
  stroke_color_preview_a = 255;

  stroke_width_default = 2.0f;

  radius = 4.0f;

  mouse_press_x = mouse_press_y = 0;
  mouse_current_x = mouse_current_y = 0;

  is_mouse_button_pressed = false;

  reset();
}

void Renderer::draw()
{
  ofFill();
  ofSetColor(255);

  for (index = 0; index < buffer_count; ++index)
  {
    draw_fat_pixel(
      fat_pixels[index].position[0],
      fat_pixels[index].position[1],
      fat_pixel_resolution);
  }

  ofSetColor(191);

  draw_grid(fat_pixel_resolution);

  if (is_mouse_button_pressed)
  {
    draw_zone(
      mouse_press_x,
      mouse_press_y,
      mouse_current_x,
      mouse_current_y);

    ofSetLineWidth(3);
    ofSetColor(191, 191, 255);

    draw_line(
      mouse_press_x,
      mouse_press_y,
      mouse_current_x,
      mouse_current_y);
  }

  draw_cursor(mouse_current_x, mouse_current_y);
}

// fonction qui initialise les gros pixels de l'image
void Renderer::reset()
{
  int index_x;
  int index_y;

  for (index = 0; index < buffer_count; ++index)
  {
    index_x = index % fat_pixel_grid_width;
    index_y = index / fat_pixel_grid_width;

    fat_pixels[index].position[0] = index_x * fat_pixel_resolution;
    fat_pixels[index].position[1] = index_y * fat_pixel_resolution;

    change_fat_pixel_state(index, PixelState::off);
  }

  ofLog() << "<reset>";
}

// fonction qui manipule les attributs d'un des gros pixels de l'image
void Renderer::change_fat_pixel_state(int index, PixelState state)
{
  int index_x;
  int index_y;

  fat_pixels[index].state = state;

  switch (fat_pixels[index].state)
  {
    case PixelState::on:

      fat_pixels[index].color[0] = stroke_color_on_r;
      fat_pixels[index].color[1] = stroke_color_on_g;
      fat_pixels[index].color[2] = stroke_color_on_b;
      fat_pixels[index].color[3] = stroke_color_on_a;
      break;

    case PixelState::off:

      index_x = index % fat_pixel_grid_width;
      index_y = index / fat_pixel_grid_width;

      if ((index_x + index_y) % 2 == 0)
      {
        fat_pixels[index].color[0] = 63 + stroke_color_off_r;
        fat_pixels[index].color[1] = 63 + stroke_color_off_g;
        fat_pixels[index].color[2] = 63 + stroke_color_off_b;
        fat_pixels[index].color[3] = stroke_color_off_a;
      }
      else
      {
        fat_pixels[index].color[0] = stroke_color_off_r;
        fat_pixels[index].color[1] = stroke_color_off_g;
        fat_pixels[index].color[2] = stroke_color_off_b;
        fat_pixels[index].color[3] = stroke_color_off_a;
      }
      break;

    case PixelState::start:

      fat_pixels[index].color[0] = 255;
      fat_pixels[index].color[1] = 0;
      fat_pixels[index].color[2] = 0;
      fat_pixels[index].color[3] = 255;
      break;

    case PixelState::end:

      fat_pixels[index].color[0] = 0;
      fat_pixels[index].color[1] = 255;
      fat_pixels[index].color[2] = 0;
      fat_pixels[index].color[3] = 255;
      break;

    case PixelState::preview:

      fat_pixels[index].color[0] = stroke_color_preview_r;
      fat_pixels[index].color[1] = stroke_color_preview_g;
      fat_pixels[index].color[2] = stroke_color_preview_b;
      fat_pixels[index].color[3] = stroke_color_preview_a;
      break;

    case PixelState::none:
    default:
      break;
  }
}

// fonction qui détermine si une position 2D est à l'intérieur d'une zone rectangulaire
bool Renderer::is_position_inside_rectangle(int x, int y, int x1, int y1, int x2, int y2) const
{
  if (x < x1)
    return false;
  if (x > x2)
    return false;
  if (y < y1)
    return false;
  if (y > y2)
    return false;
  return true;
}

// fonction qui détermine l'index d'un gros pixel à partir d'une coordonnée en X et Y dans l'espace de l'image
int Renderer::fat_pixel_index_by_coord(int x, int y) const
{
  return y * fat_pixel_grid_width + x;
}

// fonction qui détermine l'index d'un gros pixel à partir d'une position dans l'espace de la fenêtre
int Renderer::fat_pixel_index_by_position(int x, int y) const
{
  int index_x = floor(x / (float) fat_pixel_resolution);
  int index_y = floor(y / (float) fat_pixel_resolution);

  return index_y * fat_pixel_grid_width + index_x;
}

// fonction qui dessine une ligne par rastérisation avec l'algorithme de DDA
void Renderer::raster_line_dda(int x1, int y1, int x2, int y2)
{
  int index;
  int count;

  int delta_x = x2 - x1;
  int delta_y = y2 - y1;

  float length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

  if (length < 1.0f)
    return;

  float step_x = delta_x / length;
  float step_y = delta_y / length;

  float x = x1 + 0.5f;
  float y = y1 + 0.5f;

  for (count = 1; count <= length; ++count)
  {
    index = fat_pixel_index_by_coord(static_cast<int>(x), static_cast<int>(y));

    change_fat_pixel_state(index, PixelState::on);

    x += step_x;
    y += step_y;
  }

  ofLog() << "<rastérisation d'une ligne avec DDA entre : (" << x1 << ", " << y1 << ") et (" << x2 << ", " << y2 << ") avec " << count << " gros pixels>";
}

// fonction qui dessine une ligne par rastérisation avec l'algorithme de Bresenham
void Renderer::raster_line_bresenham(int x1, int y1, int x2, int y2)
{
  int index;
  int count = 0;

  int delta_x = abs(x2 - x1);
  int delta_y = abs(y2 - y1);

  int step_x = (x1 < x2 ? 1 : -1);
  int step_y = (y1 < y2 ? 1 : -1);

  int error = (delta_x > delta_y ? delta_x : -delta_y) / 2;
  int tmp;

  int x = x1;
  int y = y1;

  while (true)
  {
    ++count;

    index = fat_pixel_index_by_coord(x, y);

    change_fat_pixel_state(index, PixelState::on);

    if (x == x2 && y == y2)
      break;

    tmp = error;

    if (tmp > -delta_x)
    {
      error -= delta_y;
      x += step_x;
    }

    if (tmp < delta_y)
    {
      error += delta_x;
      y += step_y;
    }
  }

  ofLog() << "<rastérisation d'une ligne avec Bresensam entre : (" << x1 << ", " << y1 << ") et (" << x2 << ", " << y2 << ") avec " << count << " gros pixels>";
}

// fonction qui dessine un gros pixel
void Renderer::draw_fat_pixel(float x, float y, float diameter) const
{
  ofSetColor(
     fat_pixels[index].color[0],
     fat_pixels[index].color[1],
     fat_pixels[index].color[2],
     fat_pixels[index].color[3]);

  ofDrawRectangle(x, y, diameter, diameter);
}

// fonction qui dessine une grille
void Renderer::draw_grid(int cell_size) const
{
  int index;

  int subdivision_x = (int) framebuffer_width  / (float) cell_size;
  int subdivision_y = (int) framebuffer_height / (float) cell_size;

  for (index = 0; index <= subdivision_x; ++index)
  {
    if (index % 4 == 0)
      ofSetLineWidth(2);
    else
      ofSetLineWidth(1);

    ofDrawLine(index * cell_size, 0, index * cell_size, framebuffer_height);
  }

  for (index = 0; index <= subdivision_y; ++index)
  {
    if (index % 4 == 0)
      ofSetLineWidth(2);
    else
      ofSetLineWidth(1);

    ofDrawLine(0, index * cell_size, framebuffer_width, index * cell_size);
  }
}

void Renderer::draw_line(float x1, float y1, float x2, float y2) const
{
  ofDrawLine(x1, y1, x2, y2);
}

void Renderer::draw_rectangle(float x1, float y1, float x2, float y2) const
{
  ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
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
  std::free(fat_pixels);
}
