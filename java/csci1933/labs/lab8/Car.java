public class Car extends Vehicle {
    protected double mpg;
    public Car(double mpg) {
        this.mpg = mpg;
        nVehicles++;
    }
    public Car() {
        mpg = 25.0;
        nVehicles++;
    }

    public double getMPG() {
        return mpg;
    }

    public void movingForward() {
        System.out.println("Car Moving Forward");
    }

    public void movingBackward() {
        System.out.println("Car Moving Backward");
    }

    public String toString() {
        return "Car:\t\t" + mpg;
    }
}
