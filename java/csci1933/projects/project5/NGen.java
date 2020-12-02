// NGen.java
// A *simplified* generic node class for use with generic higher
// level data structures
// List functions such as addInOrder() are handled at the "list" level
// Uses generic data
// Revised 10/2020

public class NGen <T> {
  
    // constructors
    
    public NGen () {}

    public NGen (T o, NGen <T> link) {
        data = o;
        next = link;
    }

    // selectors

    public T getData() {
        return data;
    }

    public void setData(T o) {
        data = o;
    }

    public NGen <T> getNext() {
        return next;
    }

    public void setNext(NGen <T> link) {
        next = link;
    }

    // instance variables

    private T data;
    private NGen <T> next;

}  // NGen class
