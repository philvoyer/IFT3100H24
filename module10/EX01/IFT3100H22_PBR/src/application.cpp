// IFT3100H22_PBR/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  ofSetWindowTitle("modèle d'illumination PBR (Cook-Torrance GGX) (↑↓←→ q e m u r)");

  is_key_press_up = false;
  is_key_press_down = false;
  is_key_press_left = false;
  is_key_press_right = false;
  is_key_press_q = false;
  is_key_press_e = false;

  toggle_ui = true;

  renderer.setup();

  reset();

  gui.setup("pbr material");

  // interface pour les couleurs du matériau
  group_material_color.setup("color");

  group_material_color.add(color_picker_ambient);
  group_material_color.add(color_picker_diffuse);
  group_material_color.add(color_picker_specular);

  gui.add(&group_material_color);

  // interface pour les facteurs numériques du matériau
  group_material_factor.setup("factor");

  group_material_factor.add(slider_metallic);
  group_material_factor.add(slider_roughness);
  group_material_factor.add(slider_occlusion);
  group_material_factor.add(slider_brightness);

  group_material_factor.add(slider_fresnel_ior);

  gui.add(&group_material_factor);

  // interface pour les paramètres de la lumière
  group_light.setup("light");

  group_light.add(color_picker_light_color);
  group_light.add(slider_light_intensity);
  group_light.add(toggle_light_motion);

  gui.add(&group_light);

  // interface pour les paramètres de mappage tonal
  group_tone_mapping.setup("tone mapping");

  group_tone_mapping.add(slider_exposure);
  group_tone_mapping.add(slider_gamma);
  group_tone_mapping.add(toggle_tone_mapping);

  gui.add(&group_tone_mapping);

  // interface pour les options de l'application
  toggle_ui.setName("hide ui");
  gui.add(toggle_ui);

  button_reset.setup("reset");
  button_reset.addListener(this, &Application::button_reset_pressed);
  gui.add(&button_reset);
}

void Application::reset()
{
  renderer.reset();

  color_picker_ambient.set("ambient", renderer.material_color_ambient, ofColor(0, 0), ofColor(255, 255));
  color_picker_diffuse.set("diffuse", renderer.material_color_diffuse, ofColor(0, 0), ofColor(255, 255));
  color_picker_specular.set("specular", renderer.material_color_specular, ofColor(0, 0), ofColor(255, 255));

  slider_metallic.set("metallic", renderer.material_metallic, 0.0f, 1.0f);
  slider_roughness.set("roughness", renderer.material_roughness, 0.0f, 1.0f);
  slider_occlusion.set("occlusion", renderer.material_occlusion, 0.0f, 5.0f);
  slider_brightness.set("brightness", renderer.material_brightness, 0.0f, 5.0f);

  slider_fresnel_ior.set("fresnel ior", renderer.material_fresnel_ior, glm::vec3(0.0f), glm::vec3(1.0f));

  color_picker_light_color.set("color", renderer.light_color, ofColor(0, 0), ofColor(255, 255));
  slider_light_intensity.set("intensity", renderer.light_intensity, 0.0f, 100.0f);
  toggle_light_motion.set("motion", renderer.light_motion);

  slider_exposure.set("exposure", 1.0f, 0.0f, 5.0f);
  slider_gamma.set("gamma", 2.2f, 0.0f, 5.0f);

  if (renderer.tone_mapping_toggle)
    toggle_tone_mapping.set("aces filmic", true);
  else
    toggle_tone_mapping.set("reinhard", false);
}

void Application::update()
{
  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

  if (is_key_press_up)
    renderer.offset_z += renderer.delta_z * time_elapsed;
  if (is_key_press_down)
    renderer.offset_z -= renderer.delta_z * time_elapsed;
  if (is_key_press_left)
    renderer.offset_x += renderer.delta_x * time_elapsed;
  if (is_key_press_right)
    renderer.offset_x -= renderer.delta_x * time_elapsed;
  if (is_key_press_q)
    renderer.rotation_y += renderer.delta_y * time_elapsed;
  if (is_key_press_e)
    renderer.rotation_y -= renderer.delta_y * time_elapsed;

  renderer.material_color_ambient = color_picker_ambient;
  renderer.material_color_diffuse = color_picker_diffuse;
  renderer.material_color_specular = color_picker_specular;

  renderer.material_metallic = slider_metallic;
  renderer.material_roughness = slider_roughness;
  renderer.material_occlusion = slider_occlusion;
  renderer.material_brightness = slider_brightness;

  renderer.material_fresnel_ior = slider_fresnel_ior;

  renderer.light_color = color_picker_light_color;
  renderer.light_intensity = slider_light_intensity;
  renderer.light_motion = toggle_light_motion;

  renderer.tone_mapping_exposure = slider_exposure;
  renderer.tone_mapping_gamma = slider_gamma;
  renderer.tone_mapping_toggle = toggle_tone_mapping;

  if (renderer.tone_mapping_toggle)
    toggle_tone_mapping.set("aces filmic", true);
  else
    toggle_tone_mapping.set("reinhard", false);

  renderer.update();
}

void Application::draw()
{
  renderer.draw();

  if (toggle_ui)
    gui.draw();
}

void Application::keyPressed(int key)
{
  switch (key)
  {
    case 97:  // touche a
      is_key_press_left = true;
      break;

    case 100: // touche d
      is_key_press_right = true;
      break;

    case 101: // touche q
      is_key_press_q = true;
      break;

    case 113: // touche e
      is_key_press_e = true;
      break;

    case 115: // touche s
      is_key_press_down = true;
      break;

    case 119: // touche w
      is_key_press_up = true;
      break;

    case OF_KEY_LEFT:  // touche ←
      is_key_press_left = true;
      break;

    case OF_KEY_UP:    // touche ↑
      is_key_press_up = true;
      break;

    case OF_KEY_RIGHT: // touche →
      is_key_press_right = true;
      break;

    case OF_KEY_DOWN:  // touche ↓
      is_key_press_down = true;
      break;

    default:
      break;
  }
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 97:  // touche a
      is_key_press_left = false;
      break;

    case 100: // touche d
      is_key_press_right = false;
      break;

    case 101: // touche q
      is_key_press_q = false;
      break;

    case 109: // touche m
      toggle_light_motion = !toggle_light_motion;
      ofLog() << "<toggle light motion: " << toggle_light_motion << ">";
      break;

    case 113: // touche e
      is_key_press_e = false;
      break;

    case 114: // touche r
      reset();
      ofLog() << "<reset renderer>";
      break;

    case 115: // touche s
      is_key_press_down = false;
      break;

    case 117: // touche u
      toggle_ui = !toggle_ui;
      ofLog() << "<toggle ui: " << toggle_ui << ">";
      break;

    case 119: // touche w
      is_key_press_up = false;
      break;

    case OF_KEY_LEFT:  // touche ←
      is_key_press_left = false;
      break;

    case OF_KEY_UP:    // touche ↑
      is_key_press_up = false;
      break;

    case OF_KEY_RIGHT: // touche →
      is_key_press_right = false;
      break;

    case OF_KEY_DOWN:  // touche ↓
      is_key_press_down = false;
      break;

    default:
      break;
  }
}

void Application::mouseReleased(int x, int y, int button){}

void Application::windowResized(int w, int h)
{
  ofLog() << "<app::windowResized: (" << w << ", " << h << ")>";
}

void Application::button_reset_pressed()
{
  reset();
}

void Application::exit()
{
  button_reset.removeListener(this, &Application::button_reset_pressed);

  ofLog() << "<app::exit>";
}
