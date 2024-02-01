// IFT3100H24_Interface/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("interface (u)");
  ofNoFill();

  ofLog() << "<app::setup>";

  renderer.setup();

  gui.setup("interface");

  group_draw.setup("outils de dessin");

  color_picker_background.set("couleur du canevas", ofColor(31), ofColor(0, 0), ofColor(255, 255));
  color_picker_stroke.set("couleur du trait", ofColor(255), ofColor(0, 0), ofColor(255, 255));

  slider_stroke_weight.set("largeur de la ligne", 4.0f, 0.0f, 10.0f);

  group_draw.add(color_picker_background);
  group_draw.add(color_picker_stroke);
  group_draw.add(slider_stroke_weight);

  gui.add(&group_draw);

  textbox.set("text", "ift3100");
  gui.add(textbox);

  button.setup("button");
  button.addListener(this, &Application::button_pressed);
  gui.add(&button);

  checkbox.setName("visible");
  gui.add(checkbox);

  checkbox = true;
}

void Application::update()
{
  // assigner les états courants de l'interface
  renderer.background_color = color_picker_background;
  renderer.stroke_color = color_picker_stroke;
  renderer.stroke_weight = slider_stroke_weight;
  renderer.text = textbox;

  renderer.update();
}

void Application::draw()
{
  renderer.draw();

  if (checkbox)
    gui.draw();
}

void Application::keyReleased(int key)
{
  if (key == 117) // touche u
  {
    checkbox = !checkbox;
    ofLog() << "<toggle ui: " << checkbox << ">";
  }
}

void Application::button_pressed()
{
  // réinitialiser la zone de texte
  textbox.set("text", "ift3100");

  ofLog() << "<button pressed>";
}

void Application::windowResized(int w, int h)
{
  ofLog() << "<app::windowResized: (" << w << ", " << h << ")>";
}

void Application::exit()
{
  button.removeListener(this, &Application::button_pressed);

  ofLog() << "<app::exit>";
}
