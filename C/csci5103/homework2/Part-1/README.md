# CSCI 5103 Assignment 3 Pt 1
## Compile
To compile, simply run:
```sh
make
```
This will output a `part1.o` object file and a `part1` executable.  We will only need the executable for the following steps.

## Run
you can run the code with the following command:
```sh
./part1 <num_items>
```
`<num_items>` simply represents the number of items you want each producer to add to our bounded buffer.  Leaving this flag empty, or failing to provide an integer argument will result in the program defaulting the value of `<num_items>` to 100.  
When this program finishes executing, you should have four new files: `producer_red.log`,  `producer_white.log`,  `producer_blue.log`, and `consumer.log`.  You can check that each file contains the correct output yourself.

## Clean
To restore this directory to just `part1.c`, `Makefile`, and this `README.md`, you can run: 
```sh
make clean
```
This will remove all the logfiles, our object file, as well as our executable.
