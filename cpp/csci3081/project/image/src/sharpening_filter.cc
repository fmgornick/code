#include "sharpening_filter.h"

SharpeningFilter::SharpeningFilter() {
  kernel_size = 25;
  // create a new kernel of varying size, and set every element to 1 because
  // that's how mean_blur kernels are implemented
  kernel =
      new double[kernel_size]{1,  4, 6, 4,  1,  4,  16, 24, 16, 4, 6, 24, -476,
                              24, 6, 4, 16, 24, 16, 4,  1,  4,  6, 4, 1};

  kernel_sum = 0;
  for (int i = 0; i < kernel_size; i++) {
    kernel_sum += kernel[i];
  }
}
SharpeningFilter::~SharpeningFilter() { delete[] kernel; }

void SharpeningFilter::Apply(std::vector<Image *> original,
                             std::vector<Image *> filtered) {

  ApplyKernel(original, filtered);
}
