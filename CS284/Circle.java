// @author John Spicer
public class Circle extends Shape
{
	private int radius;
	
	// @param r length to set to the radius of the Circle
	public Circle(int r)
	{
		if( r <= 0 )
			r = 1;
		radius = r;
	}

	public Circle() 
	{
		radius = 1;
	}

	// @return radius of the Circle
	public int getRadius()
	{
		return radius;
	}

	/*
	@param r length to set to the radius of the Circle
	@return true if r is greater than 0
	*/
	public boolean setRadius(int r)
	{
		if(r <= 0)
			return false;
		radius = r;
		return true;
	}
	
	// @return area of the Circle
	public double area()
	{	
		return (3.14159 * radius * radius);
	}

	// @return perimeter of the Circle
	public double perimeter()
	{
		return 2 * 3.14159 * radius;
	}

	public void shortPrint()
	{
		System.out.println("Radius: " + getRadius() + ", Area: " + area() + ", Perimeter: " + perimeter() );
	}

	public void longPrint()
	{
		System.out.println("The Radius is " + getRadius() + "\n The Area is " + area() + "\n The Perimeter is " + perimeter() ) ;
	}
	
	// @return String of the Circle's data
	public String toString()
	{
		return "Circle with Radius: " + getRadius() + ", Area: " + area() + ", Perimeter: " + perimeter() ;
	}

	public static void main(String[] args)
	{
		Circle circle = new Circle(10);
		System.out.println("\n");
		System.out.println("Creating Circle(10)");
		System.out.println("\n");
		System.out.println("Expected 10 for radius, ~314.16 for area, ~62.83 for perimeter");
		circle.shortPrint();
		System.out.println("\n");
		System.out.println("Setting radius to 8, expected true");
		System.out.println(circle.setRadius(8));
		System.out.println("\n");
		System.out.println("Expected 8 for Radius, ~201.06 for area, ~50.27 for perimeter");
		circle.shortPrint();
		System.out.println("\n");

		Circle small = new Circle();

		System.out.println("Creating Circle()");
		System.out.println("\n");
		System.out.println("Expected 1 for radius, 3.14159 for area, ~6.28 for perimeter");
		small.longPrint();
		System.out.println("\n");
		System.out.println("Setting radius to 0, expected false");
		System.out.println(small.setRadius(0));
		System.out.println("\n");
		System.out.println(small.toString());
	}
}
