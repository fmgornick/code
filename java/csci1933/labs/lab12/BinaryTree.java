public class BinaryTree<V extends Comparable<V>> {
    private Node<V> root;

    public BinaryTree(Node<V> root) {
        this.root = root;
    }

    public Node<V> getRoot() {
        return this.root;
    }

    public void printInOrder() {
        printInOrderHelper(root);
    }
    private void printInOrderHelper(Node<V> node) {
        if (node == null) return;
        printInOrderHelper(node.getLeft());
        System.out.print(node.getValue() + " ");
        printInOrderHelper(node.getRight());
    }

    public void printPreorder(){
        printPreorderHelper(root);
    }
    private void printPreorderHelper(Node<V> node) {
        if (node == null) return;
        System.out.print(node.getValue() + " ");
        printPreorderHelper(node.getLeft());
        printPreorderHelper(node.getRight());
    }

    public void printPostorder() {
        printPostorderHelper(root);
    }
    private void printPostorderHelper(Node<V> node) {
        if (node == null) return;
        printPostorderHelper(node.getLeft());
        printPostorderHelper(node.getRight());
        System.out.print(node.getValue() + " ");
    }

    public V[] flatten() {
        String[] arrString = toString().split(" ");
        V[] arr = (V[]) new Comparable[arrString.length];

        for (int i = 0; i < arrString.length; i++) {
            arr[i] = (V) arrString[i];
        }

        int minIndex = 0;
        V temp;
        for (int i = 0; i < arr.length; i++) {
            minIndex = i;
            for (int j = i+1; j < arr.length; j++) {
                if (arr[j].compareTo(arr[minIndex]) < 0) minIndex = j;
            }
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }

        return arr;
    }

    public Node<V> findNode(V t) {
        return findNodeHelper(root,t);
    }
    public Node<V> findNodeHelper(Node<V> node, V value) {
        if (node != null) {
            if (node.getValue() == value) return node;
            else {
                Node<V> foundNode = findNodeHelper(node.getLeft(), value);
                if (foundNode == null) foundNode = findNodeHelper(node.getRight(), value);
                return foundNode;
            }
        }
        else return null;
    }

    public boolean containsSubtree(BinaryTree<V> other) {
        if (other == null) return true;
        String[] treeString = toString().split(" ");
        String[] subtreeString = other.toString().split(" ");

        V[] tree = (V[]) new Comparable[treeString.length];
        V[] subtree = (V[]) new Comparable[subtreeString.length];

        for (int i = 0; i < treeString.length; i++) {
            tree[i] = (V) treeString[i];
        }
        for (int i = 0; i < subtreeString.length; i++) {
            subtree[i] = (V) subtreeString[i];
        }

        boolean root = false;
        for (int i = 0; i < subtree.length; i++) {
            for (int j = 0; j < tree.length; j++) {
                if (tree[j].compareTo(subtree[i]) == 0) root = true;
            }
        }

        if (root) {
            String[] newSubtreeString = toStringHelper(findNode(other.getRoot().getValue())).split(" ");
            V[] newSubtree = (V[]) new Comparable[newSubtreeString.length];
            for (int i = 0; i < newSubtreeString.length; i++) {
                newSubtree[i] = (V) newSubtreeString[i];
            }

            if (subtree.length != newSubtree.length) return false;
            for (int i = 0; i < newSubtree.length; i++) {
                if (subtree[i].compareTo(newSubtree[i]) != 0) return false;
            }
            return true;
        }

        else return false;
    }

    public String toString() {
        return toStringHelper(root);
    }
    public String toStringHelper(Node<V> node) {
        if (node == null) return "";
        return "" + toStringHelper(node.getLeft()) + node.getValue() + " " + toStringHelper(node.getRight());

    }
 
    public static void main (String args[]) {
        // Tree given for testing on
        BinaryTree<Integer> p1Tree = new BinaryTree<Integer>(new Node<Integer>(1,
            new Node<Integer>(2,
                new Node<Integer>(4, null, null),
                new Node<Integer>(5, null, null)),
            new Node<Integer>(3, null, null)));

        // Milestone 1
        System.out.println();
        System.out.println("Milestone 1");
        p1Tree.printInOrder();      // expected output: 4 2 5 1 3
        System.out.println();
        p1Tree.printPreorder();     // expected output: 1 2 4 5 3
        System.out.println();
        p1Tree.printPostorder();    // expected output: 4 5 2 3 1
        System.out.println();
        System.out.println();

        // Milestone 2 -- expected output: 1 2 3 4 5
        System.out.println("Milestone 2");
        Comparable[] array_representation = p1Tree.flatten();
        for (int i = 0; i < array_representation.length; i++) {
            System.out.print(array_representation[i] + " ");
        }
        System.out.println();
        System.out.println();


        // Milestone 3
        System.out.println("Milestone 3");
        BinaryTree<Integer> p2Tree = new BinaryTree<Integer>(new Node<Integer>(2,
                new Node<Integer>(4, null, null),
                new Node<Integer>(5, null, null)));
        BinaryTree<Integer> p3Tree = new BinaryTree<Integer>(new Node<Integer>(1,
                new Node<Integer>(2, null, null),
                new Node<Integer>(3, null, null)));
        BinaryTree<Integer> p4Tree = null;

        System.out.println(p1Tree.containsSubtree(p2Tree)); // expected output: true
        System.out.println(p1Tree.containsSubtree(p3Tree)); // expected output: false
        System.out.println(p1Tree.containsSubtree(p4Tree)); // expected output: true
    }
}
