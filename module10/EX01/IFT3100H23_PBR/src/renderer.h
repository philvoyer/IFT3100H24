// IFT3100H23_PBR/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Renderer
{
public:

  ofShader shader;

  ofColor material_color_ambient;
  ofColor material_color_diffuse;
  ofColor material_color_specular;

  float material_metallic;
  float material_roughness;
  float material_occlusion;
  float material_brightness;

  glm::vec3 material_fresnel_ior;

  ofImage texture_diffuse;
  ofImage texture_metallic;
  ofImage texture_roughness;
  ofImage texture_occlusion;

  ofLight light;
  ofColor light_color;
  float light_intensity;
  bool light_motion;

  float tone_mapping_exposure;
  float tone_mapping_gamma;
  bool tone_mapping_toggle;

  ofxAssimpModelLoader teapot;

  ofVec3f position_cube;
  ofVec3f position_sphere;
  ofVec3f position_teapot;

  float scale_cube;
  float scale_sphere;
  float scale_teapot;

  float speed_motion;
  float speed_rotation;

  float offset_x;
  float offset_z;

  float delta_x;
  float delta_y;
  float delta_z;

  float rotation_y;

  float initial_x;
  float initial_z;

  float center_x;
  float center_y;

  void setup();
  void update();
  void draw();
  void reset();
};
