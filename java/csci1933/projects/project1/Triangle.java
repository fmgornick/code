// WRITTEN BY GORNI025

import java.awt.*;

public class Triangle {
    double xPosition = 0;
    double yPosition = 0;
    double width = 0;
    double height = 0;
    Color color = Color.white;

    public Triangle(double xPos, double yPos, double w, double h) {
        xPosition = xPos;
        yPosition = yPos;
        width = w;
        height = h;
    }
    // initializes values to input parameters

    public Triangle() {}
    // initializes all values to zero if no input parameters

    public double calculatePerimeter() {
        return 2 * (Math.sqrt(Math.pow(width/2,2) + Math.pow(height,2))) + width;
    }
    // returns triangle's perimeter

    public double calculateArea() {
        return (width/2) * height;
    }
    // returns triangle's area

    public void setColor(Color c) {
        color = c;
    }
    // lets you change the triangle's color (must input Color object)

    public void setPos(double newXPos, double newYPos) {
        xPosition = newXPos;
        yPosition = newYPos;
    }
    // lets you change the location of the triangle

    public void setHeight(double newHeight) {
        height = newHeight;
    }
    // lets you set the triangle's height

    public void setWidth(double newWidth) {
        height = newWidth;
    }
    // lets you set the triangle's width

    public Color getColor() {
        return color;
    }
    // returns the triangle's color (color object is returned, not a string)

    public double getXPos() {
        return xPosition;
    }
    // returns triangle's x position

    public double getYPos() {
        return yPosition;
    }
    // returns triangle's y position

    public double getHeight() {
        return height;
    }
    // returns triangle's height

    public double getWidth() {
        return width;
    }
    // returns triangle's width
}
