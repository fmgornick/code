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
    public static double drawFractal(String type) {
        Canvas myCanvas = new Canvas(1000,1200);

        switch (type) {
            case "triangle": drawTriangleFractal(1200, 1000, 0, 1000, Color.blue, myCanvas, 8, 0); 
                             break;

            case "circle": drawCircleFractal(200, 400, 400, Color.blue, myCanvas, 10);
                           break;

            case "rectangle": drawRectangleFractal(200, 160, 200, 360, Color.blue, myCanvas, 10);
                              break;

            default: System.out.println("this should not happen");
        }
        return 1;
    }


    //TODO:
    // drawTriangleFractal draws a triangle fractal using recursive techniques
    public static void drawTriangleFractal(double width, double height, double x, double y, Color start, Canvas can, int level, int colorNum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};

        Triangle triangle = new Triangle(x, y, width, height);
        triangle.setColor(start);

        can.drawShape(triangle);

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;

            --level;

            drawTriangleFractal(width/2, height/2, x, y, color[colorNum], can, level, colorNum);
            drawTriangleFractal(width/2, height/2, x + width/2, y, color[colorNum], can, level, colorNum);
            drawTriangleFractal(width/2, height/2, x + width/4, y - height/2, color[colorNum], can, level, colorNum);
        }
    }


    // TODO:
    // drawCircleFractal draws a circle fractal using recursive techniques
    public static void drawCircleFractal(double radius, double x, double y, Color c, Canvas can, int level) {
        Circle circle = new Circle(x, y, radius);
        circle.setColor(c);

        can.drawShape(circle);
    }


    //TODO:
    // drawRectangleFractal draws a rectangle fractal using recursive techniques
    public static void drawRectangleFractal(double width, double height, double x, double y, Color c, Canvas can, int level) {
        Rectangle rectangle = new Rectangle(x, y, width, height);
        rectangle.setColor(c);
        
        can.drawShape(rectangle);
    }

    //TODO:
    // main should ask user for shape input, and then draw the corresponding fractal.
    // should print area of fractal
    public static void main(String args[]){
        Scanner s = new Scanner(System.in);

        System.out.println();
        System.out.println("what shape would you like a fractal of?");
        System.out.print("type triangle, circle, or rectangle: ");

        String shape = s.nextLine().toLowerCase();
        drawFractal(shape);
    }
}
