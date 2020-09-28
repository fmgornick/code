import java.util.Arrays;

public class ArraySum {
    public  int sum = 0;

    public  int arraySum(int[] array) {
        for (int i: array)
            sum += i;
        return sum;
    }
        
    public static void main(String[] args) {
        ArraySum s = new ArraySum();

        int[] myArray = {4,6,2,19,903,870,-2,10};
        System.out.println("array: " + Arrays.toString(myArray));

        System.out.println("sum: " + s.arraySum(myArray));
    }
}
