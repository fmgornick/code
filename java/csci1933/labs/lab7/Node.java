public class Node {
	private Node next;
	private int index;
	private double value;

	public Node(int idx, double val){
		index = idx;
		value = val;
		next = null;
	}

	public double getValue(){ return value; }
	public int getIndex(){ return index; }

	public Node getNext(){ return next; }
	public void setNext( Node other ){ next = other; }

	public String toString(){ return ""+value; }
}
