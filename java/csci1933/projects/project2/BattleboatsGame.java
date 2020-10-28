// Fletcher Gornick, GORNI025

import java.util.Scanner;

public class BattleboatsGame {
    private static BattleboatsBoard game;
    private static int shots = 0;
    private static int turns = 1;
    private static int remaining = 0;
    private static int missile = 0;
    private static int drone = 0;

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        // beginning of game
        System.out.println("hello, welcome to battle boats! please enter 1 to play in standard mode or 2 for expert.");
        System.out.print("> ");
        String se = s.nextLine();
        
        while (true) {
            // initializes standard board
            if (se.equals("1")) {
                game = new BattleboatsBoard(1);
                game.placeBoats();

                System.out.println();
                System.out.println("your board is all set up!");
                System.out.println();
                System.out.println("---OPTIONS---");
                System.out.println("fire - type to fire at a location on the grid (type coordinates separated by a space when prompted)");
                System.out.println();
                System.out.println("missile - type to fire at a location, and every location surrounding it in a one block radius (can only use once)");
                System.out.println();
                System.out.println("drone - type to scan a row or column for boats, returns the number in the row / column (can only use once)");
                System.out.println();
                System.out.println("display - type to see the current grid containing hits, misses, and unknown cells");
                System.out.println();
                System.out.println("print - type to see the location of all the boats, as well as your hits and misses");
                System.out.println();
                System.out.println("quit - end the game");

                game.display();
                break;
            }

            else if (se.equals("2")) {
                // initializes expert board
                game = new BattleboatsBoard(2);
                game.placeBoats();

                System.out.println();
                System.out.println("your board is all set up!");
                System.out.println();
                System.out.println("---OPTIONS---");
                System.out.println("fire - type to fire at a location on the grid (type coordinates separated by a space when prompted)");
                System.out.println();
                System.out.println("missile - type to fire at a location, and every location surrounding it in a one block radius (can only use twice)");
                System.out.println();
                System.out.println("drone - type to scan a row or column for boats, returns the number in the row / column (can only use twice)");
                System.out.println();
                System.out.println("display - type to see the current grid containing hits, misses, and unknown cells");
                System.out.println();
                System.out.println("print - type to see the location of all the boats, as well as your hits and misses");
                System.out.println();
                System.out.println("quit - end the game");

                game.display();
                break;
            }

            else {
                // error detection
                System.out.println();
                System.out.println("invalid input. please enter 1 for standard or 2 for expert.");
                System.out.print("> ");
                se = s.nextLine();
            }
        }

        System.out.println();
        System.out.print("> ");
        String c = s.nextLine();
        
        // if user inputs quit, the game ends
        while(!c.equals("quit")) {

            // must type fire every time you want to fire
            if (c.equals("fire")) {
                System.out.print("coordinates: ");
                c = s.nextLine();

                // if the function takes in the correct number format, then the
                // try block will run
                try {
                    while (true) {

                        // kept everything scanner related with c, so i have to
                        // split and parse the strings
                        int[] coordinates = new int[c.split(" ").length];

                        for (int i = 0; i < c.split(" ").length; i++) {
                            coordinates[i] = Integer.parseInt(c.split(" ")[i]);
                        }

                        // must input coordinates of length 2
                        if (coordinates.length != 2) {
                            System.out.println();
                            System.out.println("error: make sure you type two integers separated by a space");
                            System.out.print("coordinates: ");
                            c = s.nextLine();

                        }

                        // must put coordinates within range
                        else if (coordinates.length == 2 && (coordinates[0] < 0 || coordinates[0] >= game.getBoardLength() || coordinates[1] < 0 || coordinates[1] >= game.getBoardLength())) {
                            System.out.println();
                            System.out.println("penalty: index out of range, you lose a turn");
                            shots++;
                            turns++;
                            break;
                        }

                        // cannot fire at the same location
                        else if (game.getBoardCoordinates(coordinates[0], coordinates[1]) == 'H' || game.getBoardCoordinates(coordinates[0], coordinates[1]) == 'M') {
                            System.out.println();
                            System.out.println("penalty: you already fired at this location, you lose a turn");
                            shots++;
                            turns++;
                            break;
                        }

                        else if (coordinates.length == 2 && coordinates[0] >= 0 && coordinates[0] < game.getBoardLength() && coordinates[1] >= 0 && coordinates[1] < game.getBoardLength()) {
                            game.fire(coordinates[0], coordinates[1]);
                            shots++;

                            // sunk
                            if (game.getBoardCoordinates(coordinates[0], coordinates[1]) == 'H') {
                                if (game.sunk(coordinates[0], coordinates[1])) {
                                    System.out.println();
                                    System.out.println("you sunk my battleship!");
                                    break;
                                }

                                // hit
                                else {
                                    System.out.println();
                                    System.out.println("hit!");
                                    break;
                                }
                            }

                            // miss
                            else {
                                System.out.println();
                                System.out.println("miss");
                                break;
                            }
                        }
                    }

                    // sets up next iteration of while loop
                    turns++;
                    game.display();
                    System.out.println();
                    if (game.gameOver()) break;
                    System.out.println("turn " + turns);
                    System.out.print("> ");
                    c = s.nextLine();
                }

                // catch block runs if the user inputs letters
                catch (NumberFormatException exception) {
                    System.out.println();
                    System.out.println("error: make sure you type two integers separated by a space");
                    c = "fire";
                }

            }

            // must type missile to run this block
            else if (c.equals("missile")) {

                // runs if numbers are inputed
                try {
                    while (true) {

                        // runs in standard if you already used a missile
                        if (se.equals("1") && missile > 0) {
                            System.out.println();
                            System.out.println("you already used the missile once, you only get one missile per game");
                            turns--;
                            break;
                        }

                        // runs in expert if you already used 2 missiles
                        else if (se.equals("2") && missile > 1) {
                            System.out.println();
                            System.out.println("you already used the missile twice, you only get two missiles per game");
                            turns--;
                            break;
                        }

                        System.out.print("coordinates: ");
                        c = s.nextLine();


                        int[] coordinates = new int[c.split(" ").length];

                        for (int i = 0; i < c.split(" ").length; i++) {
                            coordinates[i] = Integer.parseInt(c.split(" ")[i]);
                        }

                        // checks to make sure you can use the missile, if so
                        // it checks that you input the correct amount of
                        // numbers
                        if (((se.equals("1") && missile < 1) || (se.equals("2") && missile < 2)) && coordinates.length != 2) {
                            System.out.println();
                            System.out.println("error: make sure you type two integers separated by a space");
                        }

                        // must put correct range of coordinates in
                        else if (((se.equals("1") && missile < 1) || (se.equals("2") && missile < 2)) && coordinates.length == 2 && (coordinates[0] < 0 || coordinates[0] >= game.getBoardLength() || coordinates[1] < 0 || coordinates[1] >= game.getBoardLength())) {
                            System.out.println();
                            System.out.println("penalty: index out of range, you lose a turn (you can still use the missile on the next turn)");
                            turns++;
                            break;
                        }

                        // fires missile if all conditions met, also says how
                        // many hits
                        else if (((se.equals("1") && missile < 1) || (se.equals("2") && missile < 2)) && coordinates.length == 2 && coordinates[0] >= 0 && coordinates[0] < game.getBoardLength() && coordinates[1] >= 0 && coordinates[1] < game.getBoardLength()) {
                            System.out.println();
                            System.out.println(game.missile(coordinates[0], coordinates[1]) + " hit(s)");
                            missile++;
                            break;
                        }
                    }

                    // sets up next while loop iteration
                    turns++;
                    game.display();
                    System.out.println();
                    if (game.gameOver()) break;
                    System.out.println("turn " + turns);
                    System.out.print("> ");
                    c = s.nextLine();
                }

                // runs catch if you type in letters
                catch (NumberFormatException exception) {
                    System.out.println();
                    System.out.println("error: make sure you type two integers separated by a space");
                    c = "missile";
                }
            }

            // user inputs drone to run this block
            else if (c.equals("drone")) {

                // runs if numbers are inputed
                try {

                    if ((se.equals("1") && drone == 0) || (se.equals("2") && drone < 2)) {
                        System.out.println("row or column? (type \"r\" for row or \"c\" for column)");
                        System.out.print("> ");
                        c = s.nextLine();

                        while (true) {

                            // runs this block if user chooses row
                            if (c.equals("r")) {
                                System.out.println();
                                System.out.println("which row?");
                                System.out.print("> ");

                                c = s.nextLine();
                                int row = Integer.parseInt(c);

                                // checks number of indexes if conditions met
                                if (row >= 0 && ((se.equals("1") && row < 8) || (se.equals("2") && row < 12))) {
                                    System.out.println();
                                    System.out.println("there are " + game.drone(1, row) + " cell(s) containing boats in this row");
                                    drone++;
                                    break;
                                }

                                // warns you if coordinats are out of range
                                else { 
                                    System.out.println();
                                    System.out.println("penalty: index out of range, you lose a turn (you can still use the drone on the next turn)");
                                    turns++;
                                    break;
                                }
                            }

                            // runs if user chooses column
                            else if (c.equals("c")) {
                                System.out.println();
                                System.out.println("which column?");
                                System.out.print("> ");

                                c = s.nextLine();
                                int col = Integer.parseInt(c);

                                // checks indexes if conditions met
                                if (col >= 0 && col < game.getBoardLength()) {
                                    System.out.println();
                                    System.out.println("there are " + game.drone(0, col) + " cell(s) containing boats in this column");
                                    drone++;
                                    break;
                                }

                                // warns you if coordinats are out of range
                                else { 
                                    System.out.println();
                                    System.out.println("penalty: index out of range, you lose a turn (you can still use the drone on the next turn)");
                                    turns++;
                                    break;
                                }
                            }

                            // if user types anything other than r or c
                            else {
                                System.out.println();
                                System.out.println("invalid input, please type \"r\" for row or \"c\" for column)");
                                System.out.print("> ");
                                c = s.nextLine();
                            }
                        }
                    }

                    // if you used up your one drone in standard
                    else if (se.equals("1") && drone > 0) {
                        System.out.println();
                        System.out.println("you already used the drone once, you only get one drone per game");
                        turns--;
                    }

                    // if you used up your two drons in expert
                    else {
                        System.out.println();
                        System.out.println("you already used the drone twice, you only get two drones per game");
                        turns--;
                    }

                    // sets up next iteration for while loop
                    turns++;
                    game.display();
                    System.out.println();
                    if (game.gameOver()) break;
                    System.out.println("turn " + turns);
                    System.out.print("> ");
                    c = s.nextLine();
                }

                // runs if user types in letters when expecting numbers
                catch (NumberFormatException exception) {
                    System.out.println();
                    System.out.println("error: make sure you type an integer");
                    System.out.println();
                    c = "drone";
                }
            }

            // runs display function from BattleboatsBoard class
            else if (c.equals("display")) {
                game.display();
                System.out.println();
                System.out.println("turn " + turns);
                System.out.print("> ");
                c = s.nextLine();
            }

            // runs print function from BattleboatsBoard class (for cheaters)
            else if (c.equals("print")) {
                game.print();
                System.out.println();
                System.out.println("turn " + turns);
                System.out.print("> ");
                c = s.nextLine();
            }


            // checks for typos
            else {
                System.out.println("make sure you typed the command correctly");
                System.out.println();
                System.out.println("COMMAND OPTIONS: \'fire\', \'missile\', \'drone\', \'display\', \'print\', \'quit\'");
                System.out.print("> ");
                c = s.nextLine();

            }
        }

        // checks if all boats have been sunk
        if (game.gameOver()) {
            System.out.println();
            System.out.println("YOU WIN!");
        }

        // runs when user either sinks all the boats or quits
        System.out.println();
        System.out.println("number of shots fired (not including missiles): " + shots);
        System.out.println("number of turns: " + turns);
    }
}
