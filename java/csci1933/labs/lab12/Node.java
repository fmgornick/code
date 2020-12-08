public class Node<V extends Comparable<V>> {
    private V value;
    private Node<V> left, right;

    public Node(V value) {
        this.value = value;
    }

    public Node(V value, Node<V> left, Node<V> right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public Node<V> getLeft() {
        return left;
    }

    public void setLeft(Node<V> left) {
        this.left = left;
    }

    public Node<V> getRight() {
        return right;
    }

    public void setRight(Node<V> right) {
        this.right = right;
    }
}