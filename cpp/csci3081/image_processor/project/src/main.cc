#include "canny_edge_detect.h"
#include "double_threshold_filter.h"
#include "filter.h"
#include "gaussian_blur_filter.h"
#include "greyscale_filter.h"
#include "hysteresis_filter.h"
#include "invert_filter.h"
#include "mean_blur_filter.h"
#include "non_max_filter.h"
#include "purplescale_filter.h"
#include "sharpening_filter.h"
#include "sobel_filter.h"
#include "solarization_filter.h"
#include "threshold_filter.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[]) {
  // Get input file, filter type, and output file from command line
  // argc = # of arguments
  // argv = an array of arguments
  std::string inputFile(argv[1]);
  std::string filterType(argv[2]);
  std::string outputFile(argv[3]);

  // Create available filters (unique_ptr handles dynamic memory)
  std::map<std::string, unique_ptr<Filter>> filters;
  filters["canny-edge-detect"] = unique_ptr<Filter>(new CannyEdgeDetect());
  filters["double_threshold"] = unique_ptr<Filter>(new DoubleThresholdFilter());
  filters["gaussian_blur"] = unique_ptr<Filter>(new GaussianBlurFilter());
  filters["greyscale"] = unique_ptr<Filter>(new GreyScaleFilter());
  filters["hysteresis"] = unique_ptr<Filter>(new HysteresisFilter());
  filters["invert"] = unique_ptr<Filter>(new InvertFilter());
  filters["mean_blur"] = unique_ptr<Filter>(new MeanBlurFilter());
  filters["non_max"] = unique_ptr<Filter>(new NonMaxFilter());
  filters["purplescale"] = unique_ptr<Filter>(new PurpleScaleFilter());
  filters["sharpening"] = unique_ptr<Filter>(new SharpeningFilter());
  filters["sobel"] = unique_ptr<Filter>(new SobelFilter());
  filters["solarization"] = unique_ptr<Filter>(new SolarizationFilter());
  filters["threshold"] = unique_ptr<Filter>(new ThresholdFilter(0.5));
  filters["threshold-low"] = unique_ptr<Filter>(new ThresholdFilter(0.25));
  filters["threshold-high"] = unique_ptr<Filter>(new ThresholdFilter(0.75));

  // Create input and output vectors
  Image input(inputFile);
  Image output;
  std::vector<Image *> inputs;
  std::vector<Image *> outputs;
  inputs.push_back(&input);
  outputs.push_back(&output);

  // Apply filter based on filter type
  filters[filterType]->Apply(inputs, outputs);

  // Save output image
  output.SaveAs(outputFile);
}
