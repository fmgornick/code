/**
 * @file sharpening_filter.h
 */
#ifndef SHARPENING_FILTER_H
#define SHARPENING_FILTER_H
/*******************************************************************************
  * Includes
******************************************************************************/
#include "convolution_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief This is a convolution filter that uses a kernal found on Wikipedia that 
 * sharpens the image. Wikipeidea article: https://en.wikipedia.org/wiki/Kernel_(image_processing)
 */
class SharpeningFilter : public ConvolutionFilter {
public:
  /**
  * @brief Constructor.
  * 
  */
  SharpeningFilter();
/**
  * @brief Destructor.
  * 
  */
  ~SharpeningFilter();
/**
  * @brief Apply function to be overridden by parents Apply function.
  * 
  */
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered);
};

#endif // !GAUSSIAN_BLUR_FILTER_
