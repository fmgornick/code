import java.util.*;
import java.lang.String;

public class HistogramApp {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String userRange;
        String[] userRangeArray;

        System.out.println("---Histogram Console---");
        System.out.println("Options");
        System.out.println("add - used to add numbers to the histogram");
        System.out.println("print - prints the histogram to the screen");
        System.out.println("quit - leave the program");
        System.out.println();

        System.out.print("Enter Range to get started: ");
        userRange = s.nextLine();
        userRangeArray = userRange.split(" ");
        Histogram a = new Histogram(Integer.parseInt(userRangeArray[0]), Integer.parseInt(userRangeArray[1]));

        System.out.println();
        System.out.print("> ");

        String c = s.nextLine();
        while (!c.equals("quit")) {

            if (c.equals("add")) {
                System.out.print("> Enter number(s): ");
                userRangeArray = s.nextLine().split(" ");

                for (int i = 0; i < userRangeArray.length; ++i) {
                    if (a.add(Integer.parseInt(userRangeArray[i])) == false) 
                        System.out.println(Integer.parseInt(userRangeArray[i]) + " is not in the range");
                }

                System.out.print("> ");
                c = s.nextLine();
            }

            else if (c.equals("print")) {
                System.out.println();
                System.out.print(a.toString());

                System.out.print("> ");
                c = s.nextLine();
            }

            else {
                System.out.println("spelled something wrong g");
                System.out.print("> ");
                c = s.nextLine();
            }
        }
        System.out.println("Bye!");




    }
}
