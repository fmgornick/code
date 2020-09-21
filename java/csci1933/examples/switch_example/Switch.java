// Switch.java
// Mutually exclusive cases implemented with a *switch* construct
// Requires an int be entered at command line
// Updated 2/2020

// How would this be done with *if* statements instead?  Try it.
// Would the ifs be nested or non-nested, and would it make a 
// difference whether they would be nested or not?

// What happens if one or more of the "break" statements are removed?
// When would you want to remove a break, if ever?
// Why should a "default" case always be part of a switch?
// Would you be able to mimic the behavior of the switch that
// is missing breaks with an if construct?

public class Switch {

public static void main(String[] args) {
    int i;  // value converted from command line
    if (args.length != 0) {
        i = Integer.valueOf(args[0]); // get integer value of args[0]
        System.out.println();
        switch (i) {  // i must be a scalar valued expression
                      // char or String will also work
        case 0: System.out.println("Your number is 0");
                break; 
        case 1: System.out.println("Your number is 1");
                break; 
        case 2: System.out.println("Your number is 2");
                break; 
        case 3: System.out.println("Your number is 3");
                break; 
        case 4: System.out.println("Your number is 4");
                break; 
        case 5: System.out.println("Your number is 5");
                break; 
        case 6: System.out.println("Your number is 6");
                break; 
        case 7: System.out.println("Your number is 7");
                break; 
        case 8: System.out.println("Your number is 8");
                break; 
        case 9: System.out.println("Your number is 9");
                break; 
        case 10: System.out.println("Your number is 10");
                break; 
        case 11: System.out.println("Your number is 11");
                break; 
        case 12: System.out.println("Your number is 12");
                break; 
        case 13: System.out.println("Your number is 13");
                break; 
        case 14: System.out.println("Your number is 14");
                break; 
        case 15: System.out.println("Your number is 15");
                break; 
        case 16: System.out.println("Your number is 16");
                break; 
        case 17: System.out.println("Your number is 17");
                break; 
        case 18: System.out.println("Your number is 18");
                break; 
        case 19: System.out.println("Your number is 19");
                break; 
        case 20: System.out.println("Your number is 20");
                break; 
        case 21: System.out.println("Your number is 21");
                break; 
        case 22: System.out.println("Your number is 22");
                break; 
        case 23: System.out.println("Your number is 23");
                break; 
        case 24: System.out.println("Your number is 24");
                break; 
        case 25: System.out.println("Your number is 25");
                break; 
        case 26: System.out.println("Your number is 26");
                break; 
        case 27: System.out.println("Your number is 27");
                break; 
        case 28: System.out.println("Your number is 28");
                break; 
        case 29: System.out.println("Your number is 29");
                break; 
        case 30: System.out.println("Your number is 30");
                break; 
        case 31: System.out.println("Your number is 31");
                break; 
        case 32: System.out.println("Your number is 32");
                break; 
        case 33: System.out.println("Your number is 33");
                break; 
        case 34: System.out.println("Your number is 34");
                break; 
        case 35: System.out.println("Your number is 35");
                break; 
        case 36: System.out.println("Your number is 36");
                break; 
        case 37: System.out.println("Your number is 37");
                break; 
        case 38: System.out.println("Your number is 38");
                break; 
        case 39: System.out.println("Your number is 39");
                break; 
        case 40: System.out.println("Your number is 40");
                break; 
        case 41: System.out.println("Your number is 41");
                break; 
        case 42: System.out.println("Your number is 42");
                break; 
        case 43: System.out.println("Your number is 43");
                break; 
        case 44: System.out.println("Your number is 44");
                break; 
        case 45: System.out.println("Your number is 45");
                break; 
        case 46: System.out.println("Your number is 46");
                break; 
        case 47: System.out.println("Your number is 47");
                break; 
        case 48: System.out.println("Your number is 48");
                break; 
        case 49: System.out.println("Your number is 49");
                break; 
        case 50: System.out.println("Your number is 50");
                break; 
        default: System.out.println("fuck you");
        }
    }  
    else System.out.println("No integer was entered at command line");
    System.out.println();
}  // main method

}  // Switch class
