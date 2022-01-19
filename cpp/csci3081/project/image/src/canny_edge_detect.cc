#include "canny_edge_detect.h"
#include "double_threshold_filter.h"
#include "filter.h"
#include "gaussian_blur_filter.h"
#include "greyscale_filter.h"
#include "hysteresis_filter.h"
#include "non_max_filter.h"
#include "sobel_filter.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

CannyEdgeDetect::CannyEdgeDetect() {}

CannyEdgeDetect::~CannyEdgeDetect() {}

void CannyEdgeDetect::Apply(std::vector<Image *> original,
                            std::vector<Image *> filtered) {
  // to hold original image
  Image &old = *original[0];
  // flip each so that you can send filtered image into the next filter
  GreyScaleFilter().Apply(original, filtered);
  GaussianBlurFilter().Apply(filtered, original);
  SobelFilter().Apply(original, filtered);
  NonMaxFilter().Apply(filtered, original);
  DoubleThresholdFilter().Apply(original, filtered);
  HysteresisFilter().Apply(filtered, original);

  // setting original back to original image
  *filtered[0] = *original[0];
  *original[0] = old;
}
