public class Boat extends Vehicle {
    protected double mpg;
    public Boat(double mpg) {
        this.mpg = mpg;
        nVehicles++;
    }
    public Boat() {
        mpg = 1.5;
        nVehicles++;
    }

    public double getMPG() {
        return mpg;
    }

    public void movingForward() {
        System.out.println("Boat Moving Forward");
    }

    public void movingBackward() {
        System.out.println("Boat Moving Backward");
    }

    public void hoistAnchor() {
        System.out.println("Boat Hoisting Anchor");
    }

    public void dropAnchor() {
        System.out.println("Boat Dropping Anchor");
    }

    public String toString() {
        return "Boat:\t\t" + mpg;
    }
}

