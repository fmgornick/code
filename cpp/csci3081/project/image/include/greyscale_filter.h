/**
 * @file greyscale_filter.h
 */
#ifndef GREYSCALE_FILTER_H_
#define GREYSCALE_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for GreyScaleFilter, extends SimpleFilter.  Overrides the 
 * virtual ApplyAtPixel() function defined in SimpleFilter.  Just calculates the 
 * luminance value of each pixel and sets the pixels rgb values to the luminance.
 * 
 */
class GreyScaleFilter : public SimpleFilter {
public:
 /**
  * @brief Constructor.
  * 
  */
  GreyScaleFilter();
 /**
  * @brief Destructor.
  * 
  */
  ~GreyScaleFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  void ApplyAtPixel(Color &p);
};

#endif // !GREYSCALE_FILTER_H_
