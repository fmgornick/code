public class Max {
    public static int maxDigit = 0;

    public static int recursiveMaxDigit(int num) {
        if (num == 0) return maxDigit;

        else {
            if (num % 10 > maxDigit) maxDigit = num % 10;
            return recursiveMaxDigit(num / 10);
        }
    }

    public static int iterativeMaxDigit(int num) {
        while (num > 0) {
            if (num % 10 > maxDigit) maxDigit = num % 10;
            num /= 10;
        }

        return maxDigit;
    }

    public static void main(String[] args) {
        System.out.println(iterativeMaxDigit(10));
    }
}
