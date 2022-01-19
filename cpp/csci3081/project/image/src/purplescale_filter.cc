#include "purplescale_filter.h"

PurpleScaleFilter::PurpleScaleFilter() {}
PurpleScaleFilter::~PurpleScaleFilter() {}

void PurpleScaleFilter::ApplyAtPixel(Color &p) {
  float lum = p.GetLuminance();
  p.setRGBA(lum, lum, lum, p.getA());
  Color purple(1.0f, 0.0f, 1.0f, 1.0f);
  p = p*purple;
}
