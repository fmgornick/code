# Team 0 Drone Search & Rescue System
How to run docker image for Fall 2021 CSCI 3081W Drone Simulation.
## Download Image
```bash
$ docker pull gorni025/sim
```
## Run Simulation
```bash
$ docker run --name=sim -p 127.0.0.1:8080:8081 -d gorni025/sim
```

Navigate to the browser to view:
  * Simulation - http://127.0.0.1:8080/
  * Documentation - http://127.0.0.1:8080/docs/
    * Don't forget the last '/' for the Documentation!

## Stop Simulation
To kill and remove your container, you can use the following commands...
```bash
$ docker kill sim
$ docker rm sim
```

## Inspect Image 
You can run the following line to enter the docker image and see it's contents...
```bash
$ docker run -it --entrypoint /bin/bash gorni025/sim
```
Then simply type `exit` to get out of the image

## Running on a Labs Machine
If you want to try running the simulation on a CSE labs machine, you can first run this command to 
ensure the simulation will run on your local machine...
```bash
$ ssh -L 8081:127.0.0.1:8081 <x500>@<machine>.cselabs.umn.edu
```
Then you can pull and run the docker image with these commands...
```bash
$ singularity pull docker://gorni025/sim
$ singularity run docker://gorni025/sim
```
Then navigate to http://127.0.0.1:8081/ to see the simulation, and press CTRL-C to kill it.

## Running In Docker Environment
If instead, you'd like to run our whole project using our docker environment, you can first clone our repository...
```bash
$ git clone https://github.umn.edu/umn-csci-3081-f21/repo-team-0.git
```
Then, in the `repo-team-0` directory, you can build and run the docker environment with these commands...
```bash
$ bin/build-env.sh
$ bin/run-env.sh
```

Now that you're in the environment with all the dependencies, you can visit 
[This Page](https://docs.google.com/document/d/10t0DOvj9i4Ca7mcpeGftIsEbzwN9e_VLKlY5tXKk1Sg/edit?usp=sharing)
To see how to make and run everything.

