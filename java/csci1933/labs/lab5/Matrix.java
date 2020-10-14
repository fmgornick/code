public class Matrix {
    private int rows;
    private int columns;
    private int[][] matrix;

    public Matrix(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;
        this.matrix = new int[rows][columns];
    }

    public Matrix(int[][] arr) {
        this.rows = arr.length;
        this.columns = arr[0].length;
        this.matrix = new int[rows][columns];
    }

    public Matrix transpose() {
        Matrix newMatrix = new Matrix(columns, rows);
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                newMatrix.matrix[j][i] = matrix[i][j];
            }
        }
        return newMatrix;
    }

    public String toString() {
        String s = "";
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                s += matrix[i][j] + " ";
            }
            s += "\n";
        }
        return s;
    }


    public static void main(String[] args) {
        Matrix n = new Matrix(3,3);
        int num = 1;
        for (int i = 0; i < n.matrix.length; i++) {
            for (int j = 0; j < n.matrix[i].length; j++) {
                n.matrix[i][j] = num;
                num++;
            }
        }
        System.out.print(n.toString());
        System.out.println();
        System.out.print(n.transpose().toString());
    }
}
