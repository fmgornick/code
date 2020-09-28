Fletcher Gornick, GORNI025

In order to run the program you just need to compile and run the FractalDrawer
class.

you can do this by running "javac FractalDrawer.java", then "java FractalDrawer"
(make sure you're in the project1 directory when running the program)

you may get this warning when you first compile...
Note: ./Canvas.java uses or overrides a deprecated API.
Note: Recompile with -Xlint:deprecation for details.
don't worry though, it'll still run fine.

it will then prompt you to type in the shape (it doesn't matter if you capitalize 
or not, but you must spell it correctly!)

after pressing enter, the program will open a window containing the drawn fractal.  
There is a chance that it doesn't look right, that just means you need to put it in
full screen mode because it doesn't all render instantaneously.

after you close out the drawing, the terminal will display the area of all the shapes
making up the fractal (for the rectangle fractal I used some extra shapes, so the 
area may look a bit bigger than expected)


WARNING:
for the triangle and circle fractal, they're defaulted to 8 levels of recursion, 
which my computer could handle quite comfortably, but the rectangle fractal, I have
it preset to 5 levels of recursion. Your computer may be able to do 6, but 7 is 
pushing it. This doesn't mean that my program isn't working correctly, it just means 
that I have a lot of recursive function calls in my program, it takes a lot of 
computing power.

By the way, you can tweak the levels of recursion in the drawFractal method inside 
the FractalDrawer class file (second to last input parameter).

Also, I added another input parameter for the specific fractal drawing methods. 
It's just my own form of a state variable that works through recursive functions, 
it just iterates through a list of color objects, giving my fractals nice pretty
colors on each level of recursion. You can also change the 0 preset for colorNum in 
the drawFractal meathod to a 1, 2, 3, 4, or 5, which will change up the color scheme 
of the fractal.

PS:
I'm sure you could probably figure this out but my main method is in the 
FractalDrawer class file.
