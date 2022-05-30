# CSCI 4061 Project 3

**date:** 04/07/2022  
**group ID:** 69  
**names:** Peyton Johnson, Fletcher Gornick  
**x500s:** joh18218, gorni025  
**test machines:** CSE apollo & csel-kh1250-01  

## <a name="compile"></a>Compile
Before doing anything, you must first download our code.  It can be found and canvas, and should be called `group_69_submission.tar.gz`.  You can extract it by running...

``tar xzvf group_69_submission.tar.gz``

 Now to actually test the server, you must provide a folder of files to be accessed from our program.  This folder should be placed in the same directory you extracted our tar file.
 
 - Traverse to [VOLE](#vole) to see how to run our program in a graphical linux environment.
 - Or check [SSH](#ssh) for a command-line interface.  
 - We also show how to use port forwarding in [this](#port) section so you can run our server on your local machine.
 
### <a name="vole"></a>VOLE
If you want to use Vole to run our program you must first sign in to Vole (obviously).  Then you can follow the above steps to install our program.

Once everything is set up properly, you can compile with a simple `make` command, and you can run it with the [Run](#run) command.

Now suppose your folder of files is called "test", and inside it you have a file called "file.txt".  Then once you run our program, you can navigate to a browser inside of vole and type...

``http://127.0.0.1:<port>/test/file.txt``

where `<port>` is whatever port number you provided, then you should see the requested file in the browser's webpage as well as some output about the request on the terminal you used to run the program.  You can also use a terminal window and type...

``wget http://127.0.0.1:<port>/test/file.txt``

which will download the file onto your machine.  Finally, you can see [here](#terminate) for information on terminating the program.


### <a name="ssh"></a>SSH
Assuming the file is already downloaded in your SSH environment, you can first follow the steps in [Compile](#compile) to get everything set up.

To actually SSH into a CSELabs machine, you can follow the following template...

``ssh <x500>@<machine>.cselabs.umn.edu``

an example would be...

``ssh joh18212@apollo.cselabs.umn.edu``

Once everything is set up properly, you can compile with a simple `make` command, and you can run it with the [Run](#run) command.

Now suppose your folder of files is called "test", and inside it you have a file called "file.txt". Then once you run our program, you would need to open up a new terminal window in your ssh environment (I would suggest using tmux for this), and you can run a command like this...

``wget http://127.0.0.1:<port>/test/file.txt``

Which will download the file onto your machine and produce output about the file to the screen where the server is running.  You can see [here](#terminate) for information on terminating the program.

### <a name="port"></a>SSH with Port Forwarding
If you want to be able to run our server on your local machine, you can ssh using port forwarding.  You can use the following command to do so...

``ssh -L <port>:127.0.0.1:<port> <x500>@<machine>.cselabs.umn.edu``

Where `<port>` is the port number you want to use.  For example, if we wanted to run on a Keller labs machine with port 8888, we can ssh using this command...

``ssh -L 8888:127.0.0.1:8888 gorni025@csel-kh1250-01.cselabs.umn.edu``

Now if you follow the same steps outlined in [SSH](#ssh), you can run the server on your labs machine, and access it on your local machine, just make sure to use the same port number in your run command!

Now you can either use your browser or the wget command just like in vole or ssh, but now via your own local computer!  Again, you can see [here](#terminate) for information on ending the process.

## <a name="run"></a>Run
``./web_server <1> <2> <3> <4> <5> <6> <7> <8>``

1. **port number:** identifies which specific process the network is to be forwarded when it arrives at a server.  Can be any number between 1024 and 65536.
2. **path:** relative file path to folder containing files to be accessed by our server.
3. **dispatchers:** the number of dispatcher threads you want to create.  They receive the requests and add it to the request queue for workers to handle.  Must be at least 1 and no more than 100.
4. **workers:** number of worker threads you want to create.  They receive requests from the queue and process the response which relays the message to the user.  Must be at least 1 and no more than 100.
5. **dynamic flag:** set this so that our program dynamically increases/decreases the size of our thread pool depending on the server load.  1 is set and 0 is not set.
6. **cache flag:** set this so that our program will store recent requests into memory.  This makes it so if a user requests a page already in memory, it's much faster to respond with the content because the program doesn't need to access disk storage.  1 is set and 0 is not set.
7. **queue length:** the fixed length of our request queue.  This sets the maximum number of requests we can have in the queue before blocking our dispatcher threads from taking any more requests.
8. **cache size:** number of entries available in the cache.  This will be the max number of requests that can be found in memory instead of needing to go to disk.

### Example
``./web_server 8888 ./files 100 100 1 1 50 50``

Will run on port 8888, using the "files" folder as web root location.  There will be 100 dispatchers and 100 workers, with dynamic thread pool resizing and caching.  The can be at most 50 requests at once before the dispatchers block, and we can cache 50 entries.

## <a name="terminate"></a>Terminate
You can exit the program with a ^C command which will call the gracefulTerminator function to neatly cancel all the threads, clean up any dynamic memory and close file descriptors.  It should also output the number of requests still pending when the program was terminated.


## How Our Program Works
Our program acts as a very simple server, that can process basic files and send the correct response to the user using multithreading.  

First we take in arguments specifying port, web root path, number of dispatcher/worker threads, flags for dynamic thread resizing and implementing cache, request queue length, and cache size.  Provided all the arguments meet our criteria, we set up our server connection, create a handler for when the eventual interrupt is called, and create all the needed threads.  We also initialize our cache and/or thread pool manager if their flags are set.

Now our program waits for a request to the server.  If a request arrives, we send a dispatcher thread to take that message and place it onto our message queue.  If the message queue is full, then our dispatcher threads wait for a worker to process a request and free up a slot before continuing to handle requests.  Our pool manager might reduce the number of dispatcher threads if the queue gets too large or if the dispatchers aren't getting enough requests.

Our worker threads will process requests on the queue.  If one comes in, then they take the requested file, make sure it's valid, and return the result to the user.  Worker thread also logs information about the request to the terminal screen and a webserver_log file.  If the queue is empty, then there's no request to handle, and the worker waits for a new request to be added to the queue.  Our pool manager might reduce the number of worker threads if the workers aren't getting enough requests.

Also, when the worker receives a request, it first checks to see if the requested file is already stored in memory via the cache (assuming the flag is set).  If so, the worker will retrieve it from the cache, otherwise it's a cache miss and the worker grabs it from the disk.

Finally, when the user wants to kill the server, they can hit ^C, and the signal will be redirected to the gracefulTerminationHandler, which will cancel the threads (and the threads will free up any locks or memory), then close the log file, and delete the cache (if the cache flag was set).

## Extra Credit
For extra credit, we implemented both the dynamic thread pool size manager and the caching mechanism.

### Thread Pool Manager
We decided to try and implement the dynamic worker thread pool manager.  Being as we don't really know much about how capable threads are at handling server requests, we thought it'd be a good idea to just match the number of workers with the number of pending requests.  Unless of course there are no requests, in that case we just leave one worker.

Basically our worker thread manager runs on an infinite loop (until termination) checking to see if the number of workers matches the number of pending requests, if not it will create/delete the necessary number of threads to match.  After each check it will sleep for 1 ms so we don't check too often.

### Cache
Surprisingly enough, we don't know much about caches either so we weren't exactly sure how we wanted to implement ours.  We looked into the LRU and LFU caching policies but decided to stick with what we knew and just went FIFO.  Basically we just have an array of cache entries that we loop through with our cache_idx global.  Whenever we recieve new entries, we just put them into the current cache index and increment.  If we hit the end of the array then we just loop back to index 0.

When processing requests in our worker threads, they first check to see if the request is in the cache, and if so it'll just pull from there (provided the cache flag is set).  Otherwise it pulls from memory and adds it to the cache.  We also need to make sure that if the cache flag is set, then we shouldn't free our memory buffer because all that gets handled by the cache.  And when overwriting memory into an index of our cache array, it also makes sure to free that buffer and assign it the new dynamically allocated data.

## Contributions
**Peyton:** main, dispatch, and commenting/documentation  
**Fletcher:** work, gracefulTerminationHandler, dynamic pool manager, and cache
