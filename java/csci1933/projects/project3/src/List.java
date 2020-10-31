public interface List<T extends Comparable<T>> {
    /*
     * Add an element to end of the list. If element is null,
     * it will NOT add it and return false.  Otherwise, it
     * will add it and return true. Updates isSorted to false.
     */
    boolean add(T element);

    /*
     * Add an element at specific index. This method should
     * also shift the element currently at that position (if
     * any) and any subsequent elements to the right (adds
     * one to their indices). If element is null, or if index
     * index is out-of-bounds (index < 0 or index >= size_of_list),
     * it will NOT add it and return false. Otherwise it will
     * add it and return true. See size() for the definition
     * of size of list. Also updates isSorted variable to false.
     */
    boolean add(int index, T element);

    /*
     * Remove all elements from the list.
     */
    void clear();

    /*
     * Return the element at given index. If index is
     * out-of-bounds, it will return null.
     */
    T get(int index);

    /*
     * Return the first index of element in the list. If element
     * is null or not found in the list, return -1. If isSorted is
     * true, uses the ordering of the list to increase the efficiency
     * of the search.
     */
    int indexOf(T element);

    /*
     * Return true if the list is empty and false otherwise.
     */
    boolean isEmpty();

    /*
     * Return the number of elements in the list. For example, if
     * 4 elements added to a list, size will return 4, while the
     * last index in the list will be 3.
     */
    int size();

    /*
     * Sort the elements of the list in ascending order using insertion sort.
     * If isSorted is true, do NOT re-sort.
     * Hint: Since T extends Comparable, you will find it useful
     * to use the public int compareTo(T other) method.
     */
    void sort();

    /*
     * Remove whatever is at index index in the list and return
     * it. If index is out-of-bounds, return null. Shift the
     * indices as in the other remove.
     */
    T remove(int index);

    /*
     * Removes all elements of the list that are less than or equal to 'element'.
     * When this function returns, the only elements that should be left in this list
     * are greater than 'element'.
     * If isSorted is true, uses the ordering of the list to
     * increase the efficiency of the search.
     * This method should not change the ordering of the method.
     */
    void greaterThan(T element);

    /*
     * Removes all elements of the list that are greater than or equal to 'element'.
     * When this function returns, the only elements that should be left in this list
     * are less than 'element'.
     * If isSorted is true, uses the ordering of the list to
     * increase the efficiency of the search.
     * This method should not change the ordering of the method.
     */
    void lessThan(T element);

    /*
     * Removes all elements of the list that are not equal to 'element'
     * When this function returns, the only elements that should be left in this list
     * are equal to 'element'.
     * This method should not change the ordering of the method.
     */
    void equalTo(T element);

    /*
     * Note that this method exists for debugging purposes.
     * It calls the toString method of the underlying elements in
     * the list in order to create a String representation of the list.
     * The format of the toString should appear as follows:
     * Element_1
     * Element_2
     * .
     * .
     * .
     * Element_n
     * Watch out for extra spaces or carriage returns. Each element
     * should be printed on its own line.
     */
    String toString();
}  // End of interface definition.
