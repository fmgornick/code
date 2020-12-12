// Fletcher Gornick, GORNI025

// this is just to read for the enter key
import java.util.Scanner;

public class HashTable<T extends Comparable<T>> {
    private NGen<T>[] table;

    // default constructor, only really good for keywords.txt
    public HashTable() {
        table = (NGen<T>[]) new NGen[107];
        for (int i = 0; i < 107; i++) table[i] = new NGen("",null);
    }

    // I suggest inputing a number between 200 and 300, primes work best
    public HashTable(int n) {
        table = (NGen<T>[]) new NGen[n];
        for (int i = 0; i < n; i++) table[i] = new NGen("",null);
    }

    // displays the hash table as well as collision information
    public void display() {
        int count;
        int max = 0;
        float totalCollisions = 0;
        NGen<T> ptr;

        // index number: number of elements in the index
        for (int i = 0; i < table.length; i++) {
            count = 0;
            System.out.print(i + ": ");
            ptr = table[i];

            while (ptr.getData() != "") {
                count++;
                ptr = ptr.getNext();
            }

            if (max < count) max = count;
            totalCollisions += count;

            System.out.println(count);
        }

        // extra collision information
        System.out.printf("average collision length: %.2f\n", totalCollisions / table.length);
        System.out.println("longest chain: " + max);
    }

    // basic add function
    public void add(T item) {
        table[hash1(item)] = new NGen(item, table[hash1(item)]);
    }

    // depends on the hash function you want to use
    public void add(T item, int num) {
        table[hash(item, num)] = new NGen(item, table[hash(item,num)]);
    }

    // adds entire file to hash table
    public void addFile(String file) {
        String[] fileArray = TextScan.scan(file).split(" ");
        for (int i = 0; i < fileArray.length; i++) add((T) fileArray[i]);
    }

    // adds entire file based on which hash function you prefer
    public void addFile(String file, int num) {
        String[] fileArray = TextScan.scan(file).split(" ");
        for (int i = 0; i < fileArray.length; i++) add((T) fileArray[i], num);
    }

    // takes an input and runs the corresponding hash function
    private int hash(T key, int num) {
        switch (num) {
            case 1: return hash1(key);

            case 2: return hash2(key);

            case 3: return hash3(key);

            case 4: return hash4(key);

            default: return hash1(key);
        }
    }

    // this file works best on the keywords.txt file, but it's terrible on the
    // others
    private int hash1(T key) {
        int len = key.toString().length();
        if (len == 1) return key.toString().charAt(0) % table.length;
        return (key.toString().charAt(0) + key.toString().charAt(1)*7 + len) % table.length;
    }

    // this one's pretty good on all of the filess
    private int hash2(T key) {
        int len = key.toString().length();
        return (key.toString().charAt(0) + key.toString().charAt(len / 2)*3 + key.toString().charAt(len - 1)*5) % table.length;
    }

    // this one is also pretty good on them all
    private int hash3(T key) {
        int len = key.toString().length();
        if (len == 1) return key.toString().charAt(0) % table.length;
        else if (len == 2) return (key.toString().charAt(0) + key.toString().charAt(1)*3) % table.length;
        else return (key.toString().charAt(1) + key.toString().charAt(2)*26) % table.length;
    }

    // this one works especially good on bigger files
    // i got the idea to multiply by polynomial coefficients from this website
    // https://sunilsavanur.wordpress.com/2012/08/14/polynomial-hash-function-for-dictionary-words/
    private int hash4(T key) {
        int len = key.toString().length();
        String k = key.toString();

        return (121*k.charAt(0) + 1331*k.charAt(len/2) + 14641*k.charAt(len-1)) % table.length;
    }

    // main
    public static void main(String[] args) {
        System.out.println("Generic Hash Table for \"gettysburg.txt\"... (press enter to continue)");
        Scanner s = new Scanner(System.in);
        String line = s.nextLine();
        // hash table for gettysburg
        if (line != null) {
            HashTable<String> hg = new HashTable<>();
            hg.addFile("gettysburg.txt",4);
            hg.display();
        }

        System.out.println();
        System.out.println();

        System.out.println("Specific Hash Table for \"keywords.txt\"... (press enter to continue)");
        line = s.nextLine();

        // hash table for keywords
        // hash1, hash2, and hash4 are all good for this method
        if (line != null) {
            HashTable<String> hs = new HashTable<>();
            hs.addFile("keywords.txt",3);
            hs.display();
        }

        System.out.println();
        System.out.println();

        System.out.println("If you would like to see my less successful attempts");
        System.out.println("you can uncomment the rest of my code underneath this");
        System.out.println("print statement in my main function...");
        System.out.println();

        // they're not really that bad, but my hash4() function definitely
        // works the best on the gettysburg.txt file
        /*
        HashTable<String> hb1 = new HashTable<>();
        HashTable<String> hb2 = new HashTable<>();
        HashTable<String> hb3 = new HashTable<>();

        hb1.addFile("gettysburg.txt",1);
        hb2.addFile("gettysburg.txt",2);
        hb3.addFile("gettysburg.txt",3);

        hb1.display();
        System.out.println();
        hb2.display();
        System.out.println();
        hb2.display();
        System.out.println();
        */
    }
}
