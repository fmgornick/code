#include "gaussian_blur_filter.h"

GaussianBlurFilter::GaussianBlurFilter() {
  // set size for kernel.  To alter size, change first argument in std::pow()
  // function
  kernel_size = std::pow(5, 2);
  // create a new gaussian kernel of varying size
  kernel = new double[kernel_size];

  // sigma value for standard deviation of our convolution
  double sigma = 2.0;
  double r, s = 2.0 * sigma * sigma;
  int length = std::sqrt(kernel_size);
  int radius = length / 2;

  // generating nxn kernel. This double for loop was inspired from this geeks
  // for geeks page: https://www.geeksforgeeks.org/gaussian-filter-generation-c/
  kernel_sum = 0.0;
  for (int x = -1 * radius; x <= radius; x++) {
    for (int y = -1 * radius; y <= radius; y++) {
      r = sqrt(x * x + y * y);
      kernel[(x + radius) + (y + radius) * length] =
          (exp(-(r * r) / s)) / (M_PI * s);
      kernel_sum += kernel[(x + radius) + (y + radius) * length];
    }
  }
}
GaussianBlurFilter::~GaussianBlurFilter() { delete[] kernel; }

void GaussianBlurFilter::Apply(std::vector<Image *> original,
                               std::vector<Image *> filtered) {
  ApplyKernel(original, filtered);
}
