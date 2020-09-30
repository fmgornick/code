public class Histogram {
    public int lowerbound;
    public int upperbound;
    public int[] histogram;

    public Histogram(int lower, int upper) {
        this.lowerbound = lower;
        this.upperbound = upper;

        histogram = new int[upper - lower + 1];
        for (int i = 0; i < histogram.length; ++i)
            histogram[i] = 0;
    }

    public boolean add(int i) {
        if ((lowerbound <= i) && (i <= upperbound)) {
            histogram[i - lowerbound] += 1;
            return true;
        }

        else return false;
    }

    public String toString() {
        String histogramString = "";

        for (int i = 0; i < histogram.length; ++i) {
            histogramString += (lowerbound + i) + ": ";

            for (int j = 0; j < histogram[i]; ++j) {
                histogramString += "*";
            }

            histogramString += "\n";
        }


        return histogramString;
    }

    public static void main(String[] args) {
        Histogram a = new Histogram(2,5);
        a.add(2);
        a.add(2);
        a.add(2);
        a.add(3);
        a.add(3);
        a.add(5);
        a.add(5);
        a.add(5);
        System.out.print(a.toString());
    }
}
