public class StudentWorker
{
	private Student s;
	private Worker w;

	public StudentWorker(String n, short a, int c, String e)
	{
		s = new Student(n, a, c);
		w = new Worker(n, a, e);
	}

	public String getEmployer()
	{
		return w.getEmployer();
	}

	public int getCWID()
	{
		return s.getCWID();
	}

}