/**
 * @file fft_convolution_filter.h
 */
#ifndef FFT_CONVOLUTION_FILTER_
#define FFT_CONVOLUTION_FILTER_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "filter.h"
#include <bitset>
#include <cmath>
#include <complex>
#include <fftw3.h>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for ConvolutionFilter, extends Filter.
 * A basic convolution filter implementation. Each child class will have it's
 * own kernel object and run the given apply kernel function. This class has
 * a lot of extendability as long as the filter algorithm is the same.
 */
class ConvolutionFilter : public Filter {
public:
  ConvolutionFilter() {}
  /**
   * @brief The method inherited convolution filters call ApplyKernel in.
   */
  virtual void Apply(std::vector<Image *> original,
                     std::vector<Image *> filtered) = 0;

  /**
   * @brief The apply kernel algorithm. This function will work on any
   * input images and run the kernel of the given size on the images.
   * It now implements a fast Fourier transform algorithm to convolve our image
   * in a faster exponential time.
   */
  void ApplyKernel(std::vector<Image *> original,
                   std::vector<Image *> filtered) {
    // get length of the side of our kernel
    int len = (int)sqrt(kernel_size);
    // padding for image kernel
    int pad = (len - 1) / 2;
    for (int i = 0; i < original.size(); i++) {
      // set filtered image equal to original then iterate through filtered
      // image
      *filtered[i] = *original[i];
      // create reference to make access easier
      Image &img = *filtered[i];
      int width = img.GetWidth();
      int height = img.GetHeight();
      int image_size = width * height;

      // original image
      std::complex<double> *OI = new std::complex<double>[image_size];
      // original kernel
      std::complex<double> *OK = new std::complex<double>[image_size];
      // image affter fast-fourier transform
      std::complex<double> *NI = new std::complex<double>[image_size];
      // kernel affter fast-fourier transform
      std::complex<double> *NK = new std::complex<double>[image_size];

      // all the above variables reinterpreted as fftw_complex pointers.  We can
      // do this because they use memory the exact same way, and our fft plans
      // need ffw_complex arrays as arguments
      fftw_complex *fftOI = reinterpret_cast<fftw_complex *>(OI);
      fftw_complex *fftOK = reinterpret_cast<fftw_complex *>(OK);
      fftw_complex *fftNI = reinterpret_cast<fftw_complex *>(NI);
      fftw_complex *fftNK = reinterpret_cast<fftw_complex *>(NK);

      Color p;
      // set original image equal to the inputed image
      for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
          img.GetPixel(i, j, p);
          OI[i + j * width] = std::complex<double>(p.getR(), 0);
        }
      }

      // take our image of zeros and put our kernel in with 0 padding.  We must
      // circular shif our new kernel for our fft to work properly.  This is
      // done by taking a centered kernal and swapping quadrant 1 with quadrant
      // 3, and swapping quadrant 2 with quadrant 4
      for (int i = 0; i < image_size; i++)
        OK[i] = std::complex<double>(0, 0);
      int kernel_len = std::sqrt(kernel_size);
      // middle value of kernel
      int m = kernel_len / 2;
      for (int x = 0; x < kernel_len; x++) {
        for (int y = 0; y < kernel_len; y++) {
          // UPPER LEFT QUADRANT
          if ((x % kernel_len) < m && y < m) {
            OK[(width - m + x) + (height - m + y) * width] =
                kernel[x + y * kernel_len] / kernel_sum;
          }
          // LOWER RIGHT QUADRANT
          if ((x % kernel_len) >= m && y >= m) {
            OK[(x - m) + (y - m) * width] =
                kernel[x + y * kernel_len] / kernel_sum;
          }
          // LOWER LEFT QUADRANT
          if ((x % kernel_len) < m && y >= m) {
            OK[(width - m + x) + (y - m) * width] =
                kernel[x + y * kernel_len] / kernel_sum;
          }
          // UPPER RIGHT QUADRANT
          if ((x % kernel_len) >= m && y < m) {
            OK[(x - m) + (height - m + y) * width] =
                kernel[x + y * kernel_len] / kernel_sum;
          }
        }
      }

      fftw_plan plan1;
      fftw_plan plan2;
      fftw_plan plan3;
      // calculate fft on our image
      plan1 = fftw_plan_dft_2d(height, width, fftOI, fftNI, 1, FFTW_ESTIMATE);
      fftw_execute(plan1);
      // calculate fft on our kernel
      plan2 = fftw_plan_dft_2d(height, width, fftOK, fftNK, 1, FFTW_ESTIMATE);
      fftw_execute(plan2);

      // convolve image with kernel by multiplying.  This works via the
      // convolution theorem for fourier transforms
      for (int i = 0; i < image_size; i++) {
        NI[i] *= NK[i];
        OI[i] = 0;
      }

      // use inverse fft on our convolved image to get our new blurred image
      plan3 = fftw_plan_dft_2d(height, width, fftNI, fftOI, -1, FFTW_ESTIMATE);
      fftw_execute(plan3);
      // delete everything dynamically allocated accept our final image
      fftw_destroy_plan(plan1);
      fftw_destroy_plan(plan2);
      fftw_destroy_plan(plan3);
      fftw_cleanup();
      delete[] OK;
      delete[] NI;
      delete[] NK;

      // normalize the values on our image
      for (int i = 0; i < image_size; i++) {
        OI[i] /= width * height;
      }

      double val;
      // assign our new convolved image with the img reference
      for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
          val = OI[j * width + i].real();
          p = Color(val, val, val);
          img.SetPixel(i, j, p);
        }
      }
      // fincally, delete the image
      delete[] OI;
    }
  }
  /**
   * @brief Copy constructor
   * Uses the = operator to simplify the function.
   */
  ConvolutionFilter(const ConvolutionFilter &filter) { *this = filter; }
  /**
   * @brief Operator =
   */
  void operator=(const ConvolutionFilter &filter) {
    kernel_size = filter.kernel_size;
    kernel_sum = filter.kernel_sum;

    delete kernel;
    kernel = new double[filter.kernel_size];
    for (int i = 0; i < filter.kernel_size; i++) {
      kernel[i] = filter.kernel[i];
    }
  }

protected:
  int kernel_size;
  double kernel_sum;
  double *kernel;
};

#endif // !CONVOLUTION_FILTER_
