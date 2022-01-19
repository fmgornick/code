/**
 * @file solarization_filter.h
 */
#ifndef SOLARIZATION_FILTER_H_
#define SOLARIZATION_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for SolarizationFilter, extends SimpleFilter.
 * Solarization filter basically runs the rgb values through a modified sin function 
 * to create a pseudo-inversion filter.
 * 
 */
class SolarizationFilter : public SimpleFilter {
public:
/**
  * @brief Constructor.
  * 
  */
  SolarizationFilter();
 /**
  * @brief Destructor.
  * 
  */
  ~SolarizationFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  void ApplyAtPixel(Color &p);
};

#endif // !SOLZARIZATION_FILTER_H_