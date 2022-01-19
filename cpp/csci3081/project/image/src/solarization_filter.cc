#include "solarization_filter.h"
#include <math.h>
#define PI 3.14159265

SolarizationFilter::SolarizationFilter() {}
SolarizationFilter::~SolarizationFilter() {}

void SolarizationFilter::ApplyAtPixel(Color &p) {
  float r,g,b;
  r = 0.5*sin(p.getR()*10-PI/2)+0.5;
  g = 0.5*sin(p.getG()*10-PI/2)+0.5;
  b = 0.5*sin(p.getB()*10-PI/2)+0.5;

  if(r < 0){
    r = 0;
  }
  if(r > 1){
    r = 1;
  }
  if(g < 0){
    g = 0;
  }
  if(g > 1){
    g = 1;
  }
  if(b < 0){
    b = 0;
  }
  if(b > 1){
    b = 1;
  }

  p.setRGBA(r, g, b, p.getA());
}