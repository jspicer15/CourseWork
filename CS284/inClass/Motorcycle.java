public class Motorcycle implements Informative
{
	private String make;
	private String model;
	private short year;

	public Motorcycle (String ma, String mo, short y)
	{
		make = ma;
		model = mo;
		year = y;
	}

	public Motorcycle ()
	{
		make = "Harley Davidson";
		model = "Fat Boy Lo";
		year = 2012;
	}

	public String toString()
	{
		return "My cool bike: " + year + " " + make + " " + model;
	}

	public void getInfo()
	{
		System.out.println(this.toString());
	}

}