import java.util.*;
public class StackedQueue<T> {
    private Stack<T> stack1;
    private Stack<T> stack2;

    public StackedQueue() {
        stack1 = new Stack<T>();
        stack2 = new Stack<T>();
    }

    public void enqueue(T o) {
        while (!stack1.isEmpty()) {
            stack2.push(stack1.pop());
        }
        stack1.push(o);
        while (!stack2.isEmpty()) {
            stack1.push(stack2.pop());
        }
    }

    public T dequeue() {
        if (stack1.isEmpty()) {
            throw new RuntimeException("removing from empty queue");
        }
        T temp = stack1.pop();
        return temp;
    }

    public T peek() {
        return stack1.peek();
    }

    public String toString() {
        return stack1.toString();
    }

    public boolean isEmpty() {
        if (stack1.isEmpty()) return true;
        return false;
    }

    public static void main(String[] args) {
        StackedQueue<Integer> a = new StackedQueue<Integer>();
        a.enqueue(1);
        a.enqueue(2);
        a.enqueue(3);
        a.enqueue(4);
        a.enqueue(5);
        a.enqueue(6);
        a.enqueue(7);
        System.out.println(a);
        a.dequeue();
        System.out.println(a);
        System.out.println(a.peek());
    }
}
