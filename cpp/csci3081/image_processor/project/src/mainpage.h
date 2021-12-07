/*! \mainpage Droners Index Page 
 *
 * \section intro_sec Peyton, Luke, Fletcher, Jason, and Gabe
 *
 * This program is an image processor consisting of greyscale, gaussian blur, sobel, 
 * non-max suppression, double threshold, and hysteresis filters to make up a canny-
 * edge detect algorithm that "sketches" the edges of any object in a picture.
 * 
 * To use this program, you have to first make a data folder inside the project folder 
 * and insert some PNG (github doesn't like taking in PNG's), you can then create the 
 * image processor by running <make> doing a call like: 
 * <./image_processor data/myimage.png name_of_filter data/myimage-name_of_filter.png> 
 *
 * To add another filter, you must first create a .h file and .cc file for your filter, 
 * extending Filter or some other parent that extends Filter. Then in main.cc you need 
 * to #include your .h file and create your filter in main.
 * 
 */