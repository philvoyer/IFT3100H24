// IFT3100H24_CurveHermite/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

// fonction d'évaluation d'une courbe de hermite (4 points de contrôle)
void hermite(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float p4x, float p4y, float p4z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;
  float uu = u * u;
  float uuu = uu * u;
  float tt = t * t;
  float ttt = tt * t;

  x = (2 * ttt - 3 * tt + 1) * p1x + (ttt - 2 * tt + t) * p2x + (ttt - tt) * p3x + (-2 * ttt + 3 * tt) * p4x;
  y = (2 * ttt - 3 * tt + 1) * p1y + (ttt - 2 * tt + t) * p2y + (ttt - tt) * p3y + (-2 * ttt + 3 * tt) * p4y;
  z = (2 * ttt - 3 * tt + 1) * p1z + (ttt - 2 * tt + t) * p2z + (ttt - tt) * p3z + (-2 * ttt + 3 * tt) * p4z;
}

// fonction d'évaluation d'une courbe de Bézier cubique (4 points de contrôle)
void bezier_cubic(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float p4x, float p4y, float p4z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;
  float uu = u * u;
  float uuu = uu * u;
  float tt = t * t;
  float ttt = tt * t;

  x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
  y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
  z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
}

// fonction d'oscillation
float oscillate(float time, float frequency, float amplitude)
{
  return sinf(time * 2.0f * PI / frequency) * amplitude;
}

// fonction qui calcule une interpolation linéaire entre deux valeurs numériques
float interpolation_linear(float value1, float value2, float t)
{
  if (t < 0.0f)
    return value1;

  if (t > 1.0f)
    return value2;

  return (1.0f - t) * value1 + t * value2;
}

// fonction qui calcule une interpolation entre deux valeurs numériques avec la fonction 'smoothstep'
float interpolation_smoothstep(float value1, float value2, float t)
{
  if (t < 0.0f)
    return t = 0.0f;

  if (t > 1.0f)
    return t = 1.0f;

  t = t * t * (3.0f - 2.0f * t);

  return (1.0 - t) * value1 + t * value2;
}

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(0);

  // paramètres
  line_resolution = 100;
  line_width_outline = 4.0f;
  line_width_curve = 8.0f;

  radius = 32.0f;
  scale = 10.0f;
  offset = 64.0f;

  motion_speed = 250.0f;

  oscillation = 0.5f;
  oscillation_frequency = 5000.0f;
  oscillation_amplitude = 0.5;

  isAnimationActive = true;

  // initialisation des sommets de la ligne
  for (index = 0; index <= line_resolution; ++index)
    line_renderer.addVertex(ofPoint());

  // courbe au lancement de l'application
  curve_type = CurveType::hermite;

  // type d'interpolation au lancement de l'application
  interpolation_type = InterpolationType::lerp;

  // initialisation de la scène
  reset();
}

void Renderer::reset()
{
  // initialisation des variables
  framebuffer_width = ofGetWidth();
  framebuffer_height = ofGetHeight();

  // ratios de positionnement dans la fenêtre
  float w_1_8 = framebuffer_width / 8.0f;
  float w_1_4 = framebuffer_width / 4.0f;
  float w_1_2 = framebuffer_width / 2.0f;
  float w_3_4 = framebuffer_width * 3.0f / 4.0f;
  float w_7_8 = framebuffer_width * 7.0f / 8.0f;
  float h_1_5 = framebuffer_height / 5.0f;
  float h_1_3 = framebuffer_height / 3.0f;
  float h_4_5 = framebuffer_height * 4.0f / 5.0f;

  initial_position1 = {w_1_8, h_4_5, 0};
  initial_position2 = {w_1_4, h_1_3, 0};
  initial_position3 = {w_1_2, h_1_5, 0};
  initial_position4 = {w_3_4, h_1_3, 0};
  initial_position5 = {w_7_8, h_4_5, 0};

  // paramètres selon le type de courbe
  switch (curve_type)
  {
    case CurveType::hermite:

      curve_name = "Hermite cubique";

      ctrl_point1 = initial_position1;
      ctrl_point2 = initial_position2;
      ctrl_point3 = initial_position4;
      ctrl_point4 = initial_position5;

      selected_ctrl_point = &ctrl_point2;

      break;

    case CurveType::bezier_cubic:

      curve_name = "Bézier cubique";

      ctrl_point1 = initial_position1;
      ctrl_point2 = initial_position2;
      ctrl_point3 = initial_position4;
      ctrl_point4 = initial_position5;

      selected_ctrl_point = &ctrl_point2;

      break;

    default:
      break;
  }

  delta_x = motion_speed;
  delta_y = motion_speed;

  ofLog() << "<reset>";
}

void Renderer::update()
{
  // approximation de la courbe avec une séquence de lignes
  for (index = 0; index <= line_resolution; ++index)
  {
    // paramètres selon le type de courbe
    switch (curve_type)
    {
      case CurveType::hermite:

        tangent1 = ctrl_point2 - ctrl_point1;
        tangent2 = ctrl_point3 - ctrl_point4;

        hermite(
          index / (float) line_resolution,
          ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
          tangent1.x, tangent1.y, tangent1.z,
          tangent2.x, tangent2.y, tangent2.z,
          ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
          position.x, position.y, position.z);

        break;

      case CurveType::bezier_cubic:

        bezier_cubic(
          index / (float) line_resolution,
          ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
          ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
          ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
          ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
          position.x, position.y, position.z);

        break;

      default:
        break;
    }

    // affecter la position du point sur la courbe
    line_renderer[index] = position;
  }

  // mise à jour de l'oscillateur
  if (isAnimationActive)
    oscillation = oscillation_amplitude + oscillate(ofGetElapsedTimeMillis(), oscillation_frequency, oscillation_amplitude);

  // animation de la tête de lecture en fonction de la valeur courante de l'oscillateur
  switch (interpolation_type)
  {
    case InterpolationType::lerp:
      playhead = interpolation_linear(0.0f, 1.0f, oscillation);
      break;

    case InterpolationType::smoothstep:
      playhead = interpolation_smoothstep(0.0f, 1.0f, oscillation);
      break;

    default:
      break;
  }

  // calculer la position courante de l'animation sur la courbe
  switch (curve_type)
  {
    case CurveType::hermite:

      hermite(
        playhead,
        ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
        tangent1.x, tangent1.y, tangent1.z,
        tangent2.x, tangent2.y, tangent2.z,
        ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
        playhead_position.x, playhead_position.y, playhead_position.z);

      break;

    case CurveType::bezier_cubic:

      bezier_cubic(
        playhead,
        ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
        ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
        ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
        ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
        playhead_position.x, playhead_position.y, playhead_position.z);

      break;

    default:
      break;
  }
}

void Renderer::draw()
{
  // dessiner les positions initiales
  ofSetColor(63, 63, 63);
  ofDrawEllipse(initial_position1.x, initial_position1.y, radius / 2.0f, radius / 2.0f);
  ofDrawEllipse(initial_position2.x, initial_position2.y, radius / 2.0f, radius / 2.0f);
  ofDrawEllipse(initial_position3.x, initial_position3.y, radius / 2.0f, radius / 2.0f);
  ofDrawEllipse(initial_position4.x, initial_position4.y, radius / 2.0f, radius / 2.0f);
  ofDrawEllipse(initial_position5.x, initial_position5.y, radius / 2.0f, radius / 2.0f);

  // dessiner la ligne contour
  ofSetColor(0, 0, 255);
  ofSetLineWidth(line_width_outline);
  ofDrawLine(ctrl_point1.x, ctrl_point1.y, ctrl_point2.x, ctrl_point2.y);
  ofDrawLine(ctrl_point3.x, ctrl_point3.y, ctrl_point4.x, ctrl_point4.y);

  if (curve_type == CurveType::bezier_cubic)
  {
    ofDrawLine(ctrl_point2.x, ctrl_point2.y, ctrl_point3.x, ctrl_point3.y);
    ofDrawLine(ctrl_point4.x, ctrl_point4.y, ctrl_point1.x, ctrl_point1.y);
  }

  // dessiner la courbe
  ofSetColor(0, 255, 0);
  ofSetLineWidth(line_width_curve);
  line_renderer.draw();

  // dessiner les points de contrôle
  ofSetColor(255, 0, 0);
  ofDrawEllipse(ctrl_point1.x, ctrl_point1.y, radius, radius);
  ofDrawEllipse(ctrl_point2.x, ctrl_point2.y, radius, radius);
  ofDrawEllipse(ctrl_point3.x, ctrl_point3.y, radius, radius);
  ofDrawEllipse(ctrl_point4.x, ctrl_point4.y, radius, radius);

  // dessiner un repère à la position courante de l'animation sur la courbe
  ofSetColor(255);
  ofDrawEllipse(playhead_position.x, playhead_position.y, radius / 1.0f, radius / 1.0f);
}
