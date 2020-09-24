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

    public Triangle() {}

    public double calculatePerimeter() {
        return 2 * (Math.sqrt(Math.pow(width/2,2) + Math.pow(height,2))) + width;
    }

    public double calculateArea() {
        return (width/2) * height;
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

    public static void main(String args[]) {
        Triangle e = new Triangle();
        System.out.printf("height: %.2f", e.getHeight());
    }
}
