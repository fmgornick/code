public class VehicleTester {
    public static void main(String[] args) {
        Bike b1 = new Bike();
        Scooter s = new Scooter();

        Car c = new Car(100);
        Helicopter h = new Helicopter(3);
        Boat b2 = new Boat(15);

        System.out.println("Bike:");
        b1.movingForward();
        b1.movingBackward();
        System.out.println();

        System.out.println("Scooter:");
        s.movingForward();
        s.movingBackward();
        System.out.println();

        System.out.println(c);
        c.movingForward();
        c.movingBackward();
        System.out.println();

        System.out.println(h);
        h.movingForward();
        h.movingBackward();
        h.moveUp();
        h.moveDown();
        System.out.println();

        System.out.println(b2);
        b2.movingForward();
        b2.movingBackward();
        b2.hoistAnchor();
        b2.dropAnchor();
        System.out.println();

        System.out.println("Number of Vehicles: " + Vehicle.getNumVehicles());
    }
}
