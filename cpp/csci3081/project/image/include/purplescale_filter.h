/**
 * @file purplescale_filter.h
 */
#ifndef PURPLESCALE_FILTER_H_
#define PURPLESCALE_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for PurpleScaleFilter, extends SimpleFilter.
 * This filter will take an image and "purple scale" it. This means purple will
 * be the only color present in the image and different tones of purple will
 * allow the image to be still be recognizable.
 * 
 */
class PurpleScaleFilter : public SimpleFilter {
public:
 /**
  * @brief Constructor.
  * 
  */
  PurpleScaleFilter();
 /**
  * @brief Destructor.
  * 
  */
  ~PurpleScaleFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  void ApplyAtPixel(Color &p);
};

#endif // !PURPLESCALE_FILTER_H_
