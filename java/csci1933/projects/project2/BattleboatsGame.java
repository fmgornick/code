import java.util.Scanner;

public class BattleboatsGame {
    public static BattleboatsBoard game;
    public static int shots = 0;
    public static int turns = 0;
    public static int remaining = 0;
    public static int missile = 0;
    public static int drone = 0;

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        System.out.println("hello, welcome to battle boats! please enter 1 to play in standard mode or 2 for expert.");
        System.out.print("> ");
        String se = s.nextLine();
        
        while (true) {
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
                System.out.println();
                System.out.println("invalid input. please enter 1 for standard or 2 for expert.");
                System.out.print("> ");
                se = s.nextLine();
            }
        }

        System.out.println();
        System.out.print("> ");
        String c = s.nextLine();
        
        while(!c.equals("quit")) {

            if (c.equals("fire")) {
                System.out.print("coordinates: ");
                c = s.nextLine();

                int[] coordinates;

                while (true) {
                    coordinates = new int[c.split(" ").length];
                    for (int i = 0; i < c.split(" ").length; i++) {
                        coordinates[i] = Integer.parseInt(c.split(" ")[i]);
                    }

                    if (coordinates.length != 2) {
                        System.out.println();
                        System.out.println("error: make sure you type two integers separated by a space");
                        System.out.print("coordinates: ");
                        c = s.nextLine();

                    }
                    else if (coordinates.length == 2 && (coordinates[0] < 0 || coordinates[0] >= game.board.length || coordinates[1] < 0 || coordinates[1] >= game.board.length)) {
                        System.out.println();
                        System.out.println("penalty: index out of range, you lose a turn");
                        shots++;
                        turns++;
                        break;
                    }

                    else if (game.board[coordinates[0]][coordinates[1]].status == 'H' || game.board[coordinates[0]][coordinates[1]].status == 'M') {
                        System.out.println();
                        System.out.println("penalty: you already fired at this location, you lose a turn");
                        shots++;
                        turns++;
                        break;
                    }

                    else if (coordinates.length == 2 && coordinates[0] >= 0 && coordinates[0] < game.board.length && coordinates[1] >= 0 && coordinates[1] < game.board.length) {
                        game.fire(coordinates[0], coordinates[1]);
                        shots++;

                        if (game.board[coordinates[0]][coordinates[1]].status == 'H') {
                            if (game.sunk(coordinates[0], coordinates[1])) {
                                System.out.println();
                                System.out.println("you sunk my battleship!");
                                break;
                            }

                            else {
                                System.out.println();
                                System.out.println("hit!");
                                break;
                            }
                        }
                        else {
                            System.out.println();
                            System.out.println("miss");
                            break;
                        }
                    }
                }

                turns++;
                game.display();
                System.out.println();
                System.out.print("> ");
                c = s.nextLine();

            }

            else if (c.equals("missile")) {
                if ((se.equals("1") && missile == 0) || (se.equals("2") && missile < 2)) {
                    System.out.print("coordinates: ");
                    c = s.nextLine();
                    int[] coordinates = new int[c.split(" ").length];
                    for (int i = 0; i < c.split(" ").length; i++) {
                        coordinates[i] = Integer.parseInt(c.split(" ")[i]);
                    }

                    if (coordinates.length == 2 && (coordinates[0] < 0 || coordinates[0] >= game.board.length || coordinates[1] < 0 || coordinates[1] >= game.board.length)) {
                        System.out.println();
                        System.out.println("penalty: index out of range, you lose a turn (you can still use the missile on the next turn)");
                        turns++;
                    }

                    else if (coordinates.length == 2 && coordinates[0] >= 0 && coordinates[0] < game.board.length && coordinates[1] >= 0 && coordinates[1] < game.board.length) {
                        game.missile(coordinates[0], coordinates[1]);
                        missile++;
                    }
                }

                else if (se.equals("1") && missile > 0) {
                    System.out.println();
                    System.out.println("you already used the missle once, you only get one missile per game");
                }

                else {
                    System.out.println();
                    System.out.println("you already used the missle twice, you only get two missiles per game");
                }

                turns++;
                game.display();
                System.out.println();
                System.out.print("> ");
                c = s.nextLine();
            }

            else if (c.equals("drone")) {

                if ((se.equals("1") && drone == 0) || (se.equals("2") && drone < 2)) {
                    System.out.println("row or column? (type \"r\" for row or \"c\" for column)");
                    System.out.print("> ");
                    c = s.nextLine();

                    while (true) {
                        if (c.equals("r")) {
                            System.out.println();
                            System.out.println("which row?");
                            System.out.print("> ");

                            c = s.nextLine();
                            int row = Integer.parseInt(c);

                            if (row >= 0 && ((se.equals("1") && row < 8) || (se.equals("2") && row < 12))) {
                                System.out.println();
                                System.out.println("there are " + game.drone(1, row) + " cell(s) containing boats in this row");
                                drone++;
                                break;
                            }

                            else { 
                                System.out.println();
                                System.out.println("penalty: index out of range, you lose a turn (you can still use the drone on the next turn)");
                                turns++;
                                break;
                            }
                        }

                        else if (c.equals("c")) {
                            System.out.println();
                            System.out.println("which column?");
                            System.out.print("> ");

                            c = s.nextLine();
                            int col = Integer.parseInt(c);

                            if (col >= 0 && col < game.board.length) {
                                System.out.println();
                                System.out.println("there are " + game.drone(0, col) + " cell(s) containing boats in this column");
                                drone++;
                                break;
                            }

                            else { 
                                System.out.println();
                                System.out.println("penalty: index out of range, you lose a turn (you can still use the drone on the next turn)");
                                turns++;
                                break;
                            }
                        }

                        else {
                            System.out.println();
                            System.out.println("invalid input, please type \"r\" for row or \"c\" for column)");
                            System.out.print("> ");
                            c = s.nextLine();
                        }
                    }
                }

                else if (se.equals("1") && drone > 0) {
                    System.out.println();
                    System.out.println("you already used the drone once, you only get one drone per game");
                }

                else {
                    System.out.println();
                    System.out.println("you already used the drone twice, you only get two drones per game");
                }

                turns++;
                game.display();
                System.out.println();
                System.out.print("> ");
                c = s.nextLine();
            }

            else if (c.equals("display")) {
                game.display();
                System.out.println();
                System.out.print("> ");
                c = s.nextLine();
            }

            else if (c.equals("print")) {
                game.print();
                System.out.println();
                System.out.print("> ");
                c = s.nextLine();
            }


            else {
                System.out.println("make sure you typed the command correctly");
                System.out.println();
                System.out.println("COMMAND OPTIONS: \'fire\', \'missile\', \'drone\', \'display\', \'print\', \'quit\'");
                System.out.print("> ");
                c = s.nextLine();

            }
        }

        System.out.println();
        System.out.println("number of shots fired (not including missiles): " + shots);
        System.out.println("number of turns: " + turns);
    }
}
