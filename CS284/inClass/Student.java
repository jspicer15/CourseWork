public class Student extends Person
{
	private int cwid;

	public Student(String n, short a, int c)
	{
		super(n, a);
		cwid = c;
	}

	public Student()
	{
		cwid = 0;
	}

	public int getCWID()
	{
		return cwid;
	}

	public String toString()
	{
		return "Student: " + super.toString() + " CWID: " + cwid;
	}

	public void getInfo()
	{
		System.out.println(this.toString());
	}
		public static void main(String [] args)
	{
		Student p = new Student();
		Student p2 = new Student("Tom", (short)768, 23456);
		Student p3 = new Student(null, (short)-2, 45678);
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