public class Worker extends Person
{
	private String employer;

	public Worker(String n, short a, String e)
	{
		super(n, a);
		employer = e;
	}

	public Worker()
	{
		employer = "McDonald's";
	}

	public String toString()
	{
		return "Worker: " + super.toString() + " employed by " + employer;
	}

	public String getEmployer()
	{
		return employer;
	}

	public void getInfo()
	{
		System.out.println(this.toString());
	}
		public static void main(String [] args)
	{
		Worker p = new Worker();
		Worker p2 = new Worker("Tom", (short)768, "SIT");
		Worker p3 = new Worker(null, (short)-2, "RFTGHJK");
		System.out.println(p.getName() + " " + p.getAge());
		System.out.println(p2.getName() + " " + p2.getAge());
		System.out.println(p3.getName() + " " + p3.getAge());
		if (p3.setName(""))
			System.out.println("Name Changed!");
		else
			System.out.println("Name NOT Changed!");
		if (p3.setAge((short)-5))
			System.out.println("age Changed!");
		else
			System.out.println("age NOT Changed!");
		System.out.println(p3.getName() + " " + p3.getAge());
		if (p3.setName("Bob"))
			System.out.println("Name Changed!");
		else
			System.out.println("Name NOT Changed!");
		if (p3.setAge((short)7))
			System.out.println("age Changed!");
		else
			System.out.println("age NOT Changed!");
		System.out.println(p3.getName() + " " + p3.getAge());
		p3.getInfo();
	}
}