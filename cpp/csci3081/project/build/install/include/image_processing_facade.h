/** @file image_processing_facade.h */
#ifndef IMAGE_PROCESSING_FACADE_H
#define IMAGE_PROCESSING_FACADE_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "image.h"
#include "filter.h"
#include "canny_edge_detect.h"
#include "blob_detector_adapter.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @ingroup simulation
 * @brief The image processing facade, enables functionality with the image processor
 * with easy to use functions that enable complicated functions with easy use.
 * 
 */
class ImageProcessingFacade {
public:

    /**
     * @brief Construct a new Image Processing Facade object
     * 
     */
    ImageProcessingFacade() {
        cannyEdgeDetectFilter = new CannyEdgeDetect();
        blobDetectFilter = new BlobDetectorAdapater();
    };
    
    /**
     * @brief Runs the canny edge detect filter from image processor
     * 
     * @param image 
     * @return Image* 
     */
    void RunCannyEdgeDetect(Image* image, Image* cannyImage) {
        std::vector<Image*> input(1, image);
        std::vector<Image*> output(1, cannyImage);
        cannyEdgeDetectFilter->Apply(input, output);
    }

    /**
     * @brief Runs blob detect filter from image processor
     * 
     * @param image 
     * @param blobDetect 
     */
    void BlobDetect(Image* image, Image* blobDetect) {
        std::vector<Image*> input(1, image);
        std::vector<Image*> output(1, blobDetect);
        blobDetectFilter->Apply(input, output);
    }
    
    
    private:
        /** @brief Reference to canny edge detect filter */
        Filter* cannyEdgeDetectFilter;
        /** @brief Reference to blob detect filter */
        Filter* blobDetectFilter;
   
};

#endif