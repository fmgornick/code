public class Fib {

    public static int fibonacciRecursive(int n) {
        if (n <= 1) return n;
        else return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }

    public static int fibonacciIterative(int n) {
        int sum = 0;
        int x = 0;
        int y = 1;
        for (int i = 1; i < n; ++i) {
            sum = x + y;
            x = y;
            y = sum;
        }
        return sum;
    }

    public static void main(String[] args) {
        System.out.print(fibonacciRecursive(10));
    }

}
