public class LinkedList<T extends Comparable<T>> implements List<T> {
    private Node<T> start;
    private Node<T> end;
    private boolean isSorted;

    public LinkedList() {
        start = new Node<T>(null, null);
        end = start;
        isSorted = true;
    }

    public boolean add(T element) {
        if (element == null) return false;

        else if (size() == 0) {
            start = new Node<T>(element, null);
            end = start;
            return true;
        }

        else {
            end.setNext(new Node<T>(element, null));
//            if (end.getData() > end.getNext().getData()) isSorted = false;
            end = end.getNext();
            return true;
        }
    }

    public boolean add(int index, T element) {
        if (element == null || index < 0 || index > size()) return false;

        else if (index == 0) {
            start = new Node<T>(element, start);
            return true;
        }

        else if (index == size()) {
            end = new Node<T>(element, null);
            return true;
        }

        else {
            int currIndex = 1;
            Node<T> currNode = start;
            while (currNode.getNext() != null) {
                if (currIndex == index) {
                    currNode.setNext(new Node<T>(element, currNode.getNext()));
                    return true;
                } 
                else {
                    currNode = currNode.getNext();
                    currIndex++;
                }
            }
            return false;
        }
    }

    public void clear() {
        start = new Node<T>(null, null);
        end = start;
    }

    public T get(int index) {
        if (index < 0 || index >= size()) return null;

        else if (index == 0) return start.getData();

        else {
            Node<T> currNode = start;
            int currIndex = 0;
            T value = null;
            while(currIndex < size()) {
                if (currIndex == index) {
                    value = currNode.getData();
                }
                else {
                    currNode = currNode.getNext();
                    currIndex++;
                }
            }
            return value;
        }
    }

    public int indexOf(T element) {
        if (isSorted) {
//            Node<T> currNode = start;
//            int currIndex = 0;
//            while(currNode != null) {
//                if (currNode.getData() < element) {
//                    currNode = currNode.getNext();
//                    currIndex++;
//                }
//
//                else if (currNode.getData() == element) {
//                    return currIndex;
//                }
//
//                else return -1;
//            }
            return -1;
        }

        else {
            if (element == null) return -1;

            Node<T> currNode = start;
            int index = 0;
            while(index < size()) {
                if (element == currNode.getData()) {
                    return index;
                }
                else {
                    currNode = currNode.getNext();
                    index++;
                }
            }
            return -1;
        }

    }

    public boolean isEmpty() {
        if (size() == 0) return true;
        else return false;
    }

    public int size() {
        if (start.getData() == null) {
            return 0;
        }

        else {
            Node<T> currNode = start;
            int size = 1;
            while (currNode.getNext() != null) {
                size++;
                currNode = currNode.getNext();
            }
            return size;
        }
    }

    public void sort() {
    }

    public T remove(int index) {
        return start.getData();
    }

    public void greaterThan(T element) {
    }

    public void lessThan(T element) {
    }

    public void equalTo (T element) {
    }

    public String toString() {
        String result = "";
        Node<T> currNode = start;

        while (currNode != null) {
            result += currNode.getData();
            currNode = currNode.getNext();

            if (currNode != null) result += ", ";
        }
        return result;
    }

    public static void main(String[] args) {
        LinkedList ls = new LinkedList();
        ls.add(1);
        ls.add(9);
        ls.add(7);
        ls.add(4);
        ls.add(5);
        ls.add(6);
        ls.add(3,20);
        System.out.println(ls);
    }
}
