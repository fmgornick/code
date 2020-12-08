public class HashTable<T> {
    private NGen<T>[] table;

    public HashTable() {
        table = (NGen<T>[]) new NGen[107];
        for (int i = 0; i < 107; i++) table[i] = new NGen(null,null);
    }

    public HashTable(int n) {
        table = (NGen<T>[]) new NGen[n];
        for (int i = 0; i < n; i++) table[i] = new NGen(null,null);
    }

    public void display() {
        int count;
        int max = 0;
        float totalCollisions = 0;
        NGen<T> ptr;

        for (int i = 0; i < table.length; i++) {
            count = 0;
            System.out.print(i + ": ");
            ptr = table[i];

            while (ptr != null) count++;
            if (max < count) max = count;
            totalCollisions += count;

            System.out.println(count);
        }

        System.out.printf("average collision length: %.2f\n", totalCollisions / table.length);
        System.out.println("longest chain: " + max);

    }

    public void add()

    public static void main(String[] args) {
        System.out.println(TextScan.scan("keywords.txt"));
    }
}
