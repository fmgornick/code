/**
 * @file threshold_filter.h
 */
#ifndef THRESHOLD_FILTER_H_
#define THRESHOLD_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for ThresholdFilter, extends SimpleFilter.
 * Threshold scans the image and if the luminance of the image is above
 * the input threshold it changes the pixel to white, otherwise the pixel
 * turns black. This means the output image only has the colors black and
 * white
 * 
 */
class ThresholdFilter : public SimpleFilter {
public:
 /**
  * @brief Constructor for no arguments.
  * 
  */
  ThresholdFilter();
   /**
  * @brief Constructor for float threshold argument.
  * 
  */
  ThresholdFilter(float threshold);
 /**
  * @brief Destructor.
  * 
  */
  ~ThresholdFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  void ApplyAtPixel(Color &p);

private:
  float threshold;
};

#endif // !THRESHOLD_FILTER_H_
