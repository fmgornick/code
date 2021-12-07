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
// Attempt at multiplying the kernel matrix by -1/256 like the
// wiki says, but it looks way worse
/*{
      -1/256, -1/64, -3/128, -1/64, -1/256,
      -1/64, -1/16, -3/32, -1/16, -1/64,
      -3/128, -3/32, 119/64, -3/32, -3/128,
      -1/64, -1/16, -3/32, -1/16, -1/64,
      -1/256, -1/64, -3/128, -1/64, -1/256,
  }; */
