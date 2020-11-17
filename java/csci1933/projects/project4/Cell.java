/*
    A Maze is made up of Cells
 */
public class Cell {
    private boolean visited;    // whether the cell has been visited (true if visited, false if not visited)
    private boolean right;      // whether the cell has a right border (true if a right boundary, false if an open right)
    private boolean bottom;     // whether the cell has a bottom border (true if a bottom boundary, false if an open bottom)
    private int row;
    private int col;

    // All cells are initialized to full walls
    public Cell(){
        visited = false;
        right = true;
        bottom = true;
        row = 0;
        col = 0;
    }

    public Cell(int r, int c) {
        visited = false;
        right = true;
        bottom = true;
        row = r;
        col = c;
    }

    /**********
     * Setter functions
     **********/
    public void setVisited(boolean visited) { this.visited = visited; }
    public void setRight(boolean right) { this.right = right; }
    public void setBottom(boolean bottom) { this.bottom = bottom; }
    public void setRow(int row) { this.row = row; }
    public void setCol(int col) { this.col = col; }

    /**********
     * Getter functions
     **********/
    public boolean getVisited() { return visited; }
    public boolean getRight() { return right; }
    public boolean getBottom() { return bottom; }
    public int getRow() { return row; }
    public int getCol() { return col; }
}
