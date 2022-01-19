/**
 * @file filter.h
 */
#ifndef FILTER_H_
#define FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "image.h"
#include <vector>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for Filter.  This is where all the filters are derived 
 * from.
 * 
 */
class Filter {
public:
 /**
  * @brief Destructor.
  * 
  */
  virtual ~Filter() {}
  /**
  * @brief Apply function for filter (overrides most of the individual filters apply function)
  * 
  */
  // Apply function to be overridden by inherited classes
  virtual void Apply(std::vector<Image *> original,
                     std::vector<Image *> filtered) = 0;
};

#endif
