/**
 * @file sobel_filter.h
 */
#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for SobelFilter, extends Filter.  For this filter, instead 
 * of outputing two separate images and pushing them onto the Image * vector, we 
 * instead chose to double the size of the image and put the image intensity on top 
 * and image gradient on bottom.  Both image outputs are found by first applying 2 
 * kernels for x and y intensity. The intensity gradient is found by taking the 
 * hypotenuse of of each pixel, and the direction gradient is found by taking the 
 * arctangent.  More information can be found here:
 * https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123
 * 
 */
class SobelFilter : public Filter {
public:
/**
  * @brief Apply function to be overridden by Filter Apply function.
  * 
  */
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered);
};

#endif // !SOBEL_FILTER_H_
