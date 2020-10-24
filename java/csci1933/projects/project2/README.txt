Fletcher Gornick, GORNI025

in order to run the program, you just need to compile and run the BattleBoatsGame
class.

you can do this by running "javac BattleBoatsGame.java", then "java BattleBoatsGame".
(make sure you're in the project2 directory when running the program).

it will prompt you to type in a 1 or 2 for standard or expert respectively.
(I should have typo checks on everything).

after pressing enter, the program will then create the board and a list of options
will pop up and you have the option to type any of them in.
(make sure to type in all lowercase, it won't recognize uppercase).

if you type "fire" or "missile", you will be prompted to type in coordinates, make
sure to type the two values separated by a space.
(if not done correct, it will notify you and let you try again, unless you type
two coordinates with index out of range, then you lose a turn).

fire will shoot at said coordinate and let you know if it was a hit / miss / sink.
(you must type fire every time you want to use the fire feature (sowwyyy)).

missile will shoot at the coordinate, as well as any in a one-block vicinity.  You
only get one for standard and two for expert.

if you type "drone", the interface will prompt you to type "r" for row or "c" for
column.  Then it will prompt you to type in the row/column number and return the 
number of cells.  You only get one for standard and two for expert.
(if you don't type in "r" for row or "c" you'll be prompted again, same goes for 
row / column numbers if they're letters, and you lose a turn if they're out of range).


if you type "display", it will show your progress on the board without displaying
the whole boat locations.  Program also automatically runs this after every turn

if you type "print", it will show all your hits and misses, as well as the locations 
of the boats you haven't yet fired at.

if you type "quit" or manage to sink all the boats, the program will end, and it
will show the number of turns you took, as well as the number of shots fired.


PS: if you want to just quickly get to the end to see if my ending turns / shots
are counted correctly, you can change the "public static int missile" to like -100
so you can just spam the missile to get to the end.
