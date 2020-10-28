// Fletcher Gornick, GORNI025

public class Cell {
    private int row;
    private int col;
    private char status;

    public Cell(int row, int col, char status) {
        this.row = row;
        this.col = col;
        this.status = status;
    }

    public char getStatus() {
        return status;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public void setStatus(char c) {
        status = c;
    }
}
