/*! \page overview Overview

 *  \section purpose_of_project Purpose Of Project
    The drone search and rescue project is a 3D simulation with a drone, robot, hospital, and rescue drone. The project
    taught us how to design a large scale project with hundreds of files. We learned how to make UML diagrams and use
    inheritance and polymorphism to make a flexible and expandble project. We learned how the agile process works when
    making a project, and we learned how to use Github to manage our project and make sure all group members
    are on the same page on what part of the project we are responsible for. 

    \section how_project_works How Project Works
    The drone searches the entire map for the orange robot. It does this by using a patrol strategy that starts in the 
    lower left corner and scans the entire map in a sinwave. The drone uses image proccessing to detect when the robot
    has been found, and once it finds the robot the drone goes to the origin spot and the rescue drone beelines to 
    the robot and brings it to the hospital. We do this by using C++ too make json objects that get sent to the web server.
    The processes of getting the right data into these picojson objects takes a lot of work and organization. We have factories
    to make entities and a lot of logic that goes into calculating position, processing images, and determining routes.

    \section bugs_we_fixed Bugs We Fixed
    Bug 1) Makefile. Many times we had to try and try again to get our make file to work properly. It
    took about 10 hours of collective work to get our final products make files complely working.

    Bug 2) Patrol. For awhile our patrol wouldn't have the drone update its direction. We found out it was because 
    old code for manual movement was still in our project, and once we got rid of that the direction got properly 
    updated

    Bug 3) Camera. The camera wouldn't follow the drone. We tried many things to get it to be fixed. We tried adding
    a position value, we tried messing with the code in the wep app itself. Eventually the support code got updated and
    then the camera started working. 

    Bug 4) Blob Detect. For awhile, blob detect would detect the hospital as if it was a drone. The eventual fix was to lower 
    the hue threshold to not confuse a very bright redd with orange.

    \section final_result Final Result
    The project cumulated in a working product deployed on docker hub. The drone can move on its own, detect the robot, and 
    bring it to the hospital. Throughout the process our group learned how to use Github in a professional setting. Utilizing
    branches, projects, issues, cards, and pull request. We also learned how to use the scrum process that allowed our
    group to stay focused which allowed us all to know what everyone else was responsible for and where we were at in
    the process. The project, which is now in full working order, taught us how to work together as a team and develop
    software as a cohesive group. 
 *
 * 
 * 
 *
 */ 