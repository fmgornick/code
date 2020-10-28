public class SparseVector {

	private Node head;
	private int length;

	public SparseVector(int len){
		head = null;
		length = len;
	}

	// Prints out a sparse vector (including zeros)
	public String toString(){

		String result = "";
		Node currNode = head;
		int currIndex = 0;
		while( currNode != null ){
			int idx = currNode.getIndex();

			// Pad the space between nodes with zero
			while( currIndex < idx ){
				result += "0, ";
				currIndex++;
			}
			result += currNode;
			currNode = currNode.getNext();
			currIndex++;

			// Only add a comma if this isn't the last element
			if( currNode != null ){ result += ", "; }
		}
		return result;
	}

	// TODO: Implement me for milestone 1
	public void addElement(int index, double value){
        if (index >= 0 && index < length) {
            if (head == null) {
                head = new Node(index, value);
            }

            else {
                Node currNode = head;
                while (currNode.getNext() != null) {
                    currNode = currNode.getNext();
                }
                if (currNode.getIndex() < index) {
                    currNode.setNext(new Node(index, value));
                }
            }
        }
	}

	// TODO: Implement me for milestone 3
	public static double dot( SparseVector x, SparseVector y ){
        double sum = 0;
        if (x.length == y.length && x.head != null && y.head != null) {
            Node xNode = x.head;
            Node yNode = y.head;
            while (xNode != null && yNode != null) {
                if (xNode.getIndex() < yNode.getIndex()) {
                    xNode = xNode.getNext();
                }
                else if (xNode.getIndex() > yNode.getIndex()) {
                    yNode = yNode.getNext();
                }
                else {
                    sum += xNode.getValue() * yNode.getValue();
                    xNode = xNode.getNext();
                    yNode = yNode.getNext();
                }
            }
        }
        return sum;
	}


	// TODO: Test out your code here!
    public static void main(String[] args) {
        SparseVector vec = new SparseVector(6);
        vec.addElement(0,10);
        vec.addElement(3,-1.1);
        vec.addElement(5,32);

        System.out.println("Milestone 1:");
        System.out.println(vec);
        System.out.println();

        SparseVector x = new SparseVector(100000000); 
        x.addElement(0, 1.0);
        x.addElement(10000000, 3.0); 
        x.addElement(10000001, -2.0);
        SparseVector y = new SparseVector(100000000); 
        y.addElement(0, 2.0);
        y.addElement(10000001, -4.0);
        double result = dot(x, y); 

        System.out.println("Milestone 3:");
        System.out.println(result);

    }
}


