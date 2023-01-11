// IFT3100H23_DrawVectorPrimitive/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("dessin vectoriel (1-5, s, f, r)");

  ofLog() << "<app::setup>";

  renderer.setup();
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

  ofLog() << "<app::mouse pressed  at: (" << x << ", " << y << ")>";
}

void Application::mouseReleased(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = false;

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  renderer.add_vector_shape(renderer.draw_mode);

  ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";
}

void Application::mouseEntered(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse entered  at: (" << x << ", " << y << ")>";
}

void Application::mouseExited(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  ofLog() << "<app::mouse exited   at: (" << x << ", " << y << ")>";
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49:  // key 1
      renderer.draw_mode = VectorPrimitiveType::pixel;
      ofLog() << "<mode: pixel>";
      break;

    case 50:  // key 2
      renderer.draw_mode = VectorPrimitiveType::point;
      ofLog() << "<mode: point>";
      break;

    case 51:  // key 3
      renderer.draw_mode = VectorPrimitiveType::line;
      ofLog() << "<mode: line>";
      break;

    case 52:  // key 4
      renderer.draw_mode = VectorPrimitiveType::rectangle;
      ofLog() << "<mode: rectangle>";
      break;

    case 53:  // key 5
      renderer.draw_mode = VectorPrimitiveType::ellipse;
      ofLog() << "<mode: ellipse>";
      break;

    case 102: // key f
      renderer.random_color_fill();
      break;

    case 114: // key r
      renderer.reset();
      break;

    case 115: // key s
      renderer.random_color_stroke();
      break;

    default:
      break;
  }
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
