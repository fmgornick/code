// WRITTEN BY GORNI025

import java.awt.*;

public class Rectangle {
    double xPosition = 0;
    double yPosition = 0;
    double width = 0;
    double height = 0;
    Color color = Color.white;

    public Rectangle(double xPos, double yPos, double w, double h) {
        xPosition = xPos;
        yPosition = yPos;
        width = w;
        height = h;
    }
    // initializes values to input parameters

    public Rectangle() {}
    // initializes all values to zero if no input parameters

    public double calculatePerimeter() {
        return (2*width) + (2*height);
    }
    // returns rectangle's perimeter

    public double calculateArea() {
        return width * height;
    }
    // returns rectangle's area

    public void setColor(Color c) {
        color = c;
    }
    // lets you change the rectangle's color (must input Color object)

    public void setPos(double newXPos, double newYPos) {
        xPosition = newXPos;
        yPosition = newYPos;
    }
    // lets you change the location of the rectangle

    public void setHeight(double newHeight) {
        height = newHeight;
    }
    // lets you set the rectangle's height

    public void setWidth(double newWidth) {
        height = newWidth;
    }
    // lets you set the rectangle's width

    public Color getColor() {
        return color;
    }
    // returns the rectangle's color (color object is returned, not a string)

    public double getXPos() {
        return xPosition;
    }
    // returns rectangle's x position

    public double getYPos() {
        return yPosition;
    }
    // returns rectangle's y position

    public double getHeight() {
        return height;
    }
    // returns rectangle's height

    public double getWidth() {
        return width;
    }
    // returns rectangle's width
}
