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

    public Circle() {}

    public double calculatePerimeter() {
        return Math.PI * 2 * radius;
    }

    public double calculateArea() {
        return Math.PI * Math.pow(radius, 2);
    }

    public void setColor(Color c) {
        color = c;
    }

    public void setPos(double newXPos, double newYPos) {
        xPosition = newXPos;
        yPosition = newYPos;
    }

    public void setRadius(double newR) {
        radius = newR;
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

    public double getRadius() {
        return radius;
    }
}
