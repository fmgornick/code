public class ArrayList<T extends Comparable<T>> implements List<T> {

    boolean add(T element) {
        return false;
    }

    boolean add(int index, T element) {
        return false;
    }

    void clear() {
    }

    T get(int index) {
        return null;
    }

    int index(int index) {
        return -1;
    }

    boolean isEmpty() {
        return false;
    }

    int size() {
        return -1;
    }

    void sort() {
    }

    T remove(int index) {
        return null;
    }

    void greaterThan(T element) {
    }

    void lessThan(T element) {
    }

    void equalTo(T element) {
    }

    String toString() {
        return "";
    }
}
