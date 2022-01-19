/*! \page simulation_description The "Simulation" Library
 *
 * \section Simulation Overview
 *
 * The simulation is what allows you to visualize the project. 
 * 
 * To see visualization using docker- 
 * 1. Build docker image: bin/build-env.sh
 * 2. Run docker image: *bin/run-env.sh //Usage bin/run-env.sh <port - optional(default 8081)>
 * 3. Build project web server (inside docker image). (You won't be able to cd here yet
 * because the project directory does not exist. If you were able to launch the above commands 
 * you should now be inside the docker image). You can exit it with CTRL+D now: 
 * *cd /home/user/repo/project
 * *make -j
 * 4. Run web server (within project/directory inside docker image):
 * *cd /home/user/repo/project
 * *./build/web-app 8081 web
 * 5. Open up Firefox and browse to http://127.0.0.1:8081/
 * 
 * To see visualization using SSH into CSE Labs machines- 
 * 1. SSH into a CSE Lab Machine using port forwarding for the UI. (If port 8081 is not available,
 * choose a different port (8082, 8083, etc)): *ssh -L 8081:127.0.0.1:8081 x500@csel-xxxx.cselabs.umn.edu
 * //ssh -L 8081:127.0.0.1:8081 x500@csel-kh1250-05.cselabs.umn.edu
 * 2. Compile the project (within ssh session):
 * *cd /path/to/cloned/repository
 * *cd project
 * *make -j
 * 3. Run project (within project/directory inside ssh session)
 * *./build/web-app 8081 web 
 * 4. Open up Firefox and browse to http://127.0.0.1:8081/
 * 
 * To see visualization using CSE Labs machines/VOLE- 
 * VOLE: https://cse.umn.edu/cseit/self-help-guides/virtual-online-linux-environment-vole
 * 1. Build project:
 * *cd /path/to/cloned/repository
 * *cd project
 * *make -j
 * 2. Run project (within project/directory):
 * *./build/web-app 8081 web
 * 3. Open up Firefox and browse to http://127.0.0.1:8081/
 * 
 * The above is taken from the beta code read me page-
 * (https://github.umn.edu/umn-csci-3081-f21/shared-upstream/tree/support-code/project)
 * 
 * The simulation implements all of our files in tandem with the web app and simulation
 * facade. The simulation facade is the main class for the simulation, it starts by creating
 * a simulation facade object. From there, the most pertinant fuctions are the ones to create
 * entities from the JSON scene from the web app and populate the entities arrays with the 
 * JSON object, add entities to their respective arrays, and update the simulation after 
 * any of these functions are implemented. For more information on these there is commenting 
 * in the simulation_facade page. 
 * 
 * There are a couple main drawbacks to our simulation:
 * 
 * -The simulation is not accessable with certain SSH environments. When you SSH into a 
 * labs computer on your personal computer if the environment you are using doesn't support
 * opening a browser within the session (VS Code for example) you cannot reach the webpage.
 * 
 * -There is a camera delay such that the camera takes a photo at a frequency of 2.5 seconds which
 * then causes a delay in the simulation, meaning the simulation does not update instantaneously. 
 * 
 * -The patrol pattern is less comprehensive than we may have hoped as if the robot is behind or 
 * in/on a building it will not recognize that. 

 * The most problematic issues with our simulation are the camera delay and patrol pattern. 
 * Their effects would be far more obvious and detrimental if we were to actually use this 
 * drone for 'real life' search and rescue rather than just finding a robot in the simulation.
 * The camera delay partnered with the speeds of various other functions could cause issues since 
 * given that the camera isn't taking photos in constant time there is a possibility the program 
 * as a whole could miss capturing the individual that is meant to be rescued. As an example if 
 * the speed of the drone was to increase to 100mph (which I read is the speed limit for drones)
 * it would be travelling over 100 feet per second (rounded down significantly to account for 
 * various variables the drone might run into in the air that may slow the drone down) and if 
 * you are taking a picture every 2.5 seconds that would mean you would need to have the drone
 * high enough to have the image cover an area of at least 250 feet. 
 * In that example if the speed or height of the drone was off you could miss capturing a photo
 * of the target completely and the most reasonable way to try to fix that would be to find a speed
 * and a way in which the drone could take photos in constant time.
 * Similary, the patrol pattern given the issues with the buildings could also prevent us from
 * "seeing" and thus finding our target.
 * 
 * With these two examples it is easy to see the importance of all of the different parts of this 
 * project working together, especially when trying to create a smooth simulation. To see the 
 * complete structure of how our simulation uses each of the files you can access the UML diagrams 
 * generated on our docker page, however as a brief overview if we start at the simulation facade, 
 * then when creating objects we make use of the web app and entity factory pages, the web app gives 
 * us the information from the JSON scene and the entity factory pages are used for making new 
 * entities. Implementation for these is actually carried out by the specific entities factories. 
 * As a sort of hierarchy it goes from the web app, simulation facade, entity factories, then to the 
 * find robot sequence which uses camera, the various filters, movement techniques, and search 
 * strategies to- you probably guessed it already, find the robot!
 * 
 * The inheritance diagrams are very useful for visualizing how the simulation works, I suggest looking
 * at the diagrams generated for the web app or simulation facade while you're reading to actually see 
 * what I'm talking about here.
 */ 