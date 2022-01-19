/**
 * @file canny_edge_detect.h
 */
#ifndef HYSTERESIS_FILTER_H_
#define HYSTERESIS_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for HysteresisFilter, extends Filter. The hysteresis filter 
 * takes the output from the double-threshold filter and iterates through, changing
 * all 'weak' pixels into 'strong' pixels if any of the surrounding pixels are 
 * 'strong.' If not the pixel is set to black.
 * 
 */
class HysteresisFilter : public Filter {
public:
 /**
  * @brief Apply function to be overridden by Filter Apply function.
  * 
  */
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered);
};

#endif // !HYSTERESIS_FILTER_H_