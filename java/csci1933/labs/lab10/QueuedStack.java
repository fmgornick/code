import java.util.*;

public class QueuedStack<T extends Comparable<T>> {
    private Queue<T> q1;
    private Queue<T> q2;

    public QueuedStack() {
        q1 = new ArrayDeque<T>();
        q2 = new ArrayDeque<T>();
    }

    public void push(T o) {
        while (!q1.isEmpty()) q2.add(q1.remove());
        q1.add(o);
        while (!q2.isEmpty()) q1.add(q2.remove());
    }

    public T pop() {
        if (q1.isEmpty()) throw new RuntimeException("removing from an empty stack");

        T temp = q1.remove();
        return temp;
    }

    public T top() {
        return q1.peek();
    }

    public String toString() {
        return q1.toString();
    }

    public static void main(String[] args) {
        QueuedStack<Integer> a = new QueuedStack<Integer>();
        a.push(1);
        a.push(2);
        a.push(3);
        a.push(4);
        a.push(5);
        a.push(6);
        a.push(7);
        System.out.println(a);
        a.pop();
        System.out.println(a);
        System.out.println(a.top());
    }
}
