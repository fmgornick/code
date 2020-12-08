// TextScan.java
// Opens text file supplied on the command line
// Usage:  java TextScan filename
// Counts all tokens found (a token is anything delimited by a space character)
// Displays each token found to the screen
// Code may be used in part for Project 5 with proper citing. 

import java.util.Scanner;
import java.io.*;

public class TextScan {

    public static String scan(String file) {

        Scanner readFile = null;
        String s = "";

        try {
            readFile = new Scanner(new File(file));
        }
        catch (FileNotFoundException e) {
            System.out.println("File: " + file + " not found");
            System.exit(1);  
        }

        while (readFile.hasNext()) {
            s += readFile.next();
            s += " ";
        }

        return s;
    }  // main

}  // TextScan
