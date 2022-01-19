#include "greyscale_filter.h"

GreyScaleFilter::GreyScaleFilter() {}
GreyScaleFilter::~GreyScaleFilter() {}

void GreyScaleFilter::ApplyAtPixel(Color &p) {
  float lum = p.GetLuminance();
  p.setRGBA(lum, lum, lum, p.getA());
}
