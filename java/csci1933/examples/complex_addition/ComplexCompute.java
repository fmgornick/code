public class ComplexCompute {
    public static void main(String args[]) {

        double realParta = 9.1;
        double imagParta = 2.1;
        double realPartb = 4.1;
        double imagPartb = 7.3;

        double realPartResult = realParta + realPartb;
        double imagPartResult = imagParta + imagPartb;

        System.out.printf("(%.1f + %.1fi) + (%.1f + %.1fi) = %.1f + %.1fi", realParta, imagParta, realPartb, imagPartb, realPartResult, imagPartResult);

    }
}
