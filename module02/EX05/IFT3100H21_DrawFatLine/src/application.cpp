// IFT3100H21_DrawFatLine/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  renderer.setup();

  switch (renderer.line_renderer)
  {
    case LineRenderer::dda:
      ofSetWindowTitle("rastérisation de lignes (DDA)");
      break;

    case LineRenderer::bresenham:
      ofSetWindowTitle("rastérisation de lignes (Bresenham)");
      break;

    default:
      break;
  }
}

void Application::draw()
{
  renderer.draw();
}

void Application::mouseMoved(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;
}

void Application::mouseDragged(int x, int y, int button)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;
}

void Application::mousePressed(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = true;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  renderer.mouse_press_x = x;
  renderer.mouse_press_y = y;

  if (renderer.is_position_inside_rectangle(x, y, 0, 0, renderer.framebuffer_width, renderer.framebuffer_height))
  {
    int fatPixelIndex = renderer.fat_pixel_index_by_position(x, y);

    renderer.change_fat_pixel_state(fatPixelIndex, PixelState::on);
  }

  ofLog() << "<app::mouse press at: (" << x << ", " << y << ")>";
}

void Application::mouseReleased(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = false;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  if (renderer.is_position_inside_rectangle(x, y, 0, 0, renderer.framebuffer_width, renderer.framebuffer_height))
  {
    int fatPixelIndex1 = renderer.fat_pixel_index_by_position(renderer.mouse_press_x, renderer.mouse_press_y);
    int fatPixelIndex2 = renderer.fat_pixel_index_by_position(renderer.mouse_current_x, renderer.mouse_current_y);

    int x1 = fatPixelIndex1 % renderer.fat_pixel_grid_height;
    int y1 = fatPixelIndex1 / renderer.fat_pixel_grid_width;
    int x2 = fatPixelIndex2 % renderer.fat_pixel_grid_height;
    int y2 = fatPixelIndex2 / renderer.fat_pixel_grid_width;

    switch (renderer.line_renderer)
    {
      case LineRenderer::dda:
        renderer.raster_line_dda(x1, y1, x2, y2);
        break;

      case LineRenderer::bresenham:
        renderer.raster_line_bresenham(x1, y1, x2, y2);
        break;

      default:
        break;
    }

    renderer.change_fat_pixel_state(fatPixelIndex1, PixelState::start);
    renderer.change_fat_pixel_state(fatPixelIndex2, PixelState::end);
  }

  ofLog() << "<app::mouse release at: (" << x << ", " << y << ")>";
}

void Application::mouseEntered(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;
}

void Application::mouseExited(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49:  // touche 1
      renderer.line_renderer = LineRenderer::dda;
      ofSetWindowTitle("rastérisation de lignes (DDA)");
      ofLog() << "<mode: dda>";
      break;

    case 50:  // touche 2
      renderer.line_renderer = LineRenderer::bresenham;
      ofSetWindowTitle("rastérisation de lignes (Bresenham)");
      ofLog() << "<mode: bresenham>";
      break;

    case 114: // touche r
      renderer.reset();
      break;

    default:
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
