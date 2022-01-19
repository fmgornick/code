/**
 * @file non_max_filter.h
 */
#ifndef NON_MAX_FILTER_H_
#define NON_MAX_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for NonMaxFilter, extends Filter.
 * NonMax takes in two images, an intensity image and a direction image. 
 * This filter scans the image and if intensity of the nearest pixel in the 
 * given direction is larger than the current pixel, it will set the current 
 * pixel to black. The end result is an image that has thinner lines.
 * 
 */
class NonMaxFilter : public Filter {
public:
  /**
  * @brief Constructor.
  * 
  */
  NonMaxFilter();
  /**
  * @brief Apply function to be overridden by Filter Apply function.
  * 
  */
  void Apply(std::vector<Image *> original,
                   std::vector<Image *> filtered);
};

#endif // !NON_MAX_FILTER_H_
