/*! \mainpage Droners Index Page
 *
 * \section intro_sec The Droner's Drone Project
 *
 * This is a project developed in C++ by Gabe Fendrich, Fletcher Gornick, Peyton Johnson, Luke Wiskus and Jason Woitalla.
 * The purpose of this project was to solve a problem presented in our computer science class. We have
 * been given a simulation where a drone, robot, hospital and recharge station are present. Our program
 * runs the backend of this simulation to move the drone with the end goal of locating the robot. We do this
 * using two major subsystems. Fist we have the <a href="image_processing_description.html">image processing subsystem</a> 
 * and next we have the <a href="simulation_description.html">simulation backend subsystem</a>. 
 * 
 * To actually run the project, you can view our <a href="getting_started.html">getting started with the libraries page</a> 
 * which details how to build, the code. It also links to our github https://github.umn.edu/umn-csci-3081-f21/repo-team-0 
 * which has more information on cloneing and contributing to the project. This project is open source, so if you would like
 * to contribute to it please read our <a href="how_to_contribute.html">How to Contribute page</a>.
 * 
 * Another tool we used for this project was deploying it to docker. More information can be seen on our, 
 * <a href="how_to_use_docker.html">how we use docker page</a>. Docker is a container based development 
 * environment that allows us to build this project with little overhead because it just contains the dependencies 
 * we need. The project can then be built or contributed to using docker.
 * 
 * Once our docker container is running, you can view the simulation in action by going to http://127.0.0.1:8081/ .
 * To see more about what our project can do go to the <a href="overview.html">overview page</a>. It details that 
 * this simulation contains a drone that is patrolling the scene for a robot. The drone knows it found the robot 
 * when the image processing library reports a hit back to the drone. From there, the drone deploys a rescue drone 
 * to go save the robot, and return it to the hospital.
 * 
 * To read more about the technologies that power our image processing library, <a href="image_processing_description.html">go here</a>.
 * 
 * To read more about the technologies that power our drone simulation, <a href="simulation_description.html">go here</a>.
 */

/**
 * @defgroup image Image Processing Subsystem
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
 * 
 */

/**
 * @defgroup simulation Simulation Subsystem
 * This is the simulation subsystem
 * 
 */
