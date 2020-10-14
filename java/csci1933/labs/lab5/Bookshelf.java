import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Bookshelf {
    public Book[] books;
    public int nextOpen = 0;

    public Bookshelf() {
        books = new Book[20];
    }

    public Bookshelf(int size) {
        books = new Book[size];
    }

    public boolean add(Book newBook) {
        if (nextOpen < books.length) {
            books[nextOpen] = newBook;
            nextOpen++;
            return true;
        }
        else return false;
    }

    public Bookshelf getBooksByAuthor(String author) {
        Bookshelf newBookShelf;
        int numOfBooks = 0;
        for (int i = 0; i < books.length; i++) {
            if (books[i].getAuthor().equals(author)) {
                numOfBooks++;
            }
        }
        newBookShelf = new Bookshelf(numOfBooks);

        for (int i = 0; i < books.length; i++) {
            if (books[i].getAuthor().equals(author)) {
                newBookShelf.add(books[i]);
            }
        }

        return newBookShelf;
    }

    public String toString() {
        String bookString = "";
        for (int i = 0; i < books.length && books[i] != null; i++) {
            bookString += books[i].toString() + "\n";
        }
        return bookString;
    }

    public void sort(char sortBy) {
        int i, j;
        Book temp;
        for (i = 1; i < books.length && books[i] != null; i++) {
            temp = books[i];
            for (j = i - 1; j >= 0 && books[j] != null && temp.compareTo(books[j], sortBy) < 0; j--) {
                books[j+1] = books[j];
            }
            books[j+1] = temp;
        }
    }

    public static Bookshelf readBooksFromFile(String fileName) throws FileNotFoundException {

        File f = new File(fileName);
        Scanner s = new Scanner(f);

        Bookshelf fileBookShelf;
        int count = 0;
        while (s.hasNextLine()) {
            count++;
            s.nextLine();
        }

        fileBookShelf = new Bookshelf(count);
        s = new Scanner(f);

        for (int i = 0; i < fileBookShelf.books.length; i++) {
            String[] b = s.nextLine().split(", ");
            
            fileBookShelf.books[i] = new Book(b[0], b[1], Double.parseDouble(b[2]));
        }

        return fileBookShelf;
    }

    public static void writeShelfToFile (Bookshelf b, String fileName) throws FileNotFoundException {
        PrintWriter p = new PrintWriter(new File(fileName));
        p.print(b.toString());
        p.close();
    }

    public static void main(String[] args) throws FileNotFoundException {
        Book a = new Book("hasdfkl", "asdkfh", 10);
        Book b = new Book("sajdbfkv", "pasd", 9);
        Book c = new Book("ndksks", "cadjhf", 8);
        Book d = new Book("qdjfhh", "kdshf", 7);
        Book e = new Book("bskljd", "emfh", 6);
        Book f = new Book("lpllsdf", "sjkdf", 5);
        Book g = new Book("nvmasdmf", "fmdj", 4);
        Book h = new Book("ldshfhk", "xkjhasdf", 3);
        Book i = new Book("wjfnids", "bnhdh", 2);
        Book j = new Book("hjfnids", "gnhdh", 1);

        Bookshelf fletch = new Bookshelf();

        fletch.add(a);
        fletch.add(b);
        fletch.add(c);
        fletch.add(d);
        fletch.add(e);
        fletch.add(f);
        fletch.add(g);
        fletch.add(h);
        fletch.add(i);
        fletch.add(j);

        fletch.sort('a');

//        System.out.println(fletch.toString());
//        System.out.println(fletch.readBooksFromFile("bookinput.txt").toString());
//        fletch.writeShelfToFile(fletch, "output.txt");

        Bookshelf bookInputShelf = fletch.readBooksFromFile("bookinput.txt");
        bookInputShelf.sort('r');
        fletch.writeShelfToFile(bookInputShelf, "output.txt");
    }
}
