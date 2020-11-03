import java.util.ArrayList;
import java.util.List;
import java.util.Collections;


public class VehicleSorter {
	public static void main(String[] args) {
		List<Vehicle> vehicles = new ArrayList<Vehicle>();

        System.out.println("Unsorted");
        System.out.println();
        vehicles.add(new Car(30));
        vehicles.add(new Boat(22));
        vehicles.add(new Car(72));
        vehicles.add(new Helicopter(11));
        vehicles.add(new Car(45));
        vehicles.add(new Boat(32));
        vehicles.add(new Helicopter(1));
        vehicles.add(new Car(23));
        vehicles.add(new Boat(16));
        vehicles.add(new Car(44));
        vehicles.add(new Helicopter(19));
        vehicles.add(new Boat(9));
        vehicles.add(new Helicopter(13));
        vehicles.add(new Car(69));
        vehicles.add(new Boat(12));
        vehicles.add(new Car(13));
        vehicles.add(new Boat(34));
        vehicles.add(new Car(7));
        vehicles.add(new Helicopter(24));
        vehicles.add(new Car(55));
        vehicles.add(new Car(22));

		for (Vehicle v : vehicles) {
			System.out.println(v);
		}
        System.out.println();

        double min;
        int minIndex;
        for (int i = 0; i < vehicles.size(); i++) {
            min = vehicles.get(i).getMPG();
            minIndex = i;
            for (int j = i+1; j < vehicles.size(); j++) {
                if (vehicles.get(j).getMPG() < min) {
                    min = vehicles.get(j).getMPG();
                    minIndex = j;
                }
            }
            Collections.swap(vehicles, i, minIndex);
        }
		
        System.out.println("Sorted");
        System.out.println();
		for (Vehicle v : vehicles) {
			System.out.println(v);
		}
		
	}
}
