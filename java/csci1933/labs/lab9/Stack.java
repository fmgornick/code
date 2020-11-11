public class Stack<T extends Comparable<T>> {
    private T[] stack;
    private int topIndex = -1;

    public Stack() {
        stack = (T[]) new Comparable[5];
    }

    public Stack(int size) {
        stack = (T[]) new Comparable[size];
    }

    public T pop() {
        return stack[topIndex--];
    }

    public void push(T item) throws StackException {
        if (topIndex + 1 >= stack.length) {
            throw new StackException(stack.length);
        }

        else stack[++topIndex] = item;
    }

    public String toString() {
        String result = "";
        if (topIndex == -1) return result;

        else {
            for (int i = 0; i < topIndex; i++) {
                result += stack[i] + ", ";
            }
            result += stack[topIndex];
            return result;
        }
    }

    public static void main(String[] args) throws StackException {
        Stack s = new Stack(5);
        s.push(1);
        s.push(1);
        s.push(3);
        s.push(5);
        s.push(4);
        System.out.println(s);
    }
}

