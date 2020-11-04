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
            if (end.getData().compareTo(end.getNext().getData()) > 0) isSorted = false;
            end = end.getNext();
            return true;
        }
    }

    public boolean add(int index, T element) {
        if (element == null || index < 0 || index > size()) return false;

        else if (index == 0) {
            start = new Node<T>(element, start);
            if (start.getData().compareTo(start.getNext().getData()) > 0) isSorted = false;
            return true;
        }

        else if (index == size()) {
            if (end.getData().compareTo(element) > 0) isSorted = false;
            end.setNext(new Node<T>(element, null));
            end = end.getNext();
            return true;
        }

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
            while(currIndex < size()) {
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

    public int indexOf(T element) {
        if (isSorted) {
            Node<T> currNode = start;
            int currIndex = 0;
            while(currNode != null) {
                if (currNode.getData().compareTo(element) < 0) {
                    currNode = currNode.getNext();
                    currIndex++;
                }

                else if (currNode.getData().compareTo(element) == 0) {
                    return currIndex;
                }

                else return -1;
            }
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

    public boolean sorted() {
        Node<T> head = start.getNext();
        Node<T> tail = start;

        while(head != null) {
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
                    if (front.getData().compareTo(middle.getData()) < 0) {
                        middle.setNext(front.getNext());
                        front.setNext(middle);
                        back.setNext(front);
                        back = front;
                        front = middle.getNext();
                    }

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

    public T remove(int index) {
        Node<T> head;
        Node<T> tail;

        if (index < 0 || index >= size()) return null;

        else if (index == 0) {
            head = start;
            start = start.getNext();
            return head.getData();
        }

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
            if (start.getData().compareTo(element) <= 0) {
                start = null;
                end = start;
                head = null;
            }

            while(head != null) {
                if (head.getData().compareTo(element) > 0) {
                    tail.setNext(null);
                    start = head;
                    break;
                }
                else {
                    tail = head;
                    head = head.getNext();
                }
            }
        }

        else {
            while (start.getData().compareTo(element) <= 0) {
                start = start.getNext();
                head.setNext(null);
                head = start;
                tail = head;
            }

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
            if (start.getData().compareTo(element) >= 0) {
                start = null;
                end = start;
                head = null;
            }

            while(head != null) {
                if (head.getData().compareTo(element) >= 0) {
                    tail.setNext(null);
                    end = tail;
                    break;
                }
                else {
                    tail = head;
                    head = tail.getNext();
                }
            }
        }

        else {
            while (start.getData().compareTo(element) >= 0) {
                start = start.getNext();
                head.setNext(null);
                head = start;
                tail = head;
            }

            while(head != null) {
                if (head.getData().compareTo(element) >= 0) {
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

    public void equalTo (T element) {
        if (indexOf(element) == -1) {
            start = null;
            end = start;
        }

        else {
            int currIndex = 0;
            Node<T> head = start;
            Node<T> tail = head;
            while (currIndex < indexOf(element)) {
                tail = head;
                head = head.getNext();
                currIndex++;
            }
            tail.setNext(null);
            start = head;
            tail = head;
            head = head.getNext();

            while (head.getData().compareTo(element) == 0) {
                tail = head;
                head = head.getNext();
            }
            tail.setNext(null);
            end = tail;
        }
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
        LinkedList<Integer> ls = new LinkedList<>();
        ls.add(8);
        ls.add(7);
        ls.add(4);
        ls.add(1);
        ls.add(5);
        ls.add(9);
        ls.add(3,6);
        System.out.println(ls);
        ls.sort();
        System.out.println(ls);
        System.out.println("start: " + ls.start.getData());
        System.out.println("end: " + ls.end.getData());
    }
}
