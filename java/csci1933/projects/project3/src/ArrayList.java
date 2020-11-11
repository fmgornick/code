// Fletcher Gornick, GORNI025

public class ArrayList<T extends Comparable<T>> implements List<T> {
    private T[] array;
    private int lastOpen;
    private boolean isSorted;

    // ArrayList default constructor
    public ArrayList() {
        array = (T[]) new Comparable[2];
        isSorted = true;
        lastOpen = 0;
    }

    // iterates through array, copying elements over and doubling size
    public void resize() {
        T[] newArray = (T[]) new Comparable[2 * array.length];
        for (int i = 0; i < array.length; i++) {
            newArray[i] = array[i];
        }
        array = newArray;
    }

    // adds to first open index and resizes if needed
    public boolean add(T element) {
        if (element == null) return false;

        else if (lastOpen == 0) {
            array[lastOpen] = element;
            lastOpen++;
            return true;
        }

        else {
            if (lastOpen >= array.length) resize();
            array[lastOpen] = element;

            if (element.compareTo(array[lastOpen - 1]) < 0) isSorted = false;
            lastOpen++;
            return true;
        }
    }

    public boolean add(int index, T element) {
        // make sure element is within the list
        if (size() == 0 || index < 0 || index >= lastOpen || element == null) return false;

        // base case, if adding to beginning of list
        else if (index == 0) {
            if (lastOpen >= array.length) resize();
            for (int i = lastOpen - 1; i >= 0; i--) {
                array[i + 1] = array[i];
            }
            array[index] = element;
            if (array[1] != null && element.compareTo(array[1]) > 0) isSorted = false;
            lastOpen++;
            return true;
        }

        // every other case
        else {
            if (lastOpen >= array.length) resize();
            for (int i = lastOpen - 1; i >= index; i--) {
                array[i + 1] = array[i];
            }
            array[index] = element;
            if (element.compareTo(array[index-1]) < 0 || element.compareTo(array[index+1]) > 0) isSorted = false;
            lastOpen++;
            return true;
        }
    }

    // sets each element to null and moves first open index to start
    public void clear() {
        for (int i = 0; i < lastOpen; i++) {
            array[i] = null;
        }
        lastOpen = 0;
    }

    // just returns the element in a given index if it's within the list
    public T get(int index) {
        if (index < 0 || index >= lastOpen) return null;
        else return array[index];
    }

    // iterates through list and returns element if it finds one
    public int indexOf(T element) {
        if (element == null) return -1;

        else if (isSorted) {
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) == 0) return i;
                else if (array[i].compareTo(element) > 0) return -1;
            }
            // if element not found
            return -1;
        }

        else {
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) == 0) {
                    return i;
                }
            }
            // if element not found
            return -1;
        }
    }

    // only needs to check if first index is null (assuming nobody is adding 
    // null elements)
    public boolean isEmpty() {
        if (array[0] == null) return true;
        else return false;
    }

    // lastOpen keeps track of the first open index, therefore it equates to
    // the size (i know it's kinda confusing but it made sense when i made it)
    public int size() {
        return lastOpen;
    }

    // insertion sort algorithm
    public void sort() {
        if (!isSorted) {
            int minIndex;
            T temp;
            for (int i = 0; i < lastOpen; i++) {
                minIndex = i;
                for (int j = i + 1; j < lastOpen; j++) {
                    if (array[minIndex].compareTo(array[j]) > 0) minIndex = j;
                }
                temp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = temp;
            }
            isSorted = true;
        }
    }

    // removes index then shifts following elements to the left one index
    public T remove(int index) {
        if (index < 0 || index >= lastOpen) return null;

        else {
            T element = array[index];
            for (int i = index; i < lastOpen - 1; i++) {
                array[i] = array[i + 1];
            }
            lastOpen--;
            return element;
        }
    }

    public void greaterThan(T element) {
        if (isSorted) {
            // check to make sure the whole list isn't already greater than
            if (array[0].compareTo(element) <= 0) {
                int index = 0;
                int newLastOpen;
                // iterate through list until first element greater than is
                // reached
                while (array[index].compareTo(element) <= 0 && index < lastOpen) {
                    index++;
                    if (index == lastOpen) {
                        break;
                    }
                }

                newLastOpen = lastOpen - index;

                // moves greater than indexes to the start
                for (int i = 0; index < lastOpen; i++) {
                    array[i] = array[index];
                    array[index] = null;
                    index++;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
            // iterates through and removes elements less than or equal to
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) <= 0) {
                    remove(i);
                    i--;
                }
            }
        }
    }

    public void lessThan(T element) {
        if (isSorted) {
            // check to make sure the whole list isn't already less than
            if (array[lastOpen - 1].compareTo(element) >= 0) {
                int index = 0;
                int newLastOpen;
                // iterate through list until first element less than is
                // reached
                while (array[index].compareTo(element) < 0) {
                    index++;
                    if (index == lastOpen) {
                        break;
                    }
                }
                newLastOpen = index;

                // removes indexes greater than or equal to
                for (int i = index; i < lastOpen; i++) {
                    array[i] = null;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
            // iterates through and removes elements greater than or equal to
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) >= 0) {
                    remove(i);
                    i--;
                }
            }
        }
    }

    public void equalTo(T element) {
        if (isSorted) {
            int index = 0;
            int newLastOpen;
            // iterate until index is greaterThan or equal to
            while (array[index].compareTo(element) < 0) index++;

            // clear list if current element is not equal to
            if (array[index].compareTo(element) != 0) clear();

            else {
                newLastOpen = lastOpen - index;
                // shift list left to get rid of less than indexes
                for (int i = 0; index < lastOpen; i++) {
                    array[i] = array[index];
                    array[index] = null;
                    index++;
                }
                lastOpen = newLastOpen;
                index = 0;

                while (array[index].compareTo(element) == 0) index++;
                newLastOpen = index;

                // get rid of greater than indexes
                for (int i = index; i < lastOpen; i++) {
                    array[i] = null;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
            // iterate through and remove elements not equal to
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) != 0) {
                    remove(i);
                    i--;
                }
            }
        }
    }

    // iterate through and print each value
    public String toString() {
        String result = "";
        if (size() == 0) return result;

        else {
            for (int i = 0; i < lastOpen - 1; i++) {
                result += array[i] + ", ";
            }
            // last element doesn't need a comma after
            result += array[lastOpen - 1];
            return result;
        }
    }
}
