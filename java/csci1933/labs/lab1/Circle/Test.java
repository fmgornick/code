import java.util.Scanner;

public class Test {
    public static void main(String args[]) {
        Scanner object = new Scanner(System.in);
        System.out.print("Enter Radius: ");

        String radiusString = object.nextLine();
        double radiusInt = Integer.parseInt(radiusString);
        
        Circle myCircle = new Circle(radiusInt);
        Circle otherCircle = new Circle(4);

        System.out.println();
        System.out.println("Radius: " + myCircle.getRadius());
        System.out.println("Diameter: " + myCircle.getDiameter());
        System.out.println("Circumference: " + myCircle.getCircumference());
        System.out.println("Area: " + myCircle.getArea());
        System.out.println(myCircle.equals(otherCircle));
    }
}
