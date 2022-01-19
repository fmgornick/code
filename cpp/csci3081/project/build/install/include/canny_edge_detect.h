/**
 * @file canny_edge_detect.h
 */
#ifndef CANNY_EDGE_DETECT_H_
#define CANNY_EDGE_DETECT_H_
/*******************************************************************************
  * Includes
******************************************************************************/
#include "filter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @ingroup image
 * @brief The main class for CannyEdgeDetect, extends Filter. This basically just applies 
 * each of the filters required for the canny edge algorthim in order,
 * 1. Greyscale 
 * 2. Gaussian Blur 
 * 3. Sobel 
 * 4. Non-Max Suppression 
 * 5. Double Threshold 
 * 6. Hysteresis 
 * To see more information on how this works: https://towardsdatascience.com/canny-edge-detection-step-by-step-in-python-computer-vision-b49c3a2d8123 
 * 
 */
class CannyEdgeDetect : public Filter{
public: 
 /**
  * @brief Constructor.
  * 
  */
CannyEdgeDetect();
/**
  * @brief Destructor.
  * 
  */
~CannyEdgeDetect();
 /**
  * @brief Apply function to be overridden by Filter Apply function.
  * 
  */
void Apply (std::vector<Image *> original, std::vector<Image *> filtered);

};
#endif // !CANNY_EDGE_DETECT