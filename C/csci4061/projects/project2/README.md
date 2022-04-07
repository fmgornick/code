# CSCI 4061 Project 2

**test machines:** CSE apollo & csel-kh1250-01  
**date:** 03/22/2022  
**names:** Peyton Johnson, Fletcher Gornick  
**x500s:** joh18218, gorni025  

**purpose:**
Using MapReduce to the count number of occurrences of each word in a text file by creating multiple child processes on a single machine. MapReduce in the greater context of computing is often used for big data analysis but creates multiple child processes that run on multiple machines rather than a single machine like we are doing.

## Functions Implemented

### sendChunkData
#### parameter(s): 
- `inputFile`: text file to be sent
- `nMappers`: number of mappers to send data to

Reads one word at a time from inputFile and creates chunks up to 1024 bytes, if adding the next word will make the chunk exceed 1024 bytes sendChunkData then uses the message queue to send the chunk off to a mapper and will begin a new chunk. This process is repeated in a round robin fashion until the input file has reached the end of the file (EOF). 

When EOF is reached sendChunkData sends "END" message to mappers and waits to receive "ACK" (the TCP character implying receival of a package) from all mappers.

### getChunkData
#### parameter(s):
- `mapperID`: ID of current mapper, specified by master

Uses the message queue to receive chunks from the master until an "END" message is received. If an "END" message is received the function will send "ACK" to the master and return NULL. If an "END" message is not received (meaning the file is still being read) the function will return a pointer to the chunk data.

### shuffle
#### parameter(s): 
- `nMappers`: number of mappers (shuffle looks into each mapper directory)
- `nReducers`: number of reducers to send data to

Goes through each mapper directory created (from provided code), and finds each file inside.  For each file found, shuffle writes the whole file path into a message buffer to send to a reducer.  First plugs in the filename into a hashing function to generate the reducer to send it to, then finally sends the path.

Then, similar to `sendChunkData`, shuffle sends "END" message to reducers and waits to receive "ACK" back from them all before returning.

### getInterData
#### parameter(s):
- `key`: mutable string meant to hold the file path of a specific word file for other functions to process
- `reducerID`: ID of current reducer, specified by master

Uses the message queue to receive file paths from the master until an "END" message is received. If an "END" message is received the function will send "ACK" to the master and return 0. If an "END" message is not received (meaning the master is not done sending filenames) the function will change the value of `key` to be the message returned from the queue and return 1.

## Compiling
1. **get into correct folder:** `cd project_2`
2. **make the files:** `make`
3. **run the program:** `./mapreduce #mappers #reducers inputFile`
    - (e.g.): `./mapreduce 5 2 file.txt`
4. **clean when finished:** `make clean`


#### you can see the output files in the created output directory 
all the mapper files are in `output/MapOut/Map_#/<word>.txt`  
the reducer output files are in `output/ReduceOut/Reduce_#.txt`

## Assumptions
- more mappers than reducers
- maximum length of a word is 127 characters
- not using too many mappers/reducers
	- doing so may cause message queue to run out of room and program will fail
- file paths are less than 1023 characters

## Contributions
Peyton did: `getChunkData`, `getInterData`, and documentation   
Fletcher did: `sendChunkData`, `shuffle`, and debugging
