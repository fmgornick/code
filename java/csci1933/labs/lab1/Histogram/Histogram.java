// a program that makes a sideways histogram of character occurances

// I did this program in C over the summer from the classic K&R book, so credit
// goes to that

import java.util.*;

public class Histogram {
    public static void main(String args[]) {

        int i, j;
        Scanner input = new Scanner(System.in);
        String sentence = input.nextLine();

        char[] sentenceArray = new char[sentence.length()];
        for (i = 0; i < sentence.length(); ++i) {
            sentenceArray[i] = sentence.charAt(i);
        }

        int characters[];
        characters = new int[128];
        for (i = 0; i < 128; ++i) {
            characters[i] = 0;
        }

        for (i = 0; i < sentenceArray.length; ++i) {
            ++characters[(int)sentenceArray[i]];
        }

        for (i = 0; i < characters.length; ++i) {
            if (characters[i] > 0) {
                System.out.println();
                System.out.print((char)i);
                System.out.print("| ");

                for (j = 0; j < characters[i]; ++j) {
                    System.out.print("*");
                }
            }
        }

    }
}
