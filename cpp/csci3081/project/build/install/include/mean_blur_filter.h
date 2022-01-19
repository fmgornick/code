/**
 * @file mean_blur_filter.h
 */
#ifndef MEAN_BLUR_FILTER_H_
#define MEAN_BLUR_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "convolution_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for MeanBlurFilter, extends ConvolutionFilter.  Creates a
 * 3 x 3 kernel with all 1's meaning that each pixel and the surrounding 8 get the 
 * same representation for the value of the current pixel.  Kernel is applied in 
 * ConvolutionFilter Apply() method.
 * 
 */
class MeanBlurFilter : public ConvolutionFilter {
public:
 /**
  * @brief Constructor.
  * 
  */
  MeanBlurFilter();
/**
  * @brief Destructor.
  * 
  */
  ~MeanBlurFilter();
/**
  * @brief Apply function to be overridden by parents Apply function.
  * 
  */
  void Apply(std::vector<Image *> original,
                   std::vector<Image *> filtered);

};

#endif // !MEAN_BLUR_FILTER_H_
