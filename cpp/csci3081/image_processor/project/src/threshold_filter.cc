#include "threshold_filter.h"

// threshold is average if not otherwise specified
ThresholdFilter::ThresholdFilter() { threshold = 0.5; }
// set threshold member variable equal to input
ThresholdFilter::ThresholdFilter(float t) { threshold = t; }
ThresholdFilter::~ThresholdFilter() {}

void ThresholdFilter::ApplyAtPixel(Color &p) {
  float lum = p.GetLuminance();
  if (lum > threshold)
    p = Color::white();
  else
    p = Color::black();
}
