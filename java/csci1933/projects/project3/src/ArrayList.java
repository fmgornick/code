public class ArrayList<T extends Comparable<T>> implements List<T> {
    private T[] array;
    private int lastOpen;
    private boolean isSorted;

    public ArrayList() {
        array = (T[]) new Comparable[2];
        isSorted = true;
        lastOpen = 0;
    }

    public void resize() {
        T[] newArray = (T[]) new Comparable[2 * array.length];
        for (int i = 0; i < array.length; i++) {
            newArray[i] = array[i];
        }
        array = newArray;
    }

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
        if (size() == 0 || index < 0 || index >= lastOpen || element == null) return false;

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

    public void clear() {
        for (int i = 0; i < lastOpen; i++) {
            array[i] = null;
        }
        lastOpen = 0;
    }

    public T get(int index) {
        if (index < 0 || index >= lastOpen) return null;
        else return array[index];
    }

    public int indexOf(T element) {
        if (element == null) return -1;

        else if (isSorted) {
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) == 0) return i;
                else if (array[i].compareTo(element) > 0) return -1;
            }
            return -1;
        }

        else {
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) == 0) {
                    return i;
                }
            }
            return -1;
        }
    }

    public boolean isEmpty() {
        if (array[0] == null) return true;
        else return false;
    }

    public int size() {
        return lastOpen;
    }

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
            if (array[0].compareTo(element) <= 0) {
                int index = 0;
                int newLastOpen;
                while (array[index].compareTo(element) <= 0 && index < lastOpen) {
                    index++;
                    if (index == lastOpen) {
                        break;
                    }
                }

                newLastOpen = lastOpen - index;

                for (int i = 0; index < lastOpen; i++) {
                    array[i] = array[index];
                    array[index] = null;
                    index++;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
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
            if (array[lastOpen - 1].compareTo(element) >= 0) {
                int index = 0;
                int newLastOpen;
                while (array[index].compareTo(element) < 0) {
                    index++;
                    if (index == lastOpen) {
                        break;
                    }
                }
                newLastOpen = index;

                for (int i = index; i < lastOpen; i++) {
                    array[i] = null;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
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
            while (array[index].compareTo(element) < 0) index++;

            if (array[index].compareTo(element) != 0) clear();

            else {
                newLastOpen = lastOpen - index;
                for (int i = 0; index < lastOpen; i++) {
                    array[i] = array[index];
                    array[index] = null;
                    index++;
                }
                lastOpen = newLastOpen;
                index = 0;

                while (array[index].compareTo(element) == 0) index++;
                newLastOpen = index;

                for (int i = index; i < lastOpen; i++) {
                    array[i] = null;
                }
                lastOpen = newLastOpen;
            }
        }

        else {
            for (int i = 0; i < lastOpen; i++) {
                if (array[i].compareTo(element) != 0) {
                    remove(i);
                    i--;
                }
            }
        }
    }

    public String toString() {
        String result = "";
        if (size() == 0) return result;

        else {
            for (int i = 0; i < lastOpen - 1; i++) {
                result += array[i] + ", ";
            }
            result += array[lastOpen - 1];
            return result;
        }
    }
}
