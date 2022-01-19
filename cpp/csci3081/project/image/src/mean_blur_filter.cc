#include "mean_blur_filter.h"
#include <cmath>

MeanBlurFilter::MeanBlurFilter() {
  kernel_size = 9;
  // create a new kernel of varying size, and set every element to 1 because
  // that's how mean_blur kernels are implemented
  kernel = new double[kernel_size];
  kernel_sum = 0.0;
  for (int i = 0; i < kernel_size; i++) {
    kernel[i] = 1;
    kernel_sum += 1.0;
  }
}
MeanBlurFilter::~MeanBlurFilter() { delete[] kernel; }

void MeanBlurFilter::Apply(std::vector<Image *> original,
                           std::vector<Image *> filtered) {

  ApplyKernel(original, filtered);
}
