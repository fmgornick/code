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

    public Rectangle() {}

    public double calculatePerimeter() {
        return (2*width) + (2*height);
    }

    public double calculateArea() {
        return width * height;
    }

    public void setColor(Color c) {
        color = c;
    }

    public void setPos(double newXPos, double newYPos) {
        xPosition = newXPos;
        yPosition = newYPos;
    }

    public void setHeight(double newHeight) {
        height = newHeight;
    }

    public void setWidth(double newWidth) {
        height = newWidth;
    }

    public Color getColor() {
        return color;
    }

    public double getXPos() {
        return xPosition;
    }

    public double getYPos() {
        return yPosition;
    }

    public double getHeight() {
        return height;
    }

    public double getWidth() {
        return width;
    }
}
