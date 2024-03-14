// IFT3100H24_Convolution/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofLog() << "<app::setup>";

  renderer.setup();
}

void Application::update()
{
  ofSetWindowTitle("filtre de convolution : " + renderer.kernel_name + " (touches 1-5)");
}

void Application::draw()
{
  renderer.draw();
}

void Application::keyReleased(int key)
{
  switch (key)
  {
    case 49: // touche 1
      renderer.kernel_type = ConvolutionKernel::identity;
      renderer.kernel_name = "identité";
      break;

    case 50: // touche 2
      renderer.kernel_type = ConvolutionKernel::emboss;
      renderer.kernel_name = "bosseler";
      break;

    case 51: // touche 3
      renderer.kernel_type = ConvolutionKernel::sharpen;
      renderer.kernel_name = "aiguiser";
      break;

    case 52: // touche 4
      renderer.kernel_type = ConvolutionKernel::edge_detect;
      renderer.kernel_name = "détection de bordure";
      break;

    case 53: // touche 5
      renderer.kernel_type = ConvolutionKernel::blur;
      renderer.kernel_name = "flou";
      break;

    default:
      break;
  }

  // appliquer le filtre de convolution
  renderer.filter();
}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
