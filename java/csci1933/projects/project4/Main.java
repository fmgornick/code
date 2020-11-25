// Name: Fletcher Gornick
// x500: gorni025

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int r;
        int c;

        Scanner s = new Scanner(System.in);
        System.out.println("welcome to the maze program!!"); 
        System.out.println("first let's get the size of the maze..."); 
        System.out.println();
        while (true) {
            System.out.print("number of rows: ");
            try {
                r = Integer.parseInt(s.nextLine());
                if (r >= 1) break;
                else {
                    System.out.println("please type an integer greater than or equal to 1");
                    System.out.println();
                }
            }
            catch (Exception e) {
                System.out.println("please type an integer");
                System.out.println();
            }
        }
        System.out.println();

        while (true) {
            System.out.print("number of columns: ");
            try {
                c = Integer.parseInt(s.nextLine());
                if (c >= 1) break;
                else {
                    System.out.println("please type an integer greater than or equal to 1");
                    System.out.println();
                }
            }
            catch (Exception e) {
                System.out.println("please type an integer");
                System.out.println();
            }
        }
        System.out.println();

        MyMaze newMaze = MyMaze.makeMaze(r,c);
        System.out.println("here's the maze...");
        System.out.println();
        newMaze.printMaze();
        System.out.println();
        String yn;
        while (true) {
            System.out.print("would you like to solve the maze [y/n]? ");
            yn = s.next();
            if (yn.length() == 1 && yn.equals("y")) {
                System.out.println();
                System.out.println("ok, maze looks like this now...");
                System.out.println();
                newMaze.solveMaze();
                newMaze.printMaze();
                break;
            }

            else if (yn.length() == 1 && yn.equals("n")) {
                System.out.println("fair enuf mane");
                break;
            }

            else {
                System.out.println("please type either a \'y\' or an \'n\'");
                System.out.println();
            }
        }
        System.out.println("byyyyyy");
        System.out.println();
    }
}
