import org.junit.AfterClass;
import org.junit.FixMethodOrder;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.Timeout;
import static org.junit.Assert.*;
import static org.junit.runners.MethodSorters.NAME_ASCENDING;
@FixMethodOrder(NAME_ASCENDING)
public class ArrayListTest {

    private static final ScoringTestRule SCORING_TEST_RULE = new ScoringTestRule();

    @Rule
    public ScoringTestRule scoringTestRule = SCORING_TEST_RULE;

    @Rule
    public Timeout globalTimeOut = Timeout.seconds(15);


    @AfterClass
    public static void printScore() {
        System.out.println();
        System.out.println("ArrayList: " + SCORING_TEST_RULE.getPoints() + " /" + SCORING_TEST_RULE.getTotal() + " points");
        System.out.println("Note that 2 points are NOT included in these tests:");
        System.out.println("2 points for updating and using isSorted");
        System.out.println();
    }

    @Test
    public void TestAccidentalJavaLink() throws Exception {
        // Only the Java STL ArrayList should every implement Collection!
        List<String> studentList = new ArrayList<>();
        assertFalse("Test suite is linked to the Java library ArrayList", studentList instanceof java.util.Collection);
    }

    @Test
    @SuppressWarnings("all")    // studentList instanceof List always true suppressed
    public void TestImplementsList() throws Exception {
        ArrayList<String> studentList = new ArrayList<>();
        assertTrue("ArrayList doesn't implement List", studentList instanceof List);
    }

    @Test
    public void TestIndexOfUsingEquals() throws Exception {
        ArrayList<String> arr = new ArrayList<String>();
        String s1 = "horse";
        String s2 = new String("horse");
        arr.add(s1);

        assertEquals("Check to see if they are using == in indexOf", arr.indexOf(s1), arr.indexOf(s2));
    }

    @Test
    @WorthPoints(points = 1)
    public void addObjectReturnTrueTest() {
        List<String> arr = new ArrayList<String>();
        for (int i = 0; i < 18; i++)
            assertTrue(arr.add("cat" + i));
    }

    @Test
    @WorthPoints(points = 1)
    public void addNullReturnFalseTest() {
        List<String> arr = new ArrayList<String>();
        assertFalse(arr.add(null));
        arr.add("cat");
        assertFalse(arr.add(null));
    }

    @Test
    @WorthPoints(points = 2)
    public void addObjectCorrectlyTest() {
        List<String> arr = new ArrayList<String>();
        for (int i = 0; i < 18; i++)
            assertTrue(arr.add("cat" + i));
        assertEquals(arr.get(17), "cat17");
        assertEquals(arr.get(10), "cat10");
        assertEquals(arr.get(5), "cat5");
    }

    @Test
    @WorthPoints(points = 1)
    public void addIndexOutOfBoundsTest() { //depends on add()
        List<String> arr = new ArrayList<String>();
        assertFalse(arr.add(0, "fish"));
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertFalse(arr.add(-1, "fish"));
        assertFalse(arr.add(24, "fish"));
        assertFalse(arr.add(3, "fish"));
        assertFalse(arr.add(4, "fish"));
    }

    @Test
    @WorthPoints(points = 2)
    public void addAtBeginningTest() { //depends on add()
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertTrue(arr.add(0, "fish"));
        assertEquals(arr.get(0), "fish");
        assertTrue(arr.add(0, "lizard"));
        assertEquals(arr.get(0), "lizard");
        assertEquals(arr.get(1), "fish");
    }

    @Test
    @WorthPoints(points = 2)
    public void addAtMiddleAndEndTest() {//depends on get, add
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertTrue(arr.add(1, "fish"));
        assertEquals(arr.get(1), "fish");
        assertTrue(arr.add(3, "lizard"));
        assertEquals(arr.get(3), "lizard");
        assertEquals(arr.get(4), "snake");
    }

    @Test
    @WorthPoints(points = 1)
    public void addIndexNullReturnFalseTest() {//depends on add()
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertFalse(arr.add(0, null));
        assertFalse(arr.add(1, null));
    }

    @Test
    @WorthPoints(points = 1)
    public void clearNonEmptySetTest() { //depends on add, get
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.clear();
        assertNull(arr.get(0));
        arr.add("fish");
        arr.clear();
        assertNull(arr.get(0));
    }

    @Test
    @WorthPoints(points = 1)
    public void clearEmptySetTest() { //requires get
        List<String> arr = new ArrayList<String>();
        arr.clear();
        assertNull(arr.get(0));
    }

    @Test
    @WorthPoints(points = 1)
    public void getOutOfBoundsTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertNull(arr.get(-1));
        assertNull(arr.get(24));
        assertNull(arr.get(3));
    }

    @Test
    @WorthPoints(points = 2)
    public void getInBoundsTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertEquals(arr.get(0), "cat");
        assertEquals(arr.get(1), "dog");
        assertEquals(arr.get(2), "snake");
    }

    @Test
    @WorthPoints(points = 1)
    public void indexOfNotPresentTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertEquals(arr.indexOf("horse"), -1);
        assertEquals(arr.indexOf("fish"), -1);
        assertEquals(arr.indexOf(null), -1);
    }

    @Test
    @WorthPoints(points = 2)
    public void indexOfPresentTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.add("cat");
        assertEquals(arr.indexOf("cat"), 0);
        assertEquals(arr.indexOf("snake"), 2);
        assertEquals(arr.indexOf("dog"), 1);
    }

    @Test
    @WorthPoints(points = 1)
    public void emptyTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        assertTrue(arr.isEmpty());
        arr.add("cat");
        assertFalse(arr.isEmpty());
    }

    @Test
    @WorthPoints(points = 1)
    public void lastindexOfPresentTest()//requires add
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.add("cat");
        assertEquals(arr.indexOf("cat"), 0);
        assertEquals(arr.indexOf("snake"), 2);
        assertEquals(arr.indexOf("dog"), 1);
    }

    @Test
    @WorthPoints(points = 1)
    public void sizeTest()//requires add, clear
    {
        List<String> arr = new ArrayList<String>();
        assertEquals(arr.size(), 0);
        arr.add("cat");
        assertEquals(arr.size(), 1);
        arr.add("dog");
        assertEquals(arr.size(), 2);
        arr.clear();
        assertEquals(arr.size(), 0);
    }

    @Test
    @WorthPoints(points = 1)
    public void forwardSortTest()//requires add, get
    {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.add("tiger");
        arr.add("elephant");
        arr.add("dragon");
        arr.add("horse");
        arr.add("snake");
        arr.sort();
        assertEquals(arr.get(0), "cat");
        assertEquals(arr.get(1), "dog");
        assertEquals(arr.get(2), "dragon");
        assertEquals(arr.get(3), "elephant");
        assertEquals(arr.get(4), "horse");
        assertEquals(arr.get(5), "snake");
        assertEquals(arr.get(6), "snake");
        assertEquals(arr.get(7), "tiger");
    }

    @Test
    @WorthPoints(points = 1)
    public void sortForwardFromBackwardTest()//requires add, get
    {
        List<String> arr = new ArrayList<String>();
        arr.add("tiger");
        arr.add("snake");
        arr.add("snake");
        arr.add("horse");
        arr.add("elephant");
        arr.add("dragon");
        arr.add("dog");
        arr.add("cat");
        arr.sort();
        assertEquals(arr.get(0), "cat");
        assertEquals(arr.get(1), "dog");
        assertEquals(arr.get(2), "dragon");
        assertEquals(arr.get(3), "elephant");
        assertEquals(arr.get(4), "horse");
        assertEquals(arr.get(5), "snake");
        assertEquals(arr.get(6), "snake");
        assertEquals(arr.get(7), "tiger");
    }

    @Test
    @WorthPoints(points = 1)
    public void removeIndexOutOfBoundsTest() {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertNull(arr.remove(3));
        assertNull(arr.remove(-1));
        assertNull(arr.remove(12));
    }

    @Test
    @WorthPoints(points = 1)
    public void removeIndexReturnsObjectTest() {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        assertEquals(arr.remove(0), "cat");
        assertEquals(arr.remove(1), "snake");
        assertEquals(arr.remove(0), "dog");
    }

    @Test
    @WorthPoints(points = 1)
    public void removeIndexRemovesObjectTest() {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.remove(0);
        assertEquals(arr.get(0), "dog");
        arr.remove(0);
        assertEquals(arr.get(0), "snake");
        arr.remove(0);
        assertNull(arr.get(0));
    }

    @Test
    @WorthPoints(points = 1)
    public void removeIndexRemovesObjectTest2() {
        List<String> arr = new ArrayList<String>();
        arr.add("cat");
        arr.add("dog");
        arr.add("snake");
        arr.add("snake");
        arr.add("horse");
        arr.add("tiger");
        arr.remove(5);
        assertNull(arr.get(5));
        arr.remove(1);
        assertEquals(arr.get(1), "snake");
        assertEquals(arr.get(2), "snake");

    }

    @Test
    @WorthPoints(points = 1)
    public void greaterThanTest() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.greaterThan(5);
        assertEquals(arr.size(), 4);
        assertEquals((int)arr.get(0), 6);
        assertEquals((int)arr.get(1), 6);
        assertEquals((int)arr.get(2), 7);
        assertEquals((int)arr.get(3), 101);
    }

    @Test
    @WorthPoints(points = 1)
    public void greaterThanTest2() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.greaterThan(-102);
        assertEquals(arr.size(), 16);
        assertEquals((int)arr.get(0), -101);
        assertEquals((int)arr.get(1), -40);
        assertEquals((int)arr.get(2), -1);
        assertEquals((int)arr.get(3), 0);
        assertEquals((int)arr.get(4), 2);
        assertEquals((int)arr.get(5), 2);
        assertEquals((int)arr.get(6), 3);
        assertEquals((int)arr.get(7), 3);
        assertEquals((int)arr.get(8), 3);
        assertEquals((int)arr.get(9), 4);
        assertEquals((int)arr.get(10), 5);
        assertEquals((int)arr.get(11), 5);
        assertEquals((int)arr.get(12), 6);
        assertEquals((int)arr.get(13), 6);
        assertEquals((int)arr.get(14), 7);
        assertEquals((int)arr.get(15), 101);
    }

    @Test
    @WorthPoints(points = 1)
    public void greaterThanTest3() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.greaterThan(101);
        assertEquals(arr.size(), 0);
    }

    @Test
    @WorthPoints(points = 1)
    public void greaterThanRandomTest() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(100);
        arr.add(50);
        arr.add(-25);
        arr.add(22);
        arr.greaterThan(10);
        assertEquals(arr.size(), 3);
        assertEquals((int)arr.get(0), 100);
        assertEquals((int)arr.get(1), 50);
        assertEquals((int)arr.get(2), 22);
    }

    @Test
    @WorthPoints(points = 1)
    public void lessThanTest() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.lessThan(2);
        assertEquals(arr.size(), 4);
        assertEquals((int)arr.get(0), -101);
        assertEquals((int)arr.get(1), -40);
        assertEquals((int)arr.get(2), -1);
        assertEquals((int)arr.get(3), 0);
    }

    @Test
    @WorthPoints(points = 1)
    public void lessThanTest2() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.lessThan(102);
        assertEquals(arr.size(), 16);
        assertEquals((int)arr.get(0), -101);
        assertEquals((int)arr.get(1), -40);
        assertEquals((int)arr.get(2), -1);
        assertEquals((int)arr.get(3), 0);
        assertEquals((int)arr.get(4), 2);
        assertEquals((int)arr.get(5), 2);
        assertEquals((int)arr.get(6), 3);
        assertEquals((int)arr.get(7), 3);
        assertEquals((int)arr.get(8), 3);
        assertEquals((int)arr.get(9), 4);
        assertEquals((int)arr.get(10), 5);
        assertEquals((int)arr.get(11), 5);
        assertEquals((int)arr.get(12), 6);
        assertEquals((int)arr.get(13), 6);
        assertEquals((int)arr.get(14), 7);
        assertEquals((int)arr.get(15), 101);
    }

    @Test
    @WorthPoints(points = 1)
    public void lessThanTest3() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.lessThan(-101);
        assertEquals(arr.size(), 0);
    }

    @Test
    @WorthPoints(points = 1)
    public void lessThanRandomTest() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(100);
        arr.add(50);
        arr.add(-25);
        arr.add(22);
        arr.lessThan(10);
        assertEquals(arr.size(), 2);
        assertEquals((int)arr.get(0), -101);
        assertEquals((int)arr.get(1), -25);
    }

    @Test
    @WorthPoints(points = 1)
    public void equalToTest() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.equalTo(5);
        assertEquals(arr.size(), 2);
        assertEquals((int)arr.get(0), 5);
        assertEquals((int)arr.get(1), 5);
    }

    @Test
    @WorthPoints(points = 1)
    public void equalToTest2() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.equalTo(101);
        assertEquals(arr.size(), 1);
        assertEquals((int)arr.get(0), 101);
    }

    @Test
    @WorthPoints(points = 1)
    public void equalToTest3() {
        List<Integer> arr = new ArrayList<Integer>();
        arr.add(-101);
        arr.add(-40);
        arr.add(-1);
        arr.add(0);
        arr.add(2);
        arr.add(2);
        arr.add(3);
        arr.add(3);
        arr.add(3);
        arr.add(4);
        arr.add(5);
        arr.add(5);
        arr.add(6);
        arr.add(6);
        arr.add(7);
        arr.add(101);
        arr.equalTo(50);
        assertEquals(arr.size(), 0);
    }
}