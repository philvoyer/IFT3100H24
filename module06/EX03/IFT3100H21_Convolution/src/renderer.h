// IFT3100H21_Convolution/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include <array>

// énumération des types de kernel de convolution
enum class ConvolutionKernel
{
  identity,
  emboss,
  sharpen,
  edge_detect,
  blur
};

// kernel de convolution (3x3) : identité
const std::array<float, 9> convolution_kernel_identity
{
  0.0f,  0.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  0.0f,  0.0f
};

// kernel de convolution (3x3) : aiguiser
const std::array<float, 9> convolution_kernel_sharpen
{
  0.0f, -1.0f,  0.0f,
 -1.0f,  5.0f, -1.0f,
  0.0f, -1.0f,  0.0f
};

// kernel de convolution (3x3) : détection de bordure
const std::array<float, 9> convolution_kernel_edge_detect
{
  0.0f,  1.0f,  0.0f,
  1.0f, -4.0f,  1.0f,
  0.0f,  1.0f,  0.0f
};

// kernel de convolution (3x3) : bosseler
const std::array<float, 9> convolution_kernel_emboss
{
 -2.0f, -1.0f,  0.0f,
 -1.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  2.0f
};

// kernel de convolution (3x3) : flou
const std::array<float, 9> convolution_kernel_blur
{
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f,
  1.0f / 9.0f,  1.0f / 9.0f,  1.0f / 9.0f
};

class Renderer
{
public:

  ConvolutionKernel kernel_type;

  string kernel_name;

  ofImage image_source;
  ofImage image_destination;

  int image_width;
  int image_height;

  int offset_vertical;
  int offset_horizontal;

  void setup();
  void draw();

  void filter();
};
