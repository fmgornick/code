# CSCI 4061 Project 1

**test machines:** CSE apollo & csel-kh1250-01  
**date:** 02/03/2022  
**names:** Peyton Johnson, Fletcher Gornick  
**x500s:** joh18218, gorni025  

purpose:
Using MapReduce to the count number of occurrences of each word in a text file by creating multiple child processes on a single machine.
MapReduce in the greater context of computing is often used for big data analysis but creates multiple child processes that run on multiple machines rather than a single machine like we are doing. 

MapReduce as a map function and reduce function can be summed up by:
mappers- 
    Take in a chunk of the data and creates a set of intermediate (key, value) pairs where key is a word and value is a list of 1's the size of the number of occurrences of the given word (key) within the given chunk, the created sets of (key, value) pairs become our doubly-linked-list.
reducers-
    Take in a grouping (key, value) pairs and return the total count of occurrences of key, in our case adding the ones in the value list.


### COMPILE
1. **get into correct folder:** `cd project1`
2. **make the files:** `make`
3. **run the program:** `./mapreduce #mappers #reducers inputFile`
    - (e.g.): `./mapreduce 5 2 file.txt`
4. **clean when finished:** `make clean`

### OR

1. **get into correct folder:** `cd project1`
2. **run with a test file:** `make t#`
    - (e.g.): `make t1`  will run `./mapreduce 5 2 test/T1/F1.txt`
3. **run test with valgrind output:** `make v#`
    - (e.g.): `make v1` does same as `make t1` but also shows memory overview
4. **clean when finished:** `make clean`

### WARNING
Sometimes, when first trying to make the project, it might give a stack smashing error.  If I run make clean and make again it goes away and never happens again, it only happens occasionally when I try to unzip the file and run it right away.  Not really sure why this happens, but it works just fine after running a make clean after seeing the error.

#### you can see the output files in the created output directory 
all the mapper files are in `output/MapOut/Map_#/<word>.txt`  
the reducer output files are in `output/ReduceOut/Reduce_#.txt`

Also, we added our own test files in the test directory.  We also put them in the solutionexe directory and added a couple extra commands to the makefile in solutionexe.  I don't think that should mess anything up on your end, but if it does, then I apologize.

### assumptions
1. more mappers than reducers
2. maximum size of a file path is 260 bytes
3. using a Linux machine (lib/utils.o will not run on Mac machines)
    - Docker is also fine

If you would like to try running our code with Docker (assuming you already have it installed) you can run these commands...
```bash
  $ docker pull gcc:11
  $ docker run -itv "$(pwd):/usr/bin/src" -w /usr/bin/src --name project1 gcc:11
```
Then you just need to run the commands like normal.  Although valgrind won't work because it doesn't come with the gcc image, so if you wanted, you could add some stuff to a Dockerfile.  I could have just made my own docker image, but I figured it was overboard, and you're just gonna use a CSE Labs machine anyway.

Fletcher did: mapreduce, mapper, error handling  
Peyton did: readme, comments, reducer, testing

