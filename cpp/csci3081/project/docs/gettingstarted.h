/*! \page getting_started Getting Started With the Libraries
 *
 * \section overview_section Overview
 *
 * The first thing to do to get started is to navigate to the team GitHub page
 * at https://github.umn.edu/umn-csci-3081-f21/repo-team-0 . Then, in the code
 * section, switch from the 'main' branch to the 'develop' branch. From there,
 * click on the green 'code' button, and copy the https link to your clipboard.
 * Then, open the terminal on your local machine, and navigate to the place in
 * your file directory where you want to have your code repository. Using mkdir,
 * create the directory that you want to store the project in, i.e. "mkdir
 * 'my-proj'". Then, cd into that repository, and run the command "git clone
 * 'url you copied to clipboard'".
 *
 * \section setting_docker Setting up Docker
 *
 * Our build relies on Docker to run,so after installing Docker, navigate to the
 * repo-team-0 directory and run 'bin/build-env.sh' to build the Docker image.
 * This can take a while, but after the image has been built, you can run the
 * Docker image by entering 'bin/run-env.sh'. The project dependencies should
 * now be functional and you should now be able to build and run the code.
 *
 *
 *
 * \section making_running Making and Running the Code
 * There are 6 different directories that you can make and run the code in.
 * Make sure you've cd'd into the proper directory before running any of the
 * respective commands. For project/image:
 *
 * 1. run 'make -j'.
 * 2. run './image-processor-app <data/input_img.png> <filter>
 * <data/output_img.png>': in the project/image/ directory, there’s a data f
 * lder where you can put in png images, then you can apply a filter to the i
 * age by typing the above command.
 *
 * For project/simulation and project/apps/web_app:
 *
 * 1. run 'make -j'
 * 2. run 'make run'
 *
 * For project/apps/image_processor_app:
 * 1. run 'make -j'
 * 2. run './image-processor-app <data/input_img.png> <filter>
 * <data/output_img.png>':
 *
 * For project/tests:
 * 1. run 'make -j'
 * 2. run 'make test'
 *
 * For project:
 * 1. run 'make -j' (if this leads to an error then just cd into simulation
 * first and rum make, then the make in this directory should work)
 * 2. choose mode to run, either 'make run' , 'make test', or 'make
 * i=<input_file.png> f=<filter> o=<output_file.png> img'.
 *
 * Make run runs the simulation as usual, make test runs the tests, and the last
 * option allows for the image processor to be run.
 *
 * Finally, to remove the object files, you can use make clean in any of the
 * respective directories. If you have any additional questions, the README on
 * the GitHub page has additional instructions for running the code.
 *
 * If you're running the simulation code, to see the actual simulation you will
 * have to open a browser with the address http://127.0.0.1:8080/ , otherwise
 * the output will either be in your terminal (tests) or in a file (image
 * processing application or web application).
 *
 *
 *
 *
 */
