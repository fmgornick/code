Add your project details as mentioned in Section Deliverables.

test machines: CSE apollo & csel-kh1250-01
date: 02/03/2022
names: Peyton Johnson, Fletcher Gornick 
x500s: joh18218, gorni025

purpose:
Using MapReduce to the count number of occurrences of each word in a text file by creating multiple child processes on a single machine.
MapReduce in the greater context of computing is often used for big data analysis but creates multiple child processes that run on multiple machines rather than a single machine like we are doing. 

MapReduce as a map function and reduce function can be summed up by:
mappers- 
    Take in a chunk of the data and creates a set of intermediate (key, value) pairs where key is a word and value is a list of 1's the size of the number of occurrences of the given word (key) within the given chunk, the created sets of (key, value) pairs become our doubly-linked-list.
reducers-
    Take in a grouping (key, value) pairs and return the total count of occurrences of key, in our case adding the ones in the value list.


compile:
1. cd Template                                     // get into correct folder
2. make                                            // makes the files
3. ./mapreduce #mappers #reducers inputFile        // runs the program
// (e.g.) ./mapreduce 5 2 F1.txt                                        
4. make clean                                      //cleans when done

OR

1. cd Template                                     // get into correct folder
2. make t1                                         // makes the files runs the test
3. make clean                                      // clean when done

assumptions:
1. #mappers >= #reducers                       
2. maximum size of a file path is 50 bytes         
3. maximum chunk size 1024 bytes                   
4. using a Linux machine (lib/utils.o will not run on Mac machines)                     

Fletcher did: mapreduce, mapper, error handling
Peyton did: readme, comments, reducer, testing

