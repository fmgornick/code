import java.util.Arrays;
public class BinaryTree {

    // TODO complete this method
    public static boolean isValid(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] == -1) return false;
        }
        if ((int)(Math.ceil((Math.log(arr.length) / Math.log(2)))) != (int)(Math.floor(((Math.log(arr.length) / Math.log(2)))))) return false;

        if (isBST(arr)) return true;
        return false;
    }

    public static boolean isBST(int[] arr) {
        return isBSTHelper(arr, 1, 1);
    }
    public static boolean isBSTHelper(int[] a, int n, int p) {
        if (n < a.length) {
            if (n == 2*p && a[n] > a[p]) return false;
            if (n == (2*p)+1 && a[n] < a[p]) return false;
            return (isBSTHelper(a,2*n,n) && isBSTHelper(a,(2*n)+1,n));
        }
        return true;
    }

    public static void main (String args[]) {
        // milestone 1
        int[] arr1 = new int[]{-1,7,4,10,3,6,8,15};
        int[] arr2 = new int[]{-1,20,12,32,5,18,25,38};
        int[] arr3 = new int[]{-1,1,3,33,2,8,10,44};
        int[] arr4 = new int[]{-1,5,44,77,33,48,54,95,22,34,45,57,53,70,85,98};

        System.out.println("arr1 valid: " + isValid(arr1));  // expected: true
        System.out.println("arr2 valid: " + isValid(arr2));  // expected: true
        System.out.println("arr3 valid: " + isValid(arr3));  // expected: false
        System.out.println("arr4 valid: " + isValid(arr4));  // expected: false
    }
}
