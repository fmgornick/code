// FractalDrawer class draws a fractal of a shape indicated by user input
import java.awt.Color;

public class FractalDrawer {
    private double totalArea=0;  // member variable for tracking the total area

    public FractalDrawer() {}  // contructor


    //TODO:
    // drawFractal creates a new Canvas object
    // and determines which shapes to draw a fractal by calling appropriate helper function
    // drawFractal returns the area of the fractal
    public double drawFractal(String type) {
        return 2;
    }


    //TODO:
    // drawTriangleFractal draws a triangle fractal using recursive techniques
    public void drawTriangleFractal(double width, double height, double x, double y, Color c, Canvas can, int level){

    }


    // TODO:
    // drawCircleFractal draws a circle fractal using recursive techniques
    public static void drawCircleFractal(double radius, double x, double y, Color c, Canvas can, int level) {
        Circle circle = new Circle(x, y, radius);
        circle.setColor(c);

        can.drawShape(circle);
        
        if (radius > 1) {
            drawCircleFractal(radius/2, x+radius, y, c, can, level);
            drawCircleFractal(radius/2, x-radius, y, c, can, level);
        }
    }


    //TODO:
    // drawRectangleFractal draws a rectangle fractal using recursive techniques
    public void drawRectangleFractal(double width, double height, double x, double y, Color c, Canvas can, int level) {
    }

    //TODO:
    // main should ask user for shape input, and then draw the corresponding fractal.
    // should print area of fractal
    public static void main(String[] args){

        Canvas canvas = new Canvas(800,800);

        drawCircleFractal(200, 400, 400, Color.blue, canvas, 10);
    }
}
