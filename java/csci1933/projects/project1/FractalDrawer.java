// WRITTEN BY GORNI025

// FractalDrawer class draws a fractal of a shape indicated by user input
import java.util.*;
import java.awt.*;
import java.io.*;

public class FractalDrawer {
    private double totalArea=0;  // member variable for tracking the total area

    public FractalDrawer() {}  // contructor


    //TODO:
    // drawFractal creates a new Canvas object
    // and determines which shapes to draw a fractal by calling appropriate helper function
    // drawFractal returns the area of the fractal
    public double drawFractal(String type) {
        Canvas myCanvas = new Canvas(1000,1200);

        switch (type) {
            case "triangle": drawTriangleFractal(1200, 1000, 0, 1000, Color.magenta, myCanvas, 3, 0);
                             return totalArea;

            case "circle": drawCircleFractal(450, 600, 500, Color.magenta, myCanvas, 8, 0);
                           return totalArea;

            case "rectangle": drawRectangleFractal(900, 900, 150, 50, Color.magenta, myCanvas, 5, 0);
                              return totalArea;

            // the last input parameters on the fractal drawer function inputs
            // is the color level of recursion, so you can change the zero to
            // any number between 1 and 5 to get a different colored fractal

            // the second to last number is the level of recursion, so change
            // that one to make the fractals more or less detailed

            default: System.out.println("S P E L L E D     S O M E T H I N G     W R O N G     M Y     G U Y");
                     return 0;
        }
    }


    //TODO:
    // drawTriangleFractal draws a triangle fractal using recursive techniques
    public void drawTriangleFractal(double width, double height, double x, double y, Color start, Canvas can, int level, int colorNum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};  
        // list of colors that is recursively iterated through to get different colors for each level of recursion

        Triangle triangle = new Triangle(x, y, width, height);
        triangle.setColor(start);

        totalArea += triangle.calculateArea();
        // return value of the drawFractal method that prints the fractal's area

        can.drawShape(triangle);
        // template shape for fractal

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;
            // conditional that loops through the color variables

            --level;

            drawTriangleFractal(width/2, height/2, x, y, color[colorNum], can, level, colorNum);
            drawTriangleFractal(width/2, height/2, x + width/2, y, color[colorNum], can, level, colorNum);
            drawTriangleFractal(width/2, height/2, x + width/4, y - height/2, color[colorNum], can, level, colorNum);
            // actual recursive calls
        }
    }


    // TODO:
    // drawCircleFractal draws a circle fractal using recursive techniques
    public void drawCircleFractal(double radius, double x, double y, Color start, Canvas can, int level, int colorNum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};
        // list of colors that is recursively iterated through to get different colors for each level of recursion

        Circle circle = new Circle(x, y, radius);
        circle.setColor(start);

        totalArea += circle.calculateArea();
        // return value of the drawFractal method that prints the fractal's area

        can.drawShape(circle);
        // template shape for fractal

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;
            // conditional that loops through the color variables

            --level;

            drawCircleFractal(radius/2, x + radius/2, y, color[colorNum], can, level, colorNum);
            drawCircleFractal(radius/2, x - radius/2, y, color[colorNum], can, level, colorNum);
            drawCircleFractal(radius/3, x, y + (2*radius)/3, color[colorNum], can, level, colorNum);
            drawCircleFractal(radius/3, x, y - (2*radius)/3, color[colorNum], can, level, colorNum);
            // actual recursive calls
        }
    }


    //TODO:
    // drawRectangleFractal draws a rectangle fractal using recursive techniques
    public void drawRectangleFractal(double width, double height, double x, double y, Color start, Canvas can, int level, int colorNum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};
        // list of colors that is recursively iterated through to get different colors for each level of recursion

        Rectangle rectangle = new Rectangle(x, y, width, height);
        rectangle.setColor(start);

        Rectangle rectangle2 = new Rectangle(x + width/3, y + height/3, width/3, height/3);
        // added a center rectangle in the fractal, so it's a different color in each recursion level too

        totalArea += rectangle.calculateArea() + rectangle2.calculateArea();
        // return value of the drawFractal method that prints the fractal's area

        can.drawShape(rectangle);
        // template shape for fractal

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;
            // conditional that loops through the color variables

            --level;

            drawRectangleFractal(width/3, height/3, x, y + (2*height)/3, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x + width/3, y + (2*height)/3, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x + (2*width)/3, y + (2*height)/3, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x, y + height/3, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x + (2*width)/3, y + height/3, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x, y, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x + width/3, y, color[colorNum], can, level, colorNum);
            drawRectangleFractal(width/3, height/3, x + (2*width)/3, y, color[colorNum], can, level, colorNum);
            // actual recursive calls
        }
    }

    //TODO:
    // main should ask user for shape input, and then draw the corresponding fractal.
    // should print area of fractal
    public static void main(String args[]){
        Scanner s = new Scanner(System.in);

        FractalDrawer fd = new FractalDrawer();
        // need to make an instance of the class because methods are not static

        System.out.println();
        System.out.println("what shape would you like a fractal of?");
        System.out.print("type triangle, circle, or rectangle: ");

        String shape = s.nextLine().toLowerCase();
        // makes it so the user input is NOT case sensitive

        System.out.println();
        System.out.println("area of " + shape + " fractal: " + fd.drawFractal(shape));
    }
}
