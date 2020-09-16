// H3.java
// A more advanced Hello World Java program
// A better Hello World based initially on an example from the Apple Java site
// Uses Scanner class for input, command line input, and mix of Java and C IO.
// Revised January 2019


// This is a simple Java program that shows the format for a main
// method.  Each Java application must have one main method which
// is the entry point for execution.
// This example also shows use of the Java control constructs 
// 'if' and 'for'

// After compilation with javac H3.java
// Just for fun, try these to see how command line arguments to main() work:
//    java H3
//    java H3 one two three
//    java H3 1 2 3
//    java H3 Hello there how are you today.

import java.util.Scanner;

public class H3 {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println();  // print a blank line
        System.out.println("Hello World!");  
        System.out.printf("Hello World!, again\n");  // using C printf 
	if (args.length == 0)  
          System.out.println("I've got no argument with that!");
        else 
          if (args.length == 1)  // next line uses C printf
            System.out.printf("The argument typed is: \"%s\"", args[0]);
          else {  // next lines use traditional Java println
            System.out.println("The command line arguments typed are: ");
            for (int i = 0;  i < args.length;  i++)
                System.out.println("  Argument " + i + ": \"" + args[i] +  
                    "\"");
          }
        System.out.println();

        System.out.printf("Enter three integers and I'll repeat them: ");

        for (int i = 0; i < 3; i++) {
	    if (s.hasNext())
              System.out.printf("%d\n", s.nextInt());
        }
	  
    }  // main

}  // H3 class
