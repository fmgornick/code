public class StackException extends Exception {
    public int size;

    public StackException(String message) {
        super(message);
    }

    public StackException(int size) {
        this.size = size;
    }

    int getSize() {
        return size;
    }
}
