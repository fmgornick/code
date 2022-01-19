/*! \page how_to_use_docker How To Use Docker
 *
 * \section why_we_use_docker Why We Use Docker
    Docker is used in order for all group members to have access to the same libraries
    and same development environment. Because of docker we all have the same access to 
    libraries like openCV and all the libaries concerning the web application.
    Without docker, we would all have to try and make the same environment on our local 
    machines which could cause major issues when pushing code to develop that may work 
    on one of our local environments but not the others. Docker is a great way for 
    group work to stay standardized and allows for the development of the project to go quickly
    and be able to be realeased quicker. 

    \section how_we_use_docker How We Use Docker
    In our project, we have a docker file that allows us to complie all the libraries that we need in
    the same way on all of our local machines. We run the command bin/build-env.sh. This builds our docker image based
    off of what our docker page says. After doing that, we all have the ability to run a container that is the
    exact same on all of our local machines. Once the environment is built we don't have to build it every time. 
    Therefore if we want to run the container we run the command bin/run-env.sh and then you can open the container
    on your text editor and run the environment. This allows us to make changes that will work on all of our local machines.

    \section how_to_run_our_project_using_docker How To Run Our Project Using Docker
    In order to run our project, navigate to our docker submission on docker hub. 
    The URl is https://hub.docker.com/r/gorni025/sim. Run the command "docker pull gorni025/sim"
    To then run the simulation run the command "docker run --name=sim -p 127.0.0.1:8080:8081 -d gorni025/sim", and to see
    the simulation navigate to " http://127.0.0.1:8080/" in your browser, and to see our documentation navigate to
    "http://127.0.0.1:8080/docs/". To stop the simulation run the command "docker kill sim" then
    "docker rm sim". You can run the following line to enter the docker image and see it's contents,
    "docker run -it --entrypoint /bin/bash gorni025/sim" Then simply type exit to get out of the image. If you want to 
    try running the simulation on a CSE labs machine, you can first run this command to ensure the simulation will run 
    on your local machine... "ssh -L 8081:127.0.0.1:8081 <x500>@<machine>.cselabs.umn.edu" Then you can pull and run 
    the docker image with these commands "singularity pull docker://gorni025/sim",  
    "singularity run docker://gorni025/sim" Then navigate to http://127.0.0.1:8081/ to see the simulation, and press
    CTRL-C to kill it. If instead, you'd like to run our whole project using our docker environment, yo can first clone our 
    repository "git clone https://github.umn.edu/umn-csci-3081-f21/repo-team-0.git" Then, in the repo-team-0 directory,
   you can build and run the docker environment with these commands "bin/build-env.sh", "bin/run-env.sh". Now that you're 
   in the environment with all the dependencies, you can visit This Page To see how to make and run everything.


 *
 * 
 * 
 *
 */ 