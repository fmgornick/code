// Name: Fletcher Gornick
// x500: gorni025

import java.util.Random;

public class MyMaze {
    Cell[][] maze;

    public MyMaze(int rows, int cols) {
        maze = new Cell[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                maze[i][j] = new Cell(i,j);
            }
        }
    }

    /* TODO: Create a new maze using the algorithm found in the writeup. */
    public static MyMaze makeMaze(int rows, int cols) {
        MyMaze m = new MyMaze(rows, cols);
        Stack1Gen<Cell> cellStack = new Stack1Gen<Cell>();
        cellStack.push(m.maze[0][0]);
        m.maze[0][0].setVisited(true);
        int r = 0;
        int c = 0;
        int direction;

        if (m.maze.length > 1 && m.maze[0].length > 1) {
            while(!cellStack.isEmpty()) {
                r = cellStack.top().getRow();
                c = cellStack.top().getCol();

                if (r == 0 && c == 0) {
                    if (m.maze[r+1][c].getVisited() == true && m.maze[r][c+1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 2);
                            if (direction == 0) {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }
                
                else if (r == 0 && c == m.maze[r].length-1) {
                    if (m.maze[r+1][c].getVisited() == true && m.maze[r][c-1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 2);
                            if (direction == 0) {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (r == m.maze.length-1 && c == 0) {
                    if (m.maze[r-1][c].getVisited() == true && m.maze[r][c+1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 2);
                            if (direction == 0) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (r == m.maze.length-1 && c == m.maze[r].length-1) {
                    if (m.maze[r-1][c].getVisited() == true && m.maze[r][c-1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 2);
                            if (direction == 0) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (r == 0) {
                    if (m.maze[r][c+1].getVisited() == true && m.maze[r+1][c].getVisited() == true && m.maze[r][c-1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 3);
                            if (direction == 0) {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 1) {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (c == 0) {
                    if (m.maze[r-1][c].getVisited() == true && m.maze[r][c+1].getVisited() == true && m.maze[r+1][c].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 3);
                            if (direction == 0) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 1) {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (r == m.maze.length-1) {
                    if (m.maze[r][c-1].getVisited() == true && m.maze[r-1][c].getVisited() == true && m.maze[r][c+1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 3);
                            if (direction == 0) {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 1) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else if (c == m.maze[r].length-1) {
                    if (m.maze[r-1][c].getVisited() == true && m.maze[r][c-1].getVisited() == true && m.maze[r+1][c].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 3);
                            if (direction == 0) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 1) {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }

                else {
                    if (m.maze[r-1][c].getVisited() == true && m.maze[r][c+1].getVisited() == true && m.maze[r+1][c].getVisited() == true && m.maze[r][c-1].getVisited() == true) {
                        cellStack.pop();
                    }
                    else {
                        while (true) {
                            direction = (int) Math.floor(Math.random() * 4);
                            if (direction == 0) {
                                if (m.maze[r-1][c].getVisited() == false) {
                                    m.maze[r-1][c].setBottom(false);
                                    m.maze[--r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 1) {
                                if (m.maze[r][c+1].getVisited() == false) {
                                    m.maze[r][c].setRight(false);
                                    m.maze[r][++c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else if (direction == 2) {
                                if (m.maze[r+1][c].getVisited() == false) {
                                    m.maze[r][c].setBottom(false);
                                    m.maze[++r][c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                            else {
                                if (m.maze[r][c-1].getVisited() == false) {
                                    m.maze[r][c-1].setRight(false);
                                    m.maze[r][--c].setVisited(true);
                                    cellStack.push(m.maze[r][c]);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        else if (m.maze.length == 1 || m.maze[0].length == 1) {
            if (m.maze.length == 1) {
                for (int i = 0; i < m.maze[0].length; i++) {
                    m.maze[0][i].setRight(false);
                }
            }

            if (m.maze[0].length == 1) {
                for (int i = 0; i < m.maze.length; i++) {
                    m.maze[i][0].setBottom(false);
                }
            }
        }


        for (int i = 0; i < m.maze.length; i++) {
            for (int j = 0; j < m.maze[i].length; j++) {
                m.maze[i][j].setVisited(false);
            }
        }

        m.maze[m.maze.length - 1][m.maze[0].length - 1].setRight(false);
        return m;
    }

    /* TODO: Print a representation of the maze to the terminal */
    public void printMaze() {
        String result = "";

        for (int i = 0; i <= maze.length * 2; i++) {
            for (int j = 0; j < maze[0].length; j++) {
                if (i == 0 || i == maze.length * 2) result += "+ - ";

                else if (i == 1) {
                    if (maze[i/2][j].getRight() == true) {
                        if (maze[i/2][j].getVisited() == true) result += " * |";
                        else result += "   |";
                    }
                    else {
                        if (maze[i/2][j].getVisited() == true) result += " *  ";
                        else result += "    ";
                    }
                }

                else {
                    if (i % 2 == 0) {
                        if (maze[i/2 - 1][j].getBottom() == true) result += "+ - ";
                        else result += "+   ";
                    }
                    else {
                        if (maze[i/2][j].getRight() == true) {
                            if (maze[i/2][j].getVisited() == true) result += " * |";
                            else result += "   |";
                        }
                        else {
                            if (maze[i/2][j].getVisited() == true) result +=  " *  ";
                            else result +=  "    ";
                        }
                    }
                }
            }

            if (i == 0 || i == maze.length * 2) result += "+\n ";

            else if (i == maze.length * 2 - 1) result += "    \n";

            else {
                if (i % 2 == 0) result += "+\n|";
                else result += "\n";
            }
        }

        System.out.println(result);
    }

    /* TODO: Solve the maze using the algorithm found in the writeup. */
    public void solveMaze() {
        Q1Gen<Cell> cellQ = new Q1Gen<Cell>();
        cellQ.add(maze[0][0]);
        maze[0][0].setVisited(true);
        Cell temp = null;
        int r = 0;
        int c = 0;
        int direction;

        if (maze.length > 1 && maze[0].length > 1) {
            while(!cellQ.isEmpty()) {
                temp = cellQ.remove();
                r = temp.getRow();
                c = temp.getCol();
                maze[r][c].setVisited(true);

                if (r == 0 && c == 0) {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                }
                
                else if (r == 0 && c == maze[r].length-1) {
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                    if (maze[r][c-1].getRight() == false && maze[r][c-1].getVisited() == false) cellQ.add(maze[r][c-1]);
                }

                else if (r == maze.length-1 && c == 0) {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r-1][c].getBottom() == false && maze[r-1][c].getVisited() == false) cellQ.add(maze[r-1][c]);
                }

                else if (r == maze.length-1 && c == maze[r].length-1) {
                    break;
                }

                else if (r == 0) {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                    if (maze[r][c-1].getRight() == false && maze[r][c-1].getVisited() == false) cellQ.add(maze[r][c-1]);
                }

                else if (c == 0) {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                    if (maze[r-1][c].getBottom() == false && maze[r-1][c].getVisited() == false) cellQ.add(maze[r-1][c]);
                }

                else if (r == maze.length-1) {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r][c-1].getRight() == false && maze[r][c-1].getVisited() == false) cellQ.add(maze[r][c-1]);
                    if (maze[r-1][c].getBottom() == false && maze[r-1][c].getVisited() == false) cellQ.add(maze[r-1][c]);

                }

                else if (c == maze[r].length-1) {
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                    if (maze[r][c-1].getRight() == false && maze[r][c-1].getVisited() == false) cellQ.add(maze[r][c-1]);
                    if (maze[r-1][c].getBottom() == false && maze[r-1][c].getVisited() == false) cellQ.add(maze[r-1][c]);
                }

                else {
                    if (maze[r][c].getRight() == false && maze[r][c+1].getVisited() == false) cellQ.add(maze[r][c+1]);
                    if (maze[r][c].getBottom() == false && maze[r+1][c].getVisited() == false) cellQ.add(maze[r+1][c]);
                    if (maze[r-1][c].getBottom() == false && maze[r-1][c].getVisited() == false) cellQ.add(maze[r-1][c]);
                    if (maze[r][c-1].getRight() == false && maze[r][c-1].getVisited() == false) cellQ.add(maze[r][c-1]);
                }
            }
        }

        else if (maze.length == 1 || maze[0].length == 1) {
            for (int i = 0; i < maze.length; i++) {
                for (int j = 0; j < maze[0].length; j++) {
                    maze[i][j].setVisited(true);
                }
            }
        }
    }

    public static void main(String[] args) {
        MyMaze newMaze = makeMaze(1,1);
        newMaze.printMaze();
        newMaze.solveMaze();
        System.out.println();
        newMaze.printMaze();
    }
}
