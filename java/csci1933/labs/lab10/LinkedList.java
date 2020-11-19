// Fletcher Gornick, GORNI025

public class LinkedList<T extends Comparable<T>> implements List<T> {
    private Node<T> start;
    private Node<T> end;
    private boolean isSorted;

    // LinkedList default constructor
    public LinkedList() {
        start = new Node<T>(null, null);
        end = start;
        isSorted = true;
    }

    // points end node to new element
    public boolean add(T element) {
        if (element == null) return false;

        // if it's the first element added
        else if (size() == 0) {
            start = new Node<T>(element, null);
            end = start;
            return true;
        }

        else {
            // every other case
            end.setNext(new Node<T>(element, null));
            if (end.getData().compareTo(end.getNext().getData()) > 0) isSorted = false;
            end = end.getNext();
            return true;
        }
    }

    public boolean add(int index, T element) {
        // make sure element is within the list
        if (element == null || index < 0 || index >= size()) return false;

        else if (index == 0 && size() == 0) return false;

        // element added to the start of the list
        else if (index == 0) {
            start = new Node<T>(element, start);
            end = start.getNext();
            if (start.getData().compareTo(end.getData()) > 0) isSorted = false;
            return true;
        }

        // other cases
        else {
            int currIndex = 1;
            Node<T> currNode = start;
            while (currNode.getNext() != null) {
                if (currIndex == index) {
                    if (currNode.getNext().getData().compareTo(element) < 0) isSorted = false;
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

    // changes start node pointer to null and data to null
    public void clear() {
        start = new Node<T>(null, null);
        end = start;
    }

    // iterate through the list until index is reached then return element
    public T get(int index) {
        // make sure element is in list
        if (index < 0 || index >= size()) return null;

        else if (index == 0) return start.getData();

        else {
            Node<T> currNode = start;
            int currIndex = 0;
            while (currIndex < size()) {
                if (currIndex == index) {
                    return currNode.getData();
                }
                else {
                    currNode = currNode.getNext();
                    currIndex++;
                }
            }
            return null;
        }
    }

    // iterates through list and returns element if it finds one
    public int indexOf(T element) {
        if (element == null) return -1;

        else if (isSorted) {
            Node<T> currNode = start;
            int currIndex = 0;
            while (currNode != null) {
                if (currNode.getData().compareTo(element) < 0) {
                    currNode = currNode.getNext();
                    currIndex++;
                }

                else if (currNode.getData().compareTo(element) == 0) {
                    return currIndex;
                }

                // if element not found
                else return -1;
            }
            return -1;
        }

        else {
            if (element == null) return -1;

            Node<T> currNode = start;
            int index = 0;
            while (index < size()) {
                if (element == currNode.getData()) {
                    return index;
                }
                else {
                    currNode = currNode.getNext();
                    index++;
                }
            }
            // if element not found
            return -1;
        }
    }

    // only needs to check if first index is null (assuming nobody is adding 
    // null elements)
    public boolean isEmpty() {
        if (size() == 0) return true;
        else return false;
    }

    // iterates through list until reaching final node and incrementing the
    // size
    public int size() {
        // make sure size isn't 0
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

    // iterate through and check to see if it's sorted
    public boolean sorted() {
        Node<T> head = start.getNext();
        Node<T> tail = start;

        while (head != null) {
            if (head.getData().compareTo(tail.getData()) < 0) {
                return false;
            }
            tail = head;
            head = head.getNext();
        }
        return true;
    }

    public void sort() {
        if (!isSorted) {
            Node<T> front = start.getNext();
            Node<T> middle;
            Node<T> back = start;
            T min = start.getData();

            // locate smallest index
            while (front != null) {
                if (front.getData().compareTo(min) < 0) {
                    min = front.getData();
                }
                front = front.getNext();
            }

            front = start.getNext();
            if(start.getData().compareTo(min) > 0) {
                while (front != null) {
                    if (front.getData().compareTo(min) == 0) {
                        // set front equal to smallesr element
                        if (front.getNext() == null) {
                            back.setNext(null);
                            front.setNext(start);
                            start = front;
                            end = back;
                            break;
                        }
                        else {
                            back.setNext(front.getNext());
                            front.setNext(start);
                            start = front;
                            break;
                        }
                    }

                    else {
                        back = front;
                        front = front.getNext();
                    }
                }
            }

            while (!sorted()) {
                back = start;
                middle = back.getNext();
                front = middle.getNext();

                while (front != null) {
                    // switch elements if needed
                    if (front.getData().compareTo(middle.getData()) < 0) {
                        middle.setNext(front.getNext());
                        front.setNext(middle);
                        back.setNext(front);
                        back = front;
                        front = middle.getNext();
                    }

                    // move pointers up one if no switch needed
                    else {
                        back = middle;
                        middle = front;
                        front = front.getNext();
                    }
                }

                if (sorted()) end = middle;
            }
        }
    }

    // iterate through list until index reached, then remove element
    public T remove(int index) {
        Node<T> head;
        Node<T> tail;

        // check if index in list
        if (index < 0 || index >= size()) return null;

        // if there's only one element
        else if (index == 0 && start.getNext() == null) {
            T temp = start.getData();
            clear();
            return temp;
        }

        // remove furst element
        else if (index == 0) {
            head = start;
            start = start.getNext();
            return head.getData();
        }

        // other cases
        else {
            head = start.getNext();
            tail = start;
            int currIndex = 1;

            while (currIndex < size()) {
                if (currIndex == index) {
                    tail.setNext(head.getNext());
                    head.setNext(null);
                    return head.getData();
                }
                else {
                    tail = head;
                    head = head.getNext();
                    currIndex++;
                }
            }
            return null;
        }
    }

    public void greaterThan(T element) {
        Node<T> head = start;
        Node<T> tail = head;
        if (isSorted) {
            // check to make sure the whole list isn't already greater than
            if (end.getData().compareTo(element) <= 0) {
                clear();
            }

            // iterate through list until first element greater than is
            // reached
            while(head != null) {
                if (head.getData().compareTo(element) > 0) {
                    if (tail != start) {
                        // remove elements before
                        tail.setNext(null);
                    }
                    start = head;
                    break;
                }
                else {
                    tail = head;
                    head = head.getNext();
                }
            }
        }

        // if not sorted
        else {
            // first index case
            while (start.getData().compareTo(element) <= 0) {
                start = start.getNext();
                head.setNext(null);
                head = start;
                tail = head;
            }

            // every other case
            while(head != null) {
                if (head.getData().compareTo(element) <= 0) {
                    tail.setNext(head.getNext());
                    head.setNext(null);
                    head = tail.getNext();
                }
                else {
                    tail = head;
                    head = tail.getNext();
                }
            }
            end = tail;
        }
    }

    public void lessThan(T element) {
        Node<T> head = start;
        Node<T> tail = head;
        if (isSorted) {
            // check to make sure the whole list isn't already less than
            if (start.getData().compareTo(element) >= 0) {
                clear();
            }

            // iterate through list until first element greater than or equal
            // to is reached
            while(head != null) {
                if (head.getData().compareTo(element) >= 0) {
                    tail.setNext(null);
                    end = tail;
                    break;
                }
                else {
                    // remove all indexes greater than or equal to
                    tail = head;
                    head = tail.getNext();
                }
            }
        }

        else {
            // start case
            while (start.getData().compareTo(element) >= 0) {
                start = start.getNext();
                head.setNext(null);
                head = start;
                tail = head;
            }

            // remove index of greater than or equal to elements
            while(head != null) {
                if (head.getData().compareTo(element) >= 0) {
                    tail.setNext(head.getNext());
                    head.setNext(null);
                    head = tail.getNext();
                }
                // if element less than, increment pointers
                else {
                    tail = head;
                    head = tail.getNext();
                }
            }
            end = tail;
        }
    }

    public void equalTo (T element) {
        // clear list if none equal to
        if (indexOf(element) == -1) {
            clear();
        }

        else {
            int currIndex = 0;
            Node<T> head = start;
            Node<T> tail = head;
            // iterates to the equal element
            while (currIndex < indexOf(element)) {
                tail = head;
                head = head.getNext();
                currIndex++;
            }
            // remove elements before equal element
            tail.setNext(null);
            start = head;
            tail = head;
            head = head.getNext();

            if (head != null) {
                // remove all other nodes not equal to element
                while (head.getData().compareTo(element) == 0) {
                    tail = head;
                    head = head.getNext();
                }
                tail.setNext(null);
                end = tail;
            }
        }
    }

    // iterate through and print each value
    public String toString() {
        String result = "";
        Node<T> currNode = start;

        while (currNode != null) {
            result += currNode.getData();
            currNode = currNode.getNext();

            // last element doesn't need a comma after
            if (currNode != null) result += ", ";
        }
        return result;
    }

    public void removeEvery(int n) {
        int index = 1;
        Node<T> currNode = start;
        while (currNode != null) {
            if (index % n == 0) {
                currNode = currNode.getNext();
                remove(index);
                index++;
            }
            else {
                currNode = currNode.getNext();
                index++;
            }
        }
    }

    public static void main(String[] args) {
        LinkedList<Integer> a = new LinkedList<>();
        a.add(1);
        a.add(2);
        a.add(3);
        a.add(4);
        a.add(5);
        a.add(6);
        a.add(7);
        a.add(8);
        System.out.println(a);
        a.removeEvery(1);
        System.out.println(a);
    }
}
