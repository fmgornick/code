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
            case "triangle": return drawTriangleFractal(1200, 1000, 0, 1000, Color.blue, myCanvas, 8, 0, 0); 

            case "circle": return drawCircleFractal(450, 600, 500, Color.blue, myCanvas, 8, 0, 0);

            case "rectangle": return drawRectangleFractal(900, 900, 150, 50, Color.blue, myCanvas, 5, 0, 0);

            default: System.out.println("this should not happen");
        }
        return 1;
    }


    //TODO:
    // drawTriangleFractal draws a triangle fractal using recursive techniques
    public static double drawTriangleFractal(double width, double height, double x, double y, Color start, Canvas can, int level, int colorNum, double sum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};

        Triangle triangle = new Triangle(x, y, width, height);
        triangle.setColor(start);

        sum = triangle.calculateArea();

        can.drawShape(triangle);

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;

            --level;

            sum += drawTriangleFractal(width/2, height/2, x, y, color[colorNum], can, level, colorNum, sum);
            sum += drawTriangleFractal(width/2, height/2, x + width/2, y, color[colorNum], can, level, colorNum, sum);
            sum += drawTriangleFractal(width/2, height/2, x + width/4, y - height/2, color[colorNum], can, level, colorNum, sum);
        }

        return sum;
    }


    // TODO:
    // drawCircleFractal draws a circle fractal using recursive techniques
    public static double drawCircleFractal(double radius, double x, double y, Color start, Canvas can, int level, int colorNum, double sum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};

        Circle circle = new Circle(x, y, radius);
        circle.setColor(start);

        sum = circle.calculateArea();

        can.drawShape(circle);

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;

            --level;

            sum += drawCircleFractal(radius/2, x + radius/2, y, color[colorNum], can, level, colorNum, sum);
            sum += drawCircleFractal(radius/2, x - radius/2, y, color[colorNum], can, level, colorNum, sum);
            sum += drawCircleFractal(radius/3, x, y + (2*radius)/3, color[colorNum], can, level, colorNum, sum);
            sum += drawCircleFractal(radius/3, x, y - (2*radius)/3, color[colorNum], can, level, colorNum, sum);
        }

        return sum;
    }


    //TODO:
    // drawRectangleFractal draws a rectangle fractal using recursive techniques
    public static double drawRectangleFractal(double width, double height, double x, double y, Color start, Canvas can, int level, int colorNum, double sum) {
        Color[] color = {Color.red, Color.orange, Color.yellow, Color.green, Color.blue, Color.magenta};

        Rectangle rectangle = new Rectangle(x, y, width, height);
        rectangle.setColor(start);

        Rectangle rectangle2 = new Rectangle(x + width/3, y + height/3, width/3, height/3);
        
        sum = rectangle.calculateArea() + rectangle2.calculateArea();
        
        can.drawShape(rectangle);

        if (level > 0) {

            if (colorNum >= 5) colorNum = 0;
            else ++colorNum;

            --level;

            sum += drawRectangleFractal(width/3, height/3, x, y + (2*height)/3, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x + width/3, y + (2*height)/3, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x + (2*width)/3, y + (2*height)/3, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x, y + height/3, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x + (2*width)/3, y + height/3, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x, y, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x + width/3, y, color[colorNum], can, level, colorNum, sum);
            sum += drawRectangleFractal(width/3, height/3, x + (2*width)/3, y, color[colorNum], can, level, colorNum, sum);
        }

        return sum;
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

        System.out.println();
        System.out.println("area of " + shape + " fractal: " + drawFractal(shape));
    }
}
