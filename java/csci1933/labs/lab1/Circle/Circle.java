public class Circle {
    double radius;
    
    public Circle(double r) {
        radius = r;
    }

    public void setRadius(double newRadius) {
        radius = newRadius;
    }

    public double getRadius() {
        return radius;
    }

    public double getArea() {
        return Math.PI * Math.pow(radius, 2);
    }

    public double getDiameter() {
        return 2 * radius;
    }

    public double getCircumference() {
        return Math.PI * this.getDiameter();
    }
    
    @Override
    public boolean equals(Object other) {
        Circle o;
        if (other instanceof Circle) {
            o = (Circle) other;

            if (this.radius == o.radius) {
                return true;
            }
        }
        return false;
    }
}
