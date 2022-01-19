/**
 * @file invert_filter.h
 */
#ifndef INVERT_FILTER_H_
#define INVERT_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "simple_filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for InvertFilter, extends SimpleFilter. A filter that flips 
 * the values of each pixel. e.g. if a pixel was white after calling InvertFilter it would be black. 
 * 
 */
class InvertFilter : public SimpleFilter {
public:
 /**
  * @brief Constructor.
  * 
  */
  InvertFilter();
 /**
  * @brief Destructor.
  * 
  */
  ~InvertFilter();
 /**
  * @brief ApplyAtPixel function to be overridden by SimpleFilter Apply function.
  * 
  */
  void ApplyAtPixel(Color &p);
};

#endif // !INVERT_FILTER_