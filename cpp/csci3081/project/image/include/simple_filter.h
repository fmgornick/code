/**
 * @file simple_filter.h
 */
#ifndef SIMPLE_FILTER_H_
#define SIMPLE_FILTER_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for SimpleFilter, extends Filter.  This filter does the 
 * brunt of the work when iterating through an image.  It's an abstract class, 
 * so it's initialized as one of it's derived classes, so when it iterates through 
 * the image, it calls the ApplyAtPixel() function that's defined in each of it's 
 * derived classes.
 * 
 */
class SimpleFilter : public Filter {
public:
/**
  * @brief ApplyAtPixel function used by some of the filters to be overridden by Filter apply function.
  * 
  */
  virtual void ApplyAtPixel(Color &p) = 0;
  /**
  * @brief Apply function to be overridden by Filter Apply function.
  * 
  */
  // Apply function used by derived classes
  void Apply(std::vector<Image *> original, std::vector<Image *> filtered) {
    // iterate through images in input vector
    for (int i = 0; i < original.size(); i++) {
      // set filtered image equal to original then iterate through filtered
      // image
      *filtered[i] = *original[i];
      // create reference to make access easier
      Image &img = *filtered[i];

      // iterate through each pixel in the image
      for (int j = 0; j < img.GetWidth(); j++) {
        for (int k = 0; k < img.GetHeight(); k++) {
          Color p;
          img.GetPixel(j, k, p);
          ApplyAtPixel(p);
          img.SetPixel(j, k, p);
        }
      }
    }
  }
};

#endif // !SIMPLE_FILTER_H_
