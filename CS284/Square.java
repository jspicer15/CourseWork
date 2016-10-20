// @author John Spicer
public class Square extends Rectangle  
{	
	// @param s side length of the square
	public Square(int s)
	{
		super(s,s);
	}
	
	public Square()
	{
		super();
	}
	
	// @return side length of the square
	public int getSide()
	{
		return getBase();
	}
	
	/*
	@param s length to set the side of the square to
	@return true if s greater than 0
	*/
	public boolean setSide(int s)
	{
		if (setBase(s) && setHeight(s) && true)
			return true;
		return false;
	}

	public void shortPrint()
	{
		System.out.println("Side: " + getSide() + ", Area: " + area() + ", Perimeter: " + perimeter() );
	}

	public void longPrint()
	{
		System.out.println("The Side is " + getSide() + "\nThe Area is " + area() + "\nThe Perimeter is " + perimeter() ) ;
	}

	// @return String of the Square's data
	public String toString()
	{
		return "Square with Side: " + getSide() + ", Area: " + area() + ", Perimeter: " + perimeter() ;
	}

	public static void main(String[] args)
	{
		Square square = new Square(4);
		System.out.println("\n");
		System.out.println("Creating Square(4)");
		System.out.println("\n");
		System.out.println("Expected 4 for Side, 16.0 for area, 16.0 for perimeter");
		square.shortPrint();
		System.out.println("\n");
		System.out.println("Setting side to 3, expected true");
		System.out.println(square.setSide(3));
		System.out.println("\n");
		System.out.println("Expected 3 for Side, 9.0 for area, 12.0 for perimeter");
		square.shortPrint();
		System.out.println("\n");

		Square small = new Square();

		System.out.println("Creating Square()");
		System.out.println("\n");
		System.out.println("Expected 1 for side, 1.0 for area, 4.0 for perimeter");
		small.longPrint();
		System.out.println("\n");
		System.out.println("Setting Side to 0, expected false");
		System.out.println(small.setSide(0));
		System.out.println("\n");
		System.out.println(small.toString());
	}
}
