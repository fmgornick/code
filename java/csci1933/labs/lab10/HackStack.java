import java.util.*;

public class HackStack<T extends Comparable<T>> {
    private Stack<T> s1;
    private Stack<T> s2;

    public HackStack() {
        s1 = new Stack<T>();
        s2 = new Stack<T>();
    }

    public void push(T o) {
        s1.push(o);
    }

    public T pop() {
        if (s1.isEmpty()) return null;
        return s1.pop();
    }

    public T pop(int n) {
        int index = 1;
        T element = null;

        while (!s1.isEmpty()) {
            if (index == n) {
                element = s1.pop();
                break;
            }
            s2.push(s1.pop());
            index++;
        }
        if (element != null) {
            while (!s2.isEmpty()) {
                s1.push(s2.pop());
            }
            return element;
        }
        return null;
    }

    public T peek() {
        if (s1.isEmpty()) return null;
        return s1.peek();
    }

    public String toString() {
        return s1.toString();
    }

    public static void main(String[] args) {
        HackStack<Integer> a = new HackStack<Integer>();
        a.push(1);
        a.push(2);
        a.push(3);
        a.push(4);
        a.push(5);
        a.push(6);
        a.push(7);
        System.out.println(a);
        a.pop(4);
        System.out.println(a);
        System.out.println(a.peek());
    }
}
