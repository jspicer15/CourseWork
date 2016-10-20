import java.lang.Math;
// @author John Spicer
public class Triangle extends Shape
{
	private int side1;
	private int side2;
	private int side3;
	/*
	@param a length of side1
	@param b length of side2
	@param c length of side3
	*/
	public Triangle(int a, int b, int c)
	{
		if(a <= 0 )
			a = 1;
		side1 = a;
		if(b <= 0 )
			b = 1;
		side2 = b;
		if(c <= 0 )
			c = 1;
		side3 = c;
	}	

	public Triangle()
	{
		side1 = 1;
		side2 = 1;
		side3 = 1;
	}

	/*
	@param a length to set to side1
	@param b length to set to side2
	@param c length to set to side3
	@return true if a b and c are all greater than 0
	*/
	public boolean setSides(int a, int b, int c)
	{
		if(a <= 0 || b <= 0 || c <= 0)
			return false;
		side1 = a;
		side2 = b;
		side3 = c;
		return true;
	}

	// @return length of side1
	public int getSide1()
	{
		return side1;
	}

	// @return length of side2
	public int getSide2()
	{
		return side2;
	}

	// @return length of side3
	public int getSide3()
	{
		return side3;
	}

	/* 
	@param s length to set to side1
	@return true if s if greater than 0
	*/
	public boolean setSide1(int s)
	{
		if(s <= 0)
			return false;
		side1 = s;
		return true;
	}

	/* 
	@param s length to set to side2
	@return true if s if greater than 0
	*/
	public boolean setSide2(int s)
	{
		if(s <= 0)
			return false;
		side2 = s;
		return true;
	}

	/* 
	@param s length to set to side3
	@return true if s if greater than 0
	*/
	public boolean setSide3(int s)
	{
		if(s <= 0)
			return false;
		side3 = s;
		return true;
	}

	// @return area of the Triangle
	public double area()
	{
		return .25 * Math.sqrt((perimeter() * (perimeter() - side1) * (perimeter() - side2) * (perimeter() - side3)));
	}

	// @return perimeter of the Triangle
	public double perimeter()
	{
		return side1 + side2 + side3;
	}
	
	public void shortPrint()
	{
		System.out.println("Side1: " + side1 + ", Side2: " + side2 + ", Side3: " + side3 + ", Area: " + area() + ", Perimeter: " + perimeter() );
	}

	public void longPrint()
	{
		System.out.println("Side1 is " + side1 + "\nSide2 is " + side2 + "\nSide3 is " + side3 + "\nThe Area is " + area() + "\nThe Perimeter is " + perimeter() ) ;
	}

	// @return string of the Triangle's data
	public String toString()
	{
		return "Triangle with Side1: " + side1 + ", Side2: " + side2 + ", Side3: " + side3 + ", Area: " + area() + ", Perimeter: " + perimeter() ;
	}

	public static void main(String[] args)
	{
		Triangle tri = new Triangle(2,3,5);
		System.out.println("\n");
		System.out.println("Creating Triangle(2,3,5)");
		System.out.println("\n");
		System.out.println("Expected 2 for Side1, 3 for side 2, 5 for side 3, ~13.23 for area, 10.0 for perimeter");
		tri.shortPrint();
		System.out.println("\n");
		System.out.println("Setting side1 to 3, side2 = 4, side3 = 5, expected true");
		System.out.println(tri.setSides(3,4,5));
		System.out.println("\n");
		System.out.println("Expected 3 for Side1, 4 for side 2, 5 for side 3, ~19.44 for area, 12.0 for perimeter");
		tri.shortPrint();
		System.out.println("\n");

		Triangle small = new Triangle();

		System.out.println("Creating Triangle()");
		System.out.println("\n");
		System.out.println("Expected 1 for side1, 1 for side2, 1 for side3, ~1.22 for area, 3.0 for perimeter");
		small.longPrint();
		System.out.println("\n");
		System.out.println("Setting Side1 to 0, expected false");
		System.out.println(small.setSide1(0));
		System.out.println("\n");
		System.out.println("Setting Side2 to -10, expected false");
		System.out.println(small.setSide2(-10));
		System.out.println("\n");
		System.out.println("Setting Side3 to -1, expected false");
		System.out.println(small.setSide3(-1));
		System.out.println("\n");
		System.out.println(small.toString());
	}
}
