public class Helicopter extends Vehicle {
    protected double mpg;
    public Helicopter(double mpg) {
        this.mpg = mpg;
        nVehicles++;
    }
    public Helicopter() {
        mpg = 0.3;
        nVehicles++;
    }

    public double getMPG() {
        return mpg;
    }

    public void movingForward() {
        System.out.println("Helicopter Moving Forward");
    }

    public void movingBackward() {
        System.out.println("Helicopter Moving Backward");
    }

    public void moveUp() {
        System.out.println("Helicopter Moving Up");
    }

    public void moveDown() {
        System.out.println("Helicopter Moving Down");
    }

    public String toString() {
        return "Helicopter:\t" + mpg;
    }
}

