import java.util.Scanner;

public class Palindrome {
    public static void main(String args[]) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Type a word (all lowercase): ");

        String word = sc.nextLine();
        Boolean tf = true;

        for (int i = 0; i < word.length()/2; ++i) {
            if (word.charAt(i) != word.charAt(word.length() - i - 1)) {
                tf = false;
            }
        }

        if (tf) {
            System.out.println("this word is a palindrome");
        }

        else {
            System.out.println("this word is not a palindrome");
        }
    } 
}
