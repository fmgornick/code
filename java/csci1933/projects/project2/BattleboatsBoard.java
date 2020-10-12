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

    public BattleboatsBoard(int standardOrExpert) {
        se = standardOrExpert;
    }

    public void placeBoats() {
        if (se == 1) {
            int remainingBoats = 5;

            board = new Cell[8][8];
            for (int i = 0; i < board.length; i++) {
                for (int j = 0; j < board[i].length; j++) {
                    board[i][j] = new Cell(i,j,'-');
                }
            }

            while (remainingBoats > 0) {
                if (remainingBoats == 5) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 4);
                        int randCol = (int) Math.floor(Math.random() * 8);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-'
                               && board[randRow + 3][randCol].status == '-' && board[randRow + 4][randCol].status == '-') {
                            for (int i = 0; i < 5; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat1[i] = new Cell(randRow, randCol, 'B');
                                randRow++;
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 8);
                        int randCol = (int) Math.floor(Math.random() * 4);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-'
                               && board[randRow][randCol + 3].status == '-' && board[randRow][randCol + 4].status == '-') {
                            for (int i = 0; i < 5; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat1[i] = new Cell(randRow, randCol, 'B');
                                randCol++;
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 4) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 5);
                        int randCol = (int) Math.floor(Math.random() * 8);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-'
                               && board[randRow + 3][randCol].status == '-') {
                            for (int i = 0; i < 4; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat3[i] = new Cell(randRow, randCol, 'B');
                                randRow++;
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 8);
                        int randCol = (int) Math.floor(Math.random() * 5);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-'
                               && board[randRow][randCol + 3].status == '-') {
                            for (int i = 0; i < 4; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat3[i] = new Cell(randRow, randCol, 'B');
                                randCol++;
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 2 || remainingBoats == 3) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 6);
                        int randCol = (int) Math.floor(Math.random() * 8);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-') {
                            for (int i = 0; i < 3; i++) {
                                board[randRow][randCol].setStatus('B');
                                if (remainingBoats == 3) {
                                    boat5[i] = new Cell(randRow, randCol, 'B');
                                }
                                else boat7[i] = new Cell(randRow, randCol, 'B');
                                randRow++;

                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 8);
                        int randCol = (int) Math.floor(Math.random() * 6);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-') {
                            for (int i = 0; i < 3; i++) {
                                board[randRow][randCol].setStatus('B');
                                if (remainingBoats == 3) {
                                    boat5[i] = new Cell(randRow, randCol, 'B');
                                }
                                else boat7[i] = new Cell(randRow, randCol, 'B');
                                randCol++;
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 1) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 7);
                        int randCol = (int) Math.floor(Math.random() * 8);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-') {
                            for (int i = 0; i < 2; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat9[i] = new Cell(randRow, randCol, 'B');
                                randRow++;
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 8);
                        int randCol = (int) Math.floor(Math.random() * 7);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-') {
                            for (int i = 0; i < 2; i++) {
                                board[randRow][randCol].setStatus('B');
                                boat9[i] = new Cell(randRow, randCol, 'B');
                                randCol++;
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
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

            while (remainingBoats > 0) {
                if (remainingBoats == 10 || remainingBoats == 9) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 8);
                        int randCol = (int) Math.floor(Math.random() * 12);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-'
                               && board[randRow + 3][randCol].status == '-' && board[randRow + 4][randCol].status == '-') {
                            for (int i = 0; i < 5; i++) {
                                if (remainingBoats == 10) {
                                    board[randRow][randCol].setStatus('B');
                                    boat1[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat2[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 12);
                        int randCol = (int) Math.floor(Math.random() * 8);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-'
                               && board[randRow][randCol + 3].status == '-' && board[randRow][randCol + 4].status == '-') {
                            for (int i = 0; i < 5; i++) {
                                if (remainingBoats == 10) {
                                    board[randRow][randCol].setStatus('B');
                                    boat1[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat2[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 8 || remainingBoats == 7) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 9);
                        int randCol = (int) Math.floor(Math.random() * 12);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-'
                               && board[randRow + 3][randCol].status == '-') {
                            for (int i = 0; i < 4; i++) {
                                if (remainingBoats == 8) {
                                    board[randRow][randCol].setStatus('B');
                                    boat3[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat4[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 12);
                        int randCol = (int) Math.floor(Math.random() * 9);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-'
                               && board[randRow][randCol + 3].status == '-') {
                            for (int i = 0; i < 4; i++) {
                                if (remainingBoats == 8) {
                                    board[randRow][randCol].setStatus('B');
                                    boat3[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat4[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 6 || remainingBoats == 5 || remainingBoats == 4 || remainingBoats == 3) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 10);
                        int randCol = (int) Math.floor(Math.random() * 12);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-' && board[randRow + 2][randCol].status == '-') {
                            for (int i = 0; i < 3; i++) {
                                if (remainingBoats == 6) {
                                    board[randRow][randCol].setStatus('B');
                                    boat5[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else if (remainingBoats == 5) {
                                    board[randRow][randCol].setStatus('B');
                                    boat6[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else if (remainingBoats == 4) {
                                    board[randRow][randCol].setStatus('B');
                                    boat7[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat8[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 12);
                        int randCol = (int) Math.floor(Math.random() * 10);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-' && board[randRow][randCol + 2].status == '-') {
                            for (int i = 0; i < 3; i++) {
                                if (remainingBoats == 6) {
                                    board[randRow][randCol].setStatus('B');
                                    boat5[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else if (remainingBoats == 5) {
                                    board[randRow][randCol].setStatus('B');
                                    boat6[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else if (remainingBoats == 4) {
                                    board[randRow][randCol].setStatus('B');
                                    boat7[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat8[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }

                else if (remainingBoats == 2 || remainingBoats == 1) {
                    int vh = (int) Math.floor(Math.random() * 2);
                    if (vh == 0) {
                        int randRow = (int) Math.floor(Math.random() * 11);
                        int randCol = (int) Math.floor(Math.random() * 12);

                        if (board[randRow][randCol].status == '-' && board[randRow + 1][randCol].status == '-') {
                            for (int i = 0; i < 2; i++) {
                                if (remainingBoats == 2) {
                                    board[randRow][randCol].setStatus('B');
                                    boat9[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat10[i] = new Cell(randRow, randCol, 'B');
                                    randRow++;
                                }
                            }
                        }
                        else remainingBoats++;
                    }
                    else {
                        int randRow = (int) Math.floor(Math.random() * 12);
                        int randCol = (int) Math.floor(Math.random() * 11);

                        if (board[randRow][randCol].status == '-' && board[randRow][randCol + 1].status == '-') {
                            for (int i = 0; i < 2; i++) {
                                if (remainingBoats == 2) {
                                    board[randRow][randCol].setStatus('B');
                                    boat9[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                                else {
                                    board[randRow][randCol].setStatus('B');
                                    boat10[i] = new Cell(randRow, randCol, 'B');
                                    randCol++;
                                }
                            }
                        }
                        else remainingBoats++;

                    }

                    remainingBoats--;
                }
            }
        }
    }

    public int fire(int x, int y) {
        if (board[x][y].status == '-') {
            board[x][y].setStatus('M');
            return 0;
        }
        else if (board[x][y].status == 'B') {
            board[x][y].setStatus('H');
            return 0;
        }

        else return 1;
    }

    public void missile(int r, int c) {
        if (r > 0 && r < board.length - 1 && c > 0 && c < board[r].length - 1) {
            fire(r-1, c-1);
            fire(r-1, c);
            fire(r-1, c+1);
            fire(r, c-1);
            fire(r, c);
            fire(r, c+1);
            fire(r+1, c-1);
            fire(r+1, c);
            fire(r+1, c+1);
        }

        else if (r > 0 && r < board.length - 1 && c == 0 && c < board[r].length - 1) {
            fire(r-1, c);
            fire(r-1, c+1);
            fire(r, c);
            fire(r, c+1);
            fire(r+1, c);
            fire(r+1, c+1);
        }

        else if (r > 0 && r < board.length - 1 && c > 0 && c == board[r].length - 1) {
            fire(r-1, c-1);
            fire(r-1, c);
            fire(r, c-1);
            fire(r, c);
            fire(r+1, c-1);
            fire(r+1, c);
        }

        else if (r == 0 && r < board.length - 1 && c > 0 && c < board[r].length - 1) {
            fire(r, c-1);
            fire(r, c);
            fire(r, c+1);
            fire(r+1, c-1);
            fire(r+1, c);
            fire(r+1, c+1);
        }

        else if (r == 0 && r < board.length - 1 && c == 0 && c < board[r].length - 1) {
            fire(r, c);
            fire(r, c+1);
            fire(r+1, c);
            fire(r+1, c+1);
        }

        else if (r == 0 && r < board.length - 1 && c > 0 && c == board[r].length - 1) {
            fire(r, c-1);
            fire(r, c);
            fire(r+1, c-1);
            fire(r+1, c);
        }

        else if (r > 0 && r == board.length - 1 && c > 0 && c < board[r].length - 1) {
            fire(r-1, c-1);
            fire(r-1, c);
            fire(r-1, c+1);
            fire(r, c-1);
            fire(r, c);
            fire(r, c+1);
        }

        else if (r > 0 && r == board.length - 1 && c == 0 && c < board[r].length - 1) {
            fire(r-1, c);
            fire(r-1, c+1);
            fire(r, c);
            fire(r, c+1);
        }

        else {
            fire(r-1, c-1);
            fire(r-1, c);
            fire(r, c-1);
            fire(r, c);
        }
    }

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

    public String displayhelper(int r, int c) {
        if (board[r][c].status == 'H') {
            return "X";
        }
        else if (board[r][c].status == 'M') {
            return "O";
        }
        else return " ";

    }

    public void display() {
        if (se == 1) {
            System.out.println();
            System.out.println("    0   1   2   3   4   5   6   7  ");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("0 | " + displayhelper(0,0) + " | " + displayhelper(0,1) + " | " + displayhelper(0,2) + " | " + displayhelper(0,3) + " | " 
                                    + displayhelper(0,4) + " | " + displayhelper(0,5) + " | " + displayhelper(0,6) + " | " + displayhelper(0,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("1 | " + displayhelper(1,0) + " | " + displayhelper(1,1) + " | " + displayhelper(1,2) + " | " + displayhelper(1,3) + " | " 
                                    + displayhelper(1,4) + " | " + displayhelper(1,5) + " | " + displayhelper(1,6) + " | " + displayhelper(1,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("2 | " + displayhelper(2,0) + " | " + displayhelper(2,1) + " | " + displayhelper(2,2) + " | " + displayhelper(2,3) + " | " 
                                    + displayhelper(2,4) + " | " + displayhelper(2,5) + " | " + displayhelper(2,6) + " | " + displayhelper(2,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("3 | " + displayhelper(3,0) + " | " + displayhelper(3,1) + " | " + displayhelper(3,2) + " | " + displayhelper(3,3) + " | " 
                                    + displayhelper(3,4) + " | " + displayhelper(3,5) + " | " + displayhelper(3,6) + " | " + displayhelper(3,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("4 | " + displayhelper(4,0) + " | " + displayhelper(4,1) + " | " + displayhelper(4,2) + " | " + displayhelper(4,3) + " | " 
                                    + displayhelper(4,4) + " | " + displayhelper(4,5) + " | " + displayhelper(4,6) + " | " + displayhelper(4,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("5 | " + displayhelper(5,0) + " | " + displayhelper(5,1) + " | " + displayhelper(5,2) + " | " + displayhelper(5,3) + " | " 
                                    + displayhelper(5,4) + " | " + displayhelper(5,5) + " | " + displayhelper(5,6) + " | " + displayhelper(5,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("6 | " + displayhelper(6,0) + " | " + displayhelper(6,1) + " | " + displayhelper(6,2) + " | " + displayhelper(6,3) + " | " 
                                    + displayhelper(6,4) + " | " + displayhelper(6,5) + " | " + displayhelper(6,6) + " | " + displayhelper(6,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("7 | " + displayhelper(7,0) + " | " + displayhelper(7,1) + " | " + displayhelper(7,2) + " | " + displayhelper(7,3) + " | " 
                                    + displayhelper(7,4) + " | " + displayhelper(7,5) + " | " + displayhelper(7,6) + " | " + displayhelper(7,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
        }

        else {
            System.out.println();
            System.out.println("     0   1   2   3   4   5   6   7   8   9   10  11 ");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("0  | " + displayhelper(0,0) + " | " + displayhelper(0,1) + " | " + displayhelper(0,2) + " | " + displayhelper(0,3) + " | " 
                                    + displayhelper(0,4) + " | " + displayhelper(0,5) + " | " + displayhelper(0,6) + " | " + displayhelper(0,7) + " | "
                                    + displayhelper(0,8) + " | " + displayhelper(0,9) + " | " + displayhelper(0,10) + " | " + displayhelper(0,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("1  | " + displayhelper(1,0) + " | " + displayhelper(1,1) + " | " + displayhelper(1,2) + " | " + displayhelper(1,3) + " | " 
                                    + displayhelper(1,4) + " | " + displayhelper(1,5) + " | " + displayhelper(1,6) + " | " + displayhelper(1,7) + " | "
                                    + displayhelper(1,8) + " | " + displayhelper(1,9) + " | " + displayhelper(1,10) + " | " + displayhelper(1,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("2  | " + displayhelper(2,0) + " | " + displayhelper(2,1) + " | " + displayhelper(2,2) + " | " + displayhelper(2,3) + " | " 
                                    + displayhelper(2,4) + " | " + displayhelper(2,5) + " | " + displayhelper(2,6) + " | " + displayhelper(2,7) + " | "
                                    + displayhelper(2,8) + " | " + displayhelper(2,9) + " | " + displayhelper(2,10) + " | " + displayhelper(2,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("3  | " + displayhelper(3,0) + " | " + displayhelper(3,1) + " | " + displayhelper(3,2) + " | " + displayhelper(3,3) + " | " 
                                    + displayhelper(3,4) + " | " + displayhelper(3,5) + " | " + displayhelper(3,6) + " | " + displayhelper(3,7) + " | "
                                    + displayhelper(3,8) + " | " + displayhelper(3,9) + " | " + displayhelper(3,10) + " | " + displayhelper(3,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("4  | " + displayhelper(4,0) + " | " + displayhelper(4,1) + " | " + displayhelper(4,2) + " | " + displayhelper(4,3) + " | " 
                                    + displayhelper(4,4) + " | " + displayhelper(4,5) + " | " + displayhelper(4,6) + " | " + displayhelper(4,7) + " | "
                                    + displayhelper(4,8) + " | " + displayhelper(4,9) + " | " + displayhelper(4,10) + " | " + displayhelper(4,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("5  | " + displayhelper(5,0) + " | " + displayhelper(5,1) + " | " + displayhelper(5,2) + " | " + displayhelper(5,3) + " | " 
                                    + displayhelper(5,4) + " | " + displayhelper(5,5) + " | " + displayhelper(5,6) + " | " + displayhelper(5,7) + " | "
                                    + displayhelper(5,8) + " | " + displayhelper(5,9) + " | " + displayhelper(5,10) + " | " + displayhelper(5,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("6  | " + displayhelper(6,0) + " | " + displayhelper(6,1) + " | " + displayhelper(6,2) + " | " + displayhelper(6,3) + " | " 
                                    + displayhelper(6,4) + " | " + displayhelper(6,5) + " | " + displayhelper(6,6) + " | " + displayhelper(6,7) + " | "
                                    + displayhelper(6,8) + " | " + displayhelper(6,9) + " | " + displayhelper(6,10) + " | " + displayhelper(6,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("7  | " + displayhelper(7,0) + " | " + displayhelper(7,1) + " | " + displayhelper(7,2) + " | " + displayhelper(7,3) + " | " 
                                    + displayhelper(7,4) + " | " + displayhelper(7,5) + " | " + displayhelper(7,6) + " | " + displayhelper(7,7) + " | "
                                    + displayhelper(7,8) + " | " + displayhelper(7,9) + " | " + displayhelper(7,10) + " | " + displayhelper(7,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("8  | " + displayhelper(8,0) + " | " + displayhelper(8,1) + " | " + displayhelper(8,2) + " | " + displayhelper(8,3) + " | " 
                                    + displayhelper(8,4) + " | " + displayhelper(8,5) + " | " + displayhelper(8,6) + " | " + displayhelper(8,7) + " | "
                                    + displayhelper(8,8) + " | " + displayhelper(8,9) + " | " + displayhelper(8,10) + " | " + displayhelper(8,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("9  | " + displayhelper(9,0) + " | " + displayhelper(9,1) + " | " + displayhelper(9,2) + " | " + displayhelper(9,3) + " | " 
                                    + displayhelper(9,4) + " | " + displayhelper(9,5) + " | " + displayhelper(9,6) + " | " + displayhelper(9,7) + " | "
                                    + displayhelper(9,8) + " | " + displayhelper(9,9) + " | " + displayhelper(9,10) + " | " + displayhelper(9,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("10 | " + displayhelper(10,0) + " | " + displayhelper(10,1) + " | " + displayhelper(10,2) + " | " + displayhelper(10,3) + " | " 
                                    + displayhelper(10,4) + " | " + displayhelper(10,5) + " | " + displayhelper(10,6) + " | " + displayhelper(10,7) + " | "
                                    + displayhelper(10,8) + " | " + displayhelper(10,9) + " | " + displayhelper(10,10) + " | " + displayhelper(10,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("11 | " + displayhelper(11,0) + " | " + displayhelper(11,1) + " | " + displayhelper(11,2) + " | " + displayhelper(11,3) + " | " 
                                    + displayhelper(11,4) + " | " + displayhelper(11,5) + " | " + displayhelper(11,6) + " | " + displayhelper(11,7) + " | "
                                    + displayhelper(11,8) + " | " + displayhelper(11,9) + " | " + displayhelper(11,10) + " | " + displayhelper(11,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
        }
    }

    public String printhelper(int r, int c) {
        if (se == 1) {
            for (int i = 0; i < boat1.length; i++) {
                if (boat1[i].row == r && boat1[i].col == c) return "A";
            }
            for (int i = 0; i < boat3.length; i++) {
                if (boat3[i].row == r && boat3[i].col == c) return "B";
            }
            for (int i = 0; i < boat5.length; i++) {
                if (boat5[i].row == r && boat5[i].col == c) return "C";
            }
            for (int i = 0; i < boat7.length; i++) {
                if (boat7[i].row == r && boat7[i].col == c) return "D";
            }
            for (int i = 0; i < boat9.length; i++) {
                if (boat9[i].row == r && boat9[i].col == c) return "E";
            }
            return " ";
        }

        else {
            for (int i = 0; i < boat1.length; i++) {
                if (boat1[i].row == r && boat1[i].col == c) return "A";
            }
            for (int i = 0; i < boat2.length; i++) {
                if (boat2[i].row == r && boat2[i].col == c) return "B";
            }
            for (int i = 0; i < boat3.length; i++) {
                if (boat3[i].row == r && boat3[i].col == c) return "C";
            }
            for (int i = 0; i < boat4.length; i++) {
                if (boat4[i].row == r && boat4[i].col == c) return "D";
            }
            for (int i = 0; i < boat5.length; i++) {
                if (boat5[i].row == r && boat5[i].col == c) return "E";
            }
            for (int i = 0; i < boat6.length; i++) {
                if (boat6[i].row == r && boat6[i].col == c) return "F";
            }
            for (int i = 0; i < boat7.length; i++) {
                if (boat7[i].row == r && boat7[i].col == c) return "G";
            }
            for (int i = 0; i < boat8.length; i++) {
                if (boat8[i].row == r && boat8[i].col == c) return "H";
            }
            for (int i = 0; i < boat9.length; i++) {
                if (boat9[i].row == r && boat9[i].col == c) return "I";
            }
            for (int i = 0; i < boat10.length; i++) {
                if (boat10[i].row == r && boat10[i].col == c) return "J";
            }
            return " ";
        }
    }

    public void print() {
        if (se == 1) {
            System.out.println();
            System.out.println("    0   1   2   3   4   5   6   7  ");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("0 | " + printhelper(0,0) + " | " + printhelper(0,1) + " | " + printhelper(0,2) + " | " + printhelper(0,3) + " | " 
                                    + printhelper(0,4) + " | " + printhelper(0,5) + " | " + printhelper(0,6) + " | " + printhelper(0,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("1 | " + printhelper(1,0) + " | " + printhelper(1,1) + " | " + printhelper(1,2) + " | " + printhelper(1,3) + " | " 
                                    + printhelper(1,4) + " | " + printhelper(1,5) + " | " + printhelper(1,6) + " | " + printhelper(1,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("2 | " + printhelper(2,0) + " | " + printhelper(2,1) + " | " + printhelper(2,2) + " | " + printhelper(2,3) + " | " 
                                    + printhelper(2,4) + " | " + printhelper(2,5) + " | " + printhelper(2,6) + " | " + printhelper(2,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("3 | " + printhelper(3,0) + " | " + printhelper(3,1) + " | " + printhelper(3,2) + " | " + printhelper(3,3) + " | " 
                                    + printhelper(3,4) + " | " + printhelper(3,5) + " | " + printhelper(3,6) + " | " + printhelper(3,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("4 | " + printhelper(4,0) + " | " + printhelper(4,1) + " | " + printhelper(4,2) + " | " + printhelper(4,3) + " | " 
                                    + printhelper(4,4) + " | " + printhelper(4,5) + " | " + printhelper(4,6) + " | " + printhelper(4,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("5 | " + printhelper(5,0) + " | " + printhelper(5,1) + " | " + printhelper(5,2) + " | " + printhelper(5,3) + " | " 
                                    + printhelper(5,4) + " | " + printhelper(5,5) + " | " + printhelper(5,6) + " | " + printhelper(5,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("6 | " + printhelper(6,0) + " | " + printhelper(6,1) + " | " + printhelper(6,2) + " | " + printhelper(6,3) + " | " 
                                    + printhelper(6,4) + " | " + printhelper(6,5) + " | " + printhelper(6,6) + " | " + printhelper(6,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
            System.out.println("7 | " + printhelper(7,0) + " | " + printhelper(7,1) + " | " + printhelper(7,2) + " | " + printhelper(7,3) + " | " 
                                    + printhelper(7,4) + " | " + printhelper(7,5) + " | " + printhelper(7,6) + " | " + printhelper(7,7) + " |");
            System.out.println("  + - + - + - + - + - + - + - + - +");
        }

        else {
            System.out.println();
            System.out.println("     0   1   2   3   4   5   6   7   8   9   10  11 ");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("0  | " + printhelper(0,0) + " | " + printhelper(0,1) + " | " + printhelper(0,2) + " | " + printhelper(0,3) + " | " 
                                    + printhelper(0,4) + " | " + printhelper(0,5) + " | " + printhelper(0,6) + " | " + printhelper(0,7) + " | "
                                    + printhelper(0,8) + " | " + printhelper(0,9) + " | " + printhelper(0,10) + " | " + printhelper(0,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("1  | " + printhelper(1,0) + " | " + printhelper(1,1) + " | " + printhelper(1,2) + " | " + printhelper(1,3) + " | " 
                                    + printhelper(1,4) + " | " + printhelper(1,5) + " | " + printhelper(1,6) + " | " + printhelper(1,7) + " | "
                                    + printhelper(1,8) + " | " + printhelper(1,9) + " | " + printhelper(1,10) + " | " + printhelper(1,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("2  | " + printhelper(2,0) + " | " + printhelper(2,1) + " | " + printhelper(2,2) + " | " + printhelper(2,3) + " | " 
                                    + printhelper(2,4) + " | " + printhelper(2,5) + " | " + printhelper(2,6) + " | " + printhelper(2,7) + " | "
                                    + printhelper(2,8) + " | " + printhelper(2,9) + " | " + printhelper(2,10) + " | " + printhelper(2,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("3  | " + printhelper(3,0) + " | " + printhelper(3,1) + " | " + printhelper(3,2) + " | " + printhelper(3,3) + " | " 
                                    + printhelper(3,4) + " | " + printhelper(3,5) + " | " + printhelper(3,6) + " | " + printhelper(3,7) + " | "
                                    + printhelper(3,8) + " | " + printhelper(3,9) + " | " + printhelper(3,10) + " | " + printhelper(3,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("4  | " + printhelper(4,0) + " | " + printhelper(4,1) + " | " + printhelper(4,2) + " | " + printhelper(4,3) + " | " 
                                    + printhelper(4,4) + " | " + printhelper(4,5) + " | " + printhelper(4,6) + " | " + printhelper(4,7) + " | "
                                    + printhelper(4,8) + " | " + printhelper(4,9) + " | " + printhelper(4,10) + " | " + printhelper(4,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("5  | " + printhelper(5,0) + " | " + printhelper(5,1) + " | " + printhelper(5,2) + " | " + printhelper(5,3) + " | " 
                                    + printhelper(5,4) + " | " + printhelper(5,5) + " | " + printhelper(5,6) + " | " + printhelper(5,7) + " | "
                                    + printhelper(5,8) + " | " + printhelper(5,9) + " | " + printhelper(5,10) + " | " + printhelper(5,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("6  | " + printhelper(6,0) + " | " + printhelper(6,1) + " | " + printhelper(6,2) + " | " + printhelper(6,3) + " | " 
                                    + printhelper(6,4) + " | " + printhelper(6,5) + " | " + printhelper(6,6) + " | " + printhelper(6,7) + " | "
                                    + printhelper(6,8) + " | " + printhelper(6,9) + " | " + printhelper(6,10) + " | " + printhelper(6,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("7  | " + printhelper(7,0) + " | " + printhelper(7,1) + " | " + printhelper(7,2) + " | " + printhelper(7,3) + " | " 
                                    + printhelper(7,4) + " | " + printhelper(7,5) + " | " + printhelper(7,6) + " | " + printhelper(7,7) + " | "
                                    + printhelper(7,8) + " | " + printhelper(7,9) + " | " + printhelper(7,10) + " | " + printhelper(7,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("8  | " + printhelper(8,0) + " | " + printhelper(8,1) + " | " + printhelper(8,2) + " | " + printhelper(8,3) + " | " 
                                    + printhelper(8,4) + " | " + printhelper(8,5) + " | " + printhelper(8,6) + " | " + printhelper(8,7) + " | "
                                    + printhelper(8,8) + " | " + printhelper(8,9) + " | " + printhelper(8,10) + " | " + printhelper(8,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("9  | " + printhelper(9,0) + " | " + printhelper(9,1) + " | " + printhelper(9,2) + " | " + printhelper(9,3) + " | " 
                                    + printhelper(9,4) + " | " + printhelper(9,5) + " | " + printhelper(9,6) + " | " + printhelper(9,7) + " | "
                                    + printhelper(9,8) + " | " + printhelper(9,9) + " | " + printhelper(9,10) + " | " + printhelper(9,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("10 | " + printhelper(10,0) + " | " + printhelper(10,1) + " | " + printhelper(10,2) + " | " + printhelper(10,3) + " | " 
                                    + printhelper(10,4) + " | " + printhelper(10,5) + " | " + printhelper(10,6) + " | " + printhelper(10,7) + " | "
                                    + printhelper(10,8) + " | " + printhelper(10,9) + " | " + printhelper(10,10) + " | " + printhelper(10,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
            System.out.println("11 | " + printhelper(11,0) + " | " + printhelper(11,1) + " | " + printhelper(11,2) + " | " + printhelper(11,3) + " | " 
                                    + printhelper(11,4) + " | " + printhelper(11,5) + " | " + printhelper(11,6) + " | " + printhelper(11,7) + " | "
                                    + printhelper(11,8) + " | " + printhelper(11,9) + " | " + printhelper(11,10) + " | " + printhelper(11,11) + " |");
            System.out.println("   + - + - + - + - + - + - + - + - + - + - + - + - +");
        }
    }
