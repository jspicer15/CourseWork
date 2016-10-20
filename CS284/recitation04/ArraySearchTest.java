package recitation04;

import org.junit.Test;
import static org.junit.Assert.*;


/** 
 * Tester for ArraySearch class
 * @author Sadia Akhter
 */
public class ArraySearchTest {
	// array to search
	private int[] x = {5, 12, 15, 4, 8, 12, 7};
	
	@Test
	public void firstElementTest() {
		assertEquals(0, ArraySearch.search(x, 5));
	}
	
	@Test
	public void lastElementTest() {
		assertEquals(6, ArraySearch.search(x, 7));
	}
	
	@Test
	public void notInArrayTest() {
		assertEquals(-1, ArraySearch.search(x, -5));
	}
	
	@Test
	public void multipleOccurrenceTests() {
		assertEquals(1, ArraySearch.search(x, 12));
	}
	
	@Test
	public void inMiddleTest() {
		assertEquals(3, ArraySearch.search(x, 4));
	}
	
	@Test
	public void oneElementArrayTest() {
		int[] y = {10};
		assertEquals(0, ArraySearch.search(y, 10));
		assertEquals(-1, ArraySearch.search(y, -10));
	}
	
	@Test
	public void emptyArrayTest() {
		int[] y = new int[0];
		assertEquals(-1, ArraySearch.search(y, 10));
	}
	
}
