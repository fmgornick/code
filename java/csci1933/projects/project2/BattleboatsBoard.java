public class BattleboatsBoard {
    public int se;
    public Cell[][] board;

    public Cell[] boat1 = new Cell[5];
    public Cell[] boat2 = new Cell[5];
    public Cell[] boat3 = new Cell[4];
    public Cell[] boat4 = new Cell[4];
    public Cell[] boat5 = new Cell[3];
    public Cell[] boat6 = new Cell[3];
    public Cell[] boat7 = new Cell[3];
    public Cell[] boat8 = new Cell[3];
    public Cell[] boat9 = new Cell[2];
    public Cell[] boat10 = new Cell[2];

    public Cell[][] boatArray = {boat1, boat2, boat3, boat4, boat5, boat6, boat7, boat8, boat9, boat10};
    public String[] boatNames = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};


    // constructor
    public BattleboatsBoard(int se) {
        this.se = se;
    }


    // generate random cell location and place boats if no overlap
    // takes input from placeBoats method
    public int randomize(Cell[] boat, int verticalOrHorizontal, int remaining) {

        // for standard board
        if (se == 1) {
        int randRow1 = (int) Math.floor(Math.random() * (9 - boat.length));
        int randCol1 = (int) Math.floor(Math.random() * 8);

        int randRow2 = (int) Math.floor(Math.random() * 8);
        int randCol2 = (int) Math.floor(Math.random() * (9 - boat.length));

            if (verticalOrHorizontal == 0) {
                for (int i = 0; i < boat.length; i++) {
                    if (board[randRow1 + i][randCol1].status != '-') return remaining;
                }
                for (int i = 0; i < boat.length; i++) {
                    board[randRow1][randCol1].status = 'B';
                    boat[i] = board[randRow1][randCol1];
                    randRow1++;
                }
                return --remaining;
            }

            else {
                for (int i = 0; i < boat.length; i++) {
                    if (board[randRow2][randCol2 + i].status != '-') return remaining;
                }
                for (int i = 0; i < boat.length; i++) {
                    board[randRow2][randCol2].status = 'B';
                    boat[i] = board[randRow2][randCol2];
                    randCol2++;
                }
                return --remaining;
            }
        }

        // for expert board
        else {
        int randRow1 = (int) Math.floor(Math.random() * (13 - boat.length));
        int randCol1 = (int) Math.floor(Math.random() * 12);

        int randRow2 = (int) Math.floor(Math.random() * 12);
        int randCol2 = (int) Math.floor(Math.random() * (13 - boat.length));

            if (verticalOrHorizontal == 0) {
                for (int i = 0; i < boat.length; i++) {
                    if (board[randRow1 + i][randCol1].status != '-') return remaining;
                }
                for (int i = 0; i < boat.length; i++) {
                    board[randRow1][randCol1].status = 'B';
                    boat[i] = board[randRow1][randCol1];
                    randRow1++;
                }
                return --remaining;
            }

            else {
                for (int i = 0; i < boat.length; i++) {
                    if (board[randRow2][randCol2 + i].status != '-') return remaining;
                }
                for (int i = 0; i < boat.length; i++) {
                    board[randRow2][randCol2].status = 'B';
                    boat[i] = board[randRow2][randCol2];
                    randCol2++;
                }
                return --remaining;
            }
        }
    }


    // run randomize program for each boat to initialize
    public void placeBoats() {
        if (se == 1) {
            int remainingBoats = 5;
            board = new Cell[8][8];
             
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[i].length; j++) {
                    board[i][j] = new Cell(i,j,'-');
                }
            }

            // standard mode (every odd boat from 1 - 9 is standard
            while(remainingBoats > 0) {
                switch (remainingBoats) {
                    case 1:
                        remainingBoats = randomize(boat9, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 2:
                        remainingBoats = randomize(boat7, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 3:
                        remainingBoats = randomize(boat5, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 4:
                        remainingBoats = randomize(boat3, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 5:
                        remainingBoats = randomize(boat1, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    default:
                        remainingBoats = 0;
                        break;
                }
            }
        }

        else if (se == 2) {
            int remainingBoats = 10;
            board = new Cell[12][12];

            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[i].length; j++) {
                    board[i][j] = new Cell(i,j,'-');
                }
            }

            // expert mode (every boat 1 - 10 for expert)
            while(remainingBoats > 0) {
                switch (remainingBoats) {
                    case 1:
                        remainingBoats = randomize(boat10, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 2:
                        remainingBoats = randomize(boat9, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 3:
                        remainingBoats = randomize(boat8, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 4:
                        remainingBoats = randomize(boat7, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 5:
                        remainingBoats = randomize(boat6, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 6:
                        remainingBoats = randomize(boat5, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 7:
                        remainingBoats = randomize(boat4, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 8:
                        remainingBoats = randomize(boat3, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 9:
                        remainingBoats = randomize(boat2, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    case 10:
                        remainingBoats = randomize(boat1, (int) Math.floor(Math.random() * 2), remainingBoats);
                        break;
                    default:
                        remainingBoats = 0;
                        break;
                }
            }
        }
    }


    // check a location to see if there's a boat there
    public boolean isBoat(int r, int c) {
        if (se == 1) {
            for (int i = 0; i < boatArray.length; i += 2) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].row == r && boatArray[i][j].col == c) return true;
                }
            }
            return false;
        }

        else {
            for (int i = 0; i < boatArray.length; i++) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].row == r && boatArray[i][j].col == c) return true;
                }
            }
            return false;
        }
    }

    // if there is a boat, check which index on the boat the coordinate is
    public int indexBoat(int r, int c) {
        if (se == 1) {
            for (int i = 0; i < boatArray.length; i += 2) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].row == r && boatArray[i][j].col == c) {
                        return i;
                    }
                }
            }
            return -1;
        }

        else {
            for (int i = 0; i < boatArray.length; i++) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].row == r && boatArray[i][j].col == c) {
                        return i;
                    }
                }
            }
            return -1;
        }
    }


    // change coordinate location from '-' to 'M' or 'B' to 'H'.  Also updates
    // the boats elements
    public int fire(int r, int c) {
        if(isBoat(r,c)) {
            board[r][c].status = 'H';
            for (int i = 0; i < boatArray[indexBoat(r,c)].length; i++) {
                if (boatArray[indexBoat(r,c)][i].row == r && boatArray[indexBoat(r,c)][i].col == c) {
                    boatArray[indexBoat(r,c)][i].status = board[r][c].status;
                }
            }
            return 1;
        }

        else {
            board[r][c].status = 'M';
            return 0;
        }
    }


    // fires at coordinate and every one-block surrounding location.  Covers
    // every case.  Returns number of hits
    public int missile(int r, int c) {
        int numHits = 0;
        if (r > 0 && r < board.length - 1 && c > 0 && c < board[r].length - 1) {
            numHits += fire(r-1, c-1);
            numHits += fire(r-1, c);
            numHits += fire(r-1, c+1);
            numHits += fire(r, c-1);
            numHits += fire(r, c);
            numHits += fire(r, c+1);
            numHits += fire(r+1, c-1);
            numHits += fire(r+1, c);
            numHits += fire(r+1, c+1);
        }

        else if (r > 0 && r < board.length - 1 && c == 0 && c < board[r].length - 1) {
            numHits += fire(r-1, c);
            numHits += fire(r-1, c+1);
            numHits += fire(r, c);
            numHits += fire(r, c+1);
            numHits += fire(r+1, c);
            numHits += fire(r+1, c+1);
        }

        else if (r > 0 && r < board.length - 1 && c > 0 && c == board[r].length - 1) {
            numHits += fire(r-1, c-1);
            numHits += fire(r-1, c);
            numHits += fire(r, c-1);
            numHits += fire(r, c);
            numHits += fire(r+1, c-1);
            numHits += fire(r+1, c);
        }

        else if (r == 0 && r < board.length - 1 && c > 0 && c < board[r].length - 1) {
            numHits += fire(r, c-1);
            numHits += fire(r, c);
            numHits += fire(r, c+1);
            numHits += fire(r+1, c-1);
            numHits += fire(r+1, c);
            numHits += fire(r+1, c+1);
        }

        else if (r == 0 && r < board.length - 1 && c == 0 && c < board[r].length - 1) {
            numHits += fire(r, c);
            numHits += fire(r, c+1);
            numHits += fire(r+1, c);
            numHits += fire(r+1, c+1);
        }

        else if (r == 0 && r < board.length - 1 && c > 0 && c == board[r].length - 1) {
            numHits += fire(r, c-1);
            numHits += fire(r, c);
            numHits += fire(r+1, c-1);
            numHits += fire(r+1, c);
        }

        else if (r > 0 && r == board.length - 1 && c > 0 && c < board[r].length - 1) {
            numHits += fire(r-1, c-1);
            numHits += fire(r-1, c);
            numHits += fire(r-1, c+1);
            numHits += fire(r, c-1);
            numHits += fire(r, c);
            numHits += fire(r, c+1);
        }

        else if (r > 0 && r == board.length - 1 && c == 0 && c < board[r].length - 1) {
            numHits += fire(r-1, c);
            numHits += fire(r-1, c+1);
            numHits += fire(r, c);
            numHits += fire(r, c+1);
        }

        else {
            numHits += fire(r-1, c-1);
            numHits += fire(r-1, c);
            numHits += fire(r, c-1);
            numHits += fire(r, c);
        }

        return numHits;
    }


    // iterates through row / column and returns all indexes containing a boat
    public int drone(int direction, int index) {
        int numCells = 0;
        if (direction == 0) {
            for (int i = 0; i < board.length; i++) {
                if (board[i][index].status == 'H' || board[i][index].status == 'B') {
                    numCells++;
                }
            }
        }

        else {
            for (int i = 0; i < board[index].length; i++) {
                if (board[index][i].status == 'H' || board[index][i].status == 'B') {
                    numCells++;
                }
            }
        }

        return numCells;
    }


    // iterates through boat to check if every element was hit
    public boolean sunk(int r, int c) {
        for (int i = 0; i < boatArray[indexBoat(r,c)].length; i++) {
            if (boatArray[indexBoat(r,c)][i].status != 'H') return false;
        }
        return true;
    }


    // checks to see if every boat is hit
    public boolean gameOver() {
        if (se == 1) {
            for (int i = 0; i < boatArray.length; i += 2) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].status != 'H') return false;
                }
            }
            return true;
        }

        else {
            for (int i = 0; i < boatArray.length; i++) {
                for (int j = 0; j < boatArray[i].length; j++) {
                    if (boatArray[i][j].status != 'H') return false;
                }
            }
            return true;
        }
    }


    // returns an 'X' for a hit loaction, and 'O' for a missed location, and
    // nothing if it hasn't been fired at
    public String displayHelper(int r, int c) {
        switch (board[r][c].status) {
            case 'H':
                return "X";

            case 'M':
                return "O";

            default:
                return " ";
        }
    }


    // displays the whole grid
    public void display() {
        // standard grid
        if (se == 1) {
            System.out.println();
            System.out.println("    0   1   2   3   4   5   6   7  ");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("0 | " + displayHelper(0,0) + " | " + displayHelper(0,1) + " | " + displayHelper(0,2) + " | " + displayHelper(0,3) + " | " 
                                    + displayHelper(0,4) + " | " + displayHelper(0,5) + " | " + displayHelper(0,6) + " | " + displayHelper(0,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("1 | " + displayHelper(1,0) + " | " + displayHelper(1,1) + " | " + displayHelper(1,2) + " | " + displayHelper(1,3) + " | " 
                                    + displayHelper(1,4) + " | " + displayHelper(1,5) + " | " + displayHelper(1,6) + " | " + displayHelper(1,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("2 | " + displayHelper(2,0) + " | " + displayHelper(2,1) + " | " + displayHelper(2,2) + " | " + displayHelper(2,3) + " | " 
                                    + displayHelper(2,4) + " | " + displayHelper(2,5) + " | " + displayHelper(2,6) + " | " + displayHelper(2,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("3 | " + displayHelper(3,0) + " | " + displayHelper(3,1) + " | " + displayHelper(3,2) + " | " + displayHelper(3,3) + " | " 
                                    + displayHelper(3,4) + " | " + displayHelper(3,5) + " | " + displayHelper(3,6) + " | " + displayHelper(3,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("4 | " + displayHelper(4,0) + " | " + displayHelper(4,1) + " | " + displayHelper(4,2) + " | " + displayHelper(4,3) + " | " 
                                    + displayHelper(4,4) + " | " + displayHelper(4,5) + " | " + displayHelper(4,6) + " | " + displayHelper(4,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("5 | " + displayHelper(5,0) + " | " + displayHelper(5,1) + " | " + displayHelper(5,2) + " | " + displayHelper(5,3) + " | " 
                                    + displayHelper(5,4) + " | " + displayHelper(5,5) + " | " + displayHelper(5,6) + " | " + displayHelper(5,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("6 | " + displayHelper(6,0) + " | " + displayHelper(6,1) + " | " + displayHelper(6,2) + " | " + displayHelper(6,3) + " | " 
                                    + displayHelper(6,4) + " | " + displayHelper(6,5) + " | " + displayHelper(6,6) + " | " + displayHelper(6,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("7 | " + displayHelper(7,0) + " | " + displayHelper(7,1) + " | " + displayHelper(7,2) + " | " + displayHelper(7,3) + " | " 
                                    + displayHelper(7,4) + " | " + displayHelper(7,5) + " | " + displayHelper(7,6) + " | " + displayHelper(7,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
        }

        // expert grid
        else {
            System.out.println();
            System.out.println("     0   1   2   3   4   5   6   7   8   9   10  11 ");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("0  | " + displayHelper(0,0) + " | " + displayHelper(0,1) + " | " + displayHelper(0,2) + " | " + displayHelper(0,3) + " | " 
                                    + displayHelper(0,4) + " | " + displayHelper(0,5) + " | " + displayHelper(0,6) + " | " + displayHelper(0,7) + " | "
                                    + displayHelper(0,8) + " | " + displayHelper(0,9) + " | " + displayHelper(0,10) + " | " + displayHelper(0,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("1  | " + displayHelper(1,0) + " | " + displayHelper(1,1) + " | " + displayHelper(1,2) + " | " + displayHelper(1,3) + " | " 
                                    + displayHelper(1,4) + " | " + displayHelper(1,5) + " | " + displayHelper(1,6) + " | " + displayHelper(1,7) + " | "
                                    + displayHelper(1,8) + " | " + displayHelper(1,9) + " | " + displayHelper(1,10) + " | " + displayHelper(1,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("2  | " + displayHelper(2,0) + " | " + displayHelper(2,1) + " | " + displayHelper(2,2) + " | " + displayHelper(2,3) + " | " 
                                    + displayHelper(2,4) + " | " + displayHelper(2,5) + " | " + displayHelper(2,6) + " | " + displayHelper(2,7) + " | "
                                    + displayHelper(2,8) + " | " + displayHelper(2,9) + " | " + displayHelper(2,10) + " | " + displayHelper(2,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("3  | " + displayHelper(3,0) + " | " + displayHelper(3,1) + " | " + displayHelper(3,2) + " | " + displayHelper(3,3) + " | " 
                                    + displayHelper(3,4) + " | " + displayHelper(3,5) + " | " + displayHelper(3,6) + " | " + displayHelper(3,7) + " | "
                                    + displayHelper(3,8) + " | " + displayHelper(3,9) + " | " + displayHelper(3,10) + " | " + displayHelper(3,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("4  | " + displayHelper(4,0) + " | " + displayHelper(4,1) + " | " + displayHelper(4,2) + " | " + displayHelper(4,3) + " | " 
                                    + displayHelper(4,4) + " | " + displayHelper(4,5) + " | " + displayHelper(4,6) + " | " + displayHelper(4,7) + " | "
                                    + displayHelper(4,8) + " | " + displayHelper(4,9) + " | " + displayHelper(4,10) + " | " + displayHelper(4,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("5  | " + displayHelper(5,0) + " | " + displayHelper(5,1) + " | " + displayHelper(5,2) + " | " + displayHelper(5,3) + " | " 
                                    + displayHelper(5,4) + " | " + displayHelper(5,5) + " | " + displayHelper(5,6) + " | " + displayHelper(5,7) + " | "
                                    + displayHelper(5,8) + " | " + displayHelper(5,9) + " | " + displayHelper(5,10) + " | " + displayHelper(5,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("6  | " + displayHelper(6,0) + " | " + displayHelper(6,1) + " | " + displayHelper(6,2) + " | " + displayHelper(6,3) + " | " 
                                    + displayHelper(6,4) + " | " + displayHelper(6,5) + " | " + displayHelper(6,6) + " | " + displayHelper(6,7) + " | "
                                    + displayHelper(6,8) + " | " + displayHelper(6,9) + " | " + displayHelper(6,10) + " | " + displayHelper(6,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("7  | " + displayHelper(7,0) + " | " + displayHelper(7,1) + " | " + displayHelper(7,2) + " | " + displayHelper(7,3) + " | " 
                                    + displayHelper(7,4) + " | " + displayHelper(7,5) + " | " + displayHelper(7,6) + " | " + displayHelper(7,7) + " | "
                                    + displayHelper(7,8) + " | " + displayHelper(7,9) + " | " + displayHelper(7,10) + " | " + displayHelper(7,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("8  | " + displayHelper(8,0) + " | " + displayHelper(8,1) + " | " + displayHelper(8,2) + " | " + displayHelper(8,3) + " | " 
                                    + displayHelper(8,4) + " | " + displayHelper(8,5) + " | " + displayHelper(8,6) + " | " + displayHelper(8,7) + " | "
                                    + displayHelper(8,8) + " | " + displayHelper(8,9) + " | " + displayHelper(8,10) + " | " + displayHelper(8,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("9  | " + displayHelper(9,0) + " | " + displayHelper(9,1) + " | " + displayHelper(9,2) + " | " + displayHelper(9,3) + " | " 
                                    + displayHelper(9,4) + " | " + displayHelper(9,5) + " | " + displayHelper(9,6) + " | " + displayHelper(9,7) + " | "
                                    + displayHelper(9,8) + " | " + displayHelper(9,9) + " | " + displayHelper(9,10) + " | " + displayHelper(9,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("10 | " + displayHelper(10,0) + " | " + displayHelper(10,1) + " | " + displayHelper(10,2) + " | " + displayHelper(10,3) + " | " 
                                    + displayHelper(10,4) + " | " + displayHelper(10,5) + " | " + displayHelper(10,6) + " | " + displayHelper(10,7) + " | "
                                    + displayHelper(10,8) + " | " + displayHelper(10,9) + " | " + displayHelper(10,10) + " | " + displayHelper(10,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("11 | " + displayHelper(11,0) + " | " + displayHelper(11,1) + " | " + displayHelper(11,2) + " | " + displayHelper(11,3) + " | " 
                                    + displayHelper(11,4) + " | " + displayHelper(11,5) + " | " + displayHelper(11,6) + " | " + displayHelper(11,7) + " | "
                                    + displayHelper(11,8) + " | " + displayHelper(11,9) + " | " + displayHelper(11,10) + " | " + displayHelper(11,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
        }
    }


    // returns 'X' for hits, 'O' for misses, nothing if no boats are present,
    // and the boats character names if boats were present and not fired at
    public String printHelper(int r, int c) {
        switch (board[r][c].status) {
            case '-':
                return " ";

            case 'B':
                if (se == 1) return boatNames[indexBoat(r,c) / 2];
                else return boatNames[indexBoat(r,c)];

            case 'H':
                return "X";

            case 'M':
                return "O";

            default:
                return "n";
        }
    }


    // prints the grid (including non-fired-at boat locations)
    public void print() {
        // standard
        if (se == 1) {
            System.out.println();
            System.out.println("    0   1   2   3   4   5   6   7  ");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("0 | " + printHelper(0,0) + " | " + printHelper(0,1) + " | " + printHelper(0,2) + " | " + printHelper(0,3) + " | " 
                                    + printHelper(0,4) + " | " + printHelper(0,5) + " | " + printHelper(0,6) + " | " + printHelper(0,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("1 | " + printHelper(1,0) + " | " + printHelper(1,1) + " | " + printHelper(1,2) + " | " + printHelper(1,3) + " | " 
                                    + printHelper(1,4) + " | " + printHelper(1,5) + " | " + printHelper(1,6) + " | " + printHelper(1,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("2 | " + printHelper(2,0) + " | " + printHelper(2,1) + " | " + printHelper(2,2) + " | " + printHelper(2,3) + " | " 
                                    + printHelper(2,4) + " | " + printHelper(2,5) + " | " + printHelper(2,6) + " | " + printHelper(2,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("3 | " + printHelper(3,0) + " | " + printHelper(3,1) + " | " + printHelper(3,2) + " | " + printHelper(3,3) + " | " 
                                    + printHelper(3,4) + " | " + printHelper(3,5) + " | " + printHelper(3,6) + " | " + printHelper(3,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("4 | " + printHelper(4,0) + " | " + printHelper(4,1) + " | " + printHelper(4,2) + " | " + printHelper(4,3) + " | " 
                                    + printHelper(4,4) + " | " + printHelper(4,5) + " | " + printHelper(4,6) + " | " + printHelper(4,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("5 | " + printHelper(5,0) + " | " + printHelper(5,1) + " | " + printHelper(5,2) + " | " + printHelper(5,3) + " | " 
                                    + printHelper(5,4) + " | " + printHelper(5,5) + " | " + printHelper(5,6) + " | " + printHelper(5,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("6 | " + printHelper(6,0) + " | " + printHelper(6,1) + " | " + printHelper(6,2) + " | " + printHelper(6,3) + " | " 
                                    + printHelper(6,4) + " | " + printHelper(6,5) + " | " + printHelper(6,6) + " | " + printHelper(6,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("7 | " + printHelper(7,0) + " | " + printHelper(7,1) + " | " + printHelper(7,2) + " | " + printHelper(7,3) + " | " 
                                    + printHelper(7,4) + " | " + printHelper(7,5) + " | " + printHelper(7,6) + " | " + printHelper(7,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
        }

        // expert
        else {
            System.out.println();
            System.out.println("     0   1   2   3   4   5   6   7   8   9   10  11 ");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("0  | " + printHelper(0,0) + " | " + printHelper(0,1) + " | " + printHelper(0,2) + " | " + printHelper(0,3) + " | " 
                                    + printHelper(0,4) + " | " + printHelper(0,5) + " | " + printHelper(0,6) + " | " + printHelper(0,7) + " | "
                                    + printHelper(0,8) + " | " + printHelper(0,9) + " | " + printHelper(0,10) + " | " + printHelper(0,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("1  | " + printHelper(1,0) + " | " + printHelper(1,1) + " | " + printHelper(1,2) + " | " + printHelper(1,3) + " | " 
                                    + printHelper(1,4) + " | " + printHelper(1,5) + " | " + printHelper(1,6) + " | " + printHelper(1,7) + " | "
                                    + printHelper(1,8) + " | " + printHelper(1,9) + " | " + printHelper(1,10) + " | " + printHelper(1,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("2  | " + printHelper(2,0) + " | " + printHelper(2,1) + " | " + printHelper(2,2) + " | " + printHelper(2,3) + " | " 
                                    + printHelper(2,4) + " | " + printHelper(2,5) + " | " + printHelper(2,6) + " | " + printHelper(2,7) + " | "
                                    + printHelper(2,8) + " | " + printHelper(2,9) + " | " + printHelper(2,10) + " | " + printHelper(2,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("3  | " + printHelper(3,0) + " | " + printHelper(3,1) + " | " + printHelper(3,2) + " | " + printHelper(3,3) + " | " 
                                    + printHelper(3,4) + " | " + printHelper(3,5) + " | " + printHelper(3,6) + " | " + printHelper(3,7) + " | "
                                    + printHelper(3,8) + " | " + printHelper(3,9) + " | " + printHelper(3,10) + " | " + printHelper(3,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("4  | " + printHelper(4,0) + " | " + printHelper(4,1) + " | " + printHelper(4,2) + " | " + printHelper(4,3) + " | " 
                                    + printHelper(4,4) + " | " + printHelper(4,5) + " | " + printHelper(4,6) + " | " + printHelper(4,7) + " | "
                                    + printHelper(4,8) + " | " + printHelper(4,9) + " | " + printHelper(4,10) + " | " + printHelper(4,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("5  | " + printHelper(5,0) + " | " + printHelper(5,1) + " | " + printHelper(5,2) + " | " + printHelper(5,3) + " | " 
                                    + printHelper(5,4) + " | " + printHelper(5,5) + " | " + printHelper(5,6) + " | " + printHelper(5,7) + " | "
                                    + printHelper(5,8) + " | " + printHelper(5,9) + " | " + printHelper(5,10) + " | " + printHelper(5,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("6  | " + printHelper(6,0) + " | " + printHelper(6,1) + " | " + printHelper(6,2) + " | " + printHelper(6,3) + " | " 
                                    + printHelper(6,4) + " | " + printHelper(6,5) + " | " + printHelper(6,6) + " | " + printHelper(6,7) + " | "
                                    + printHelper(6,8) + " | " + printHelper(6,9) + " | " + printHelper(6,10) + " | " + printHelper(6,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("7  | " + printHelper(7,0) + " | " + printHelper(7,1) + " | " + printHelper(7,2) + " | " + printHelper(7,3) + " | " 
                                    + printHelper(7,4) + " | " + printHelper(7,5) + " | " + printHelper(7,6) + " | " + printHelper(7,7) + " | "
                                    + printHelper(7,8) + " | " + printHelper(7,9) + " | " + printHelper(7,10) + " | " + printHelper(7,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("8  | " + printHelper(8,0) + " | " + printHelper(8,1) + " | " + printHelper(8,2) + " | " + printHelper(8,3) + " | " 
                                    + printHelper(8,4) + " | " + printHelper(8,5) + " | " + printHelper(8,6) + " | " + printHelper(8,7) + " | "
                                    + printHelper(8,8) + " | " + printHelper(8,9) + " | " + printHelper(8,10) + " | " + printHelper(8,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("9  | " + printHelper(9,0) + " | " + printHelper(9,1) + " | " + printHelper(9,2) + " | " + printHelper(9,3) + " | " 
                                    + printHelper(9,4) + " | " + printHelper(9,5) + " | " + printHelper(9,6) + " | " + printHelper(9,7) + " | "
                                    + printHelper(9,8) + " | " + printHelper(9,9) + " | " + printHelper(9,10) + " | " + printHelper(9,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("10 | " + printHelper(10,0) + " | " + printHelper(10,1) + " | " + printHelper(10,2) + " | " + printHelper(10,3) + " | " 
                                    + printHelper(10,4) + " | " + printHelper(10,5) + " | " + printHelper(10,6) + " | " + printHelper(10,7) + " | "
                                    + printHelper(10,8) + " | " + printHelper(10,9) + " | " + printHelper(10,10) + " | " + printHelper(10,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("11 | " + printHelper(11,0) + " | " + printHelper(11,1) + " | " + printHelper(11,2) + " | " + printHelper(11,3) + " | " 
                                    + printHelper(11,4) + " | " + printHelper(11,5) + " | " + printHelper(11,6) + " | " + printHelper(11,7) + " | "
                                    + printHelper(11,8) + " | " + printHelper(11,9) + " | " + printHelper(11,10) + " | " + printHelper(11,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
        }
    }
}
