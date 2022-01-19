#include "./../include/double_threshold_filter.h"
#include "./../include/color.h"

DoubleThresholdFilter::DoubleThresholdFilter() = default;

DoubleThresholdFilter::~DoubleThresholdFilter() {}

void DoubleThresholdFilter::ApplyAtPixel(Color &p) {
  float lum = p.GetLuminance();
  //low threshold is 0.2
  //high threshold is 0.1
  if (lum > 0.2) {
    p = Color::white();
    }
    else if (lum > 0.1){
        p.setRGBA(0.5,0.5,0.5,1);
    } 
    else {
        p = Color::black();
    }
  
}
