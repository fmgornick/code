public abstract class Vehicle implements Comparable<Vehicle> {
    //movingForward and movingBackward are left abstract
    public abstract void movingForward();
    public abstract void movingBackward();
    public void start(){System.out.println("Starting Vehicle Engine..");}
    public void stop(){System.out.println("Stopping Vehicle Engine..");}
    protected static int nVehicles = 0;
    public abstract double getMPG();

    /**
     * this method returns true if and only if o is the same type
     * of vehicle and has the same mpg as the vehicle being called upon
     */
    public boolean equals(Object o) {
        if (o != null && this.getClass() == o.getClass()) {
            Vehicle v = (Vehicle)o;
            if (getMPG() == v.getMPG()) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public static final int getNumVehicles() {
        return nVehicles;
    }

    /**
     * This method is used for sorting vehicles by their MPG.
     * TODO:
     * return less than 0 if v has larger MPG than this
     * vehicle, greater than 0 if v has smaller MPG than
     * this vehicle, and 0 if v has the same MPG as
     * this vehicle.
     */
    public int compareTo(Vehicle v) {
        return 0;
    }
}
