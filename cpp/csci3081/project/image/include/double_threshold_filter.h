/**
 * @file double_threshold_filter.h
 */
#ifndef DOUBLE_THRESHOLD_FILTER_H_
#define DOUBLE_THRESHOLD_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief Double Threshold takes in the value of the each pixel and decides if it is a strong 
 * or weak pixel based off of its luminencence. It has a strong threshold which makes if white,
 * and a weak threshold that makes it grey. 
 * 
 */
class DoubleThresholdFilter : public SimpleFilter {
public:
 /**
  * @brief Constructor.
  * 
  */
  DoubleThresholdFilter();
 /**
  * @brief Destructor.
  * 
  */
  ~DoubleThresholdFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  // Apply function to be overridden by inherited classes
  void ApplyAtPixel(Color &p);

private:
  float threshold;
};

#endif // !DOUBLE_THRESHOLD_FILTER_H_
