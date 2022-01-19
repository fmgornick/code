/*! \page image_processing_description The "Image Processing" Library
 *
 * \section image_processing_section Overview
 * 
 * This is the overview of the image processing library. This image processing library enables our drone 
 * to take pictures and analyze them. The core class of the image processing library is the Image class. 
 * This class contains a pointer of data that represents a 4-channel image, the ordering of the data is 
 * in the RGBA format. From this image class, the Filter class is used to apply transformations to the image,
 * and these can be used for practical purposes. The image library is also integrated with OpenCV to 
 * enable more complex behavior in some filters.
 * 
 * An important idea of the image processing library is the Filter class. This is an abstract class that 
 * has one Apply function. This “Apply” function will take all the Images in its input and run a filter 
 * algorithm on them and put the outputs in its output vector. Filters can be broken up into 2 main categories,
 * there are SimpleFilters and ConvolutionFilters, there are also miscellaneous filters that do not 
 * fit into either category.
 * 
 * The SimpleFilter, takes an image and applies some transformation on 1 pixel at a time and this transformation
 * is the same for every pixel. A ConvolutionFilter applies a kernel to every pixel of the image. This 
 * kernel tells the filter what to do with the neighboring pixels to create a transformation. These two filter
 * types allow the image processor to have a simple CannyEdgeDetect filter. This filter runs a series of simple
 * and convolution filters on the image to identify any edges with white pixels. The CannyEdgeDetect filter
 * is one of the image processors most powerful functions. Looking at the UML diagram for the Filter class will
 * show how all functionality from this library derives from that class.
 * 
 * Another really powerful use for the image processor, is the OpenCV integration. The BlobDetectorAdapter class
 * is a very powerful filter that uses OpenCV. It uses OpenCV contours and a morphology algorithm to locate the 
 * orange robot in the simulation. This functionality would be very complex to implement with the Filter and Image
 * class on its own so OpenCV was used to save time and energy. OpenCV is not used outside of this class, and any
 * class that does OpenCV should stick with the Filter class format and use the adapter design pattern to implement
 * functionality.
 * 
 * From the UML diagram, it is seen that the Filter class and Image class do not interact outside of the Apply
 * function. This is important. An image should not have any reference to any filters, and filters should not
 * have any images as member variables.
 * 
 * \section image_processing_contribute How to Contribute
 * 
 * If a developer wishes to add to our image processing library the process is easy to catch onto. The only
 * extensions that the image processing library accepts is the creation of new filters. First the developer
 * must decide what filter they would like to implement. From there it must be decided if this filter is a 
 * SimpleFilter or ConvolutionFilter. The new filter then must extend one of those two classes to use their 
 * apply function. However, sometimes a filter is more complex and can simply extend Filter if it gains no 
 * benefit from extending any other filter class. The process is then just implanting the Apply function to 
 * work on the vector of inputs and adding to the vector of outputs.
 */ 