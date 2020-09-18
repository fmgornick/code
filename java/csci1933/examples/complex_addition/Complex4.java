// Complex4.java
// Revised 9/2020

// A reasonable complex number class

// Can you explain the reasoning behind everything that is done here?
// What about the mutating of "this" Complex4 operand in the
// addComplex() and subtractComplex() methods?
// Can you modify addComplex() and subtractComplex() to return a
// new Complex4 object without mutating either of the operands?
// Try it, and write a main() driver within this Complex4 class to test
// your modified  methods.

// Also view and run the file ComplexComputation.java and follow the
// instructions there.

public class Complex4 {

    private double realPart = 0;  
    private double imaginaryPart = 0;

    public Complex4(double a, double b) {
        realPart = a;
        imaginaryPart = b;
    }

    public Complex4() {}  // default constructor

    // accessor methods

    public void setRealPart(double value) {
        realPart = value;
    }

    public void setImaginaryPart(double value) {
        imaginaryPart = value;
    }

    public double getRealPart() {
        return realPart;
    }
   
    public double getImaginaryPart() {
        return imaginaryPart;
    }

    // operators

    // note: mutates "this" complex number
    public void addComplex(Complex4 c) {
        realPart = realPart + c.getRealPart();
        imaginaryPart = imaginaryPart + c.getImaginaryPart();
    }

    // note: mutates "this" complex number
    public void subtractComplex(Complex4 c) {
        realPart = realPart - c.getRealPart();
        imaginaryPart = imaginaryPart - c.getImaginaryPart();
    }

    public String toString() {
        return "" + realPart + "+" + imaginaryPart + "i";
    }

    public boolean equals(Object anotherObject) {
        Complex4 temp;
        boolean same = false;
        if (anotherObject instanceof Complex4) {
          temp = (Complex4) anotherObject;
          if (realPart == temp.getRealPart() &&
              imaginaryPart == temp.getImaginaryPart())
              same = true;
        }
        return same;
    }

    public static void main(String args[]) {
        Complex4 c1 = new Complex4();
        Complex4 c2 = new Complex4(3,4);
        Complex4 c3 = new Complex4(5,6);

        c1.subtractComplex(c2);

        System.out.println(c1);
    }
          
}  // Complex4 class
