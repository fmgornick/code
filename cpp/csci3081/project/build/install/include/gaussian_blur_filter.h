/**
 * @file gaussian_blur_filter.h
 */
#ifndef GAUSSIAN_BLUR_FILTER_
#define GAUSSIAN_BLUR_FILTER_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "convolution_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for GaussianBlurFilter, extends ConvolutionFilter.  Creates 
 * a 5 x 5 kernel to apply to each pixel and ConvolutionFilter is used to iterate 
 * through the image to apply it.  Gaussian Blur is different from Mean Blur in that 
 * the representation of each pixel isn't equally distributed like Mean Blur.
 * 
 */
class GaussianBlurFilter : public ConvolutionFilter {
public:
/**
  * @brief Constructor.
  * 
  */
  GaussianBlurFilter();
/**
  * @brief Constructor.
  * 
  */
  ~GaussianBlurFilter();
  /**
  * @brief Apply function to be overridden by parents Apply function.
  * 
  */
  // class-specific application of parent apply
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered);
};

#endif // !GAUSSIAN_BLUR_FILTER_
