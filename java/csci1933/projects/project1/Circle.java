// WRITTEN BY GORNI025

import java.awt.*;

public class Circle {
    double xPosition = 0;
    double yPosition = 0;
    double radius = 0;
    Color color = Color.white;

    public Circle(double xPos, double yPos, double r) {
        xPosition = xPos;
        yPosition = yPos;
        radius = r;
    }
    // initializes values to input parameters

    public Circle() {}
    // initializes all values to zero if no input parameters

    public double calculatePerimeter() {
        return Math.PI * 2 * radius;
    }
    // returns circle's perimeter

    public double calculateArea() {
        return Math.PI * Math.pow(radius, 2);
    }
    // returns circle's area

    public void setColor(Color c) {
        color = c;
    }
    // lets you change the circle's color (must input Color object)

    public void setPos(double newXPos, double newYPos) {
        xPosition = newXPos;
        yPosition = newYPos;
    }
    // lets you change the location of the circle

    public void setRadius(double newR) {
        radius = newR;
    }
    // lets you change the circle's radius

    public Color getColor() {
        return color;
    }
    // returns the circle's color (color object is returned, not a string)

    public double getXPos() {
        return xPosition;
    }
    // returns circle's x position

    public double getYPos() {
        return yPosition;
    }
    // returns circle's y position

    public double getRadius() {
        return radius;
    }
    // returns circle's radius
}
