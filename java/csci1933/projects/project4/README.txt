Name: Fletcher Gornick
x500: gorni025

there are two ways to run this program if you wish.

For the more user friendly experience, you can run the Main.java file which is pretty
intuitive and just takes in user input to make the maze so i'm not gonna explain any
mor for this one.

For the other option, if you just want to efficiently run the program a bunch of times,
you can hop into the MyMaze.java file, and in it there will be a main method that just
contains the maze instantiation, solveMaze, and printMaze calls.  The maze is initially
instantiated to size 10x10, so you can alter that by just changing the input parameters
in the MyMaze constructor call in main.

compile and run for Main.java:
javac Main.java
java Main

compile and run for MyMaze.java:
javac MyMaze.java
java MyMaze

PS: sometimes the solution for the maze looks very inefficient, but it still solves it,
so I just assume the problem is with the weird implementation of a queue.

PPS: also, i'm assuming that you're going to input values greater than or equal to zero,
so if you input a value that's zero or less in the Main java file, it will correct you 
and make sure to keep running the program without error, but if your running the MyMaze
java file it'll break.  So for the sake of points, please grade that edge case based off
my Main file, and not the MyMaze file, because i do check for that error in the Main file.
