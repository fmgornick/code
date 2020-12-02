// TextScan.java
// Opens text file supplied on the command line
// Usage:  java TextScan filename
// Counts all tokens found (a token is anything delimited by a space character)
// Displays each token found to the screen
// Code may be used in part for Project 5 with proper citing. 

import java.util.Scanner;
import java.io.*;

public class TextScan {

    public static void main(String[] args) {

        Scanner readFile = null;
        String s;
        int count = 0;

        System.out.println();
        System.out.println("Attempting to read from file: " + args[0]);
        try {
            readFile = new Scanner(new File(args[0]));
        }
        catch (FileNotFoundException e) {
            System.out.println("File: " + args[0] + " not found");
            System.exit(1);  
        }

        System.out.println("Connection to file: " + args[0] + " successful");
        System.out.println();
        while (readFile.hasNext()) {
            s = readFile.next();
            System.out.println("Token found: " + s);
            count++;
        }
        
        System.out.println();
        System.out.println(count + " Tokens found");
        System.out.println();

    }  // main

}  // TextScan
