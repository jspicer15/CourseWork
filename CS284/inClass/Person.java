public abstract class Person implements Informative
{
	protected String name;
	protected short age;

	public Person(String n, short a)
	{
		if (n != null)
			name = n;
		else
			name = "You're an idiot";
		if (a >= 0)
			age = a;
		else
			age = 0;
	}

	public Person()
	{
		name = "Chewbacca";
		age = 147;
	}

	public String getName()
	{
		return name;
	}

	public short getAge()
	{
		return age;
	}

	public boolean setName(String n)
	{
		if (n == null || n.equals(""))
			return false;
		name = n;
		return true;
	}

	public String toString()
	{
		return name + " " + age + " years old.";
	}

	public boolean setAge(short a)
	{
		if (a < 0)
			return false;
		age = a;
		return true;
	}
/*
	public static void main(String [] args)
	{
		Person p = new Person();
		Person p2 = new Person("Tom", (short)768);
		Person p3 = new Person(null, (short)-2);
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

	}
	*/
}