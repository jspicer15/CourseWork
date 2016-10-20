/*
	@author John Spicer
*/

import java.util.List;
import java.util.ArrayList;

public class AssignmentOne
{
	private static List<Integer> results = new ArrayList<Integer>();

	public static  List<Integer> lprimes(List<Integer[]> intervals)
	{

		for (int i = 0; i < intervals.size(); i++)
		 {
		 	PrimeFinder primeF = new PrimeFinder(intervals.get(i)[0], intervals.get(i)[1]);
		 	Thread thr = new Thread(primeF);
		 	thr.start();

		 	try 
			{
		 		thr.join();
		 	} catch (InterruptedException e) {
      				e.printStackTrace();
      			}

      			List<Integer> primeList = primeF.getPrimesList();

      			for (int j = 0; j < primeList.size(); j++)
      			{
				results.add(new Integer(primeList.get(j)));
      			}
		 }

		return results;
	}

	public static void main(String[] args)
	{
		List<Integer[]> intervals = new ArrayList<Integer[]>();
		List<Integer> printable;
		int i = 0;

		for (i = 0; i < args.length - 1; i++)
		{
		 	intervals.add(new Integer[]{Integer.valueOf(args[i]), Integer.valueOf(args[i + 1])});
		}

		System.out.print("[");
		printable = lprimes(intervals);

		for (i = 0; i < printable.size() - 1; i++)
		{
			System.out.print(printable.get(i));
			System.out.print(",");
		}

		System.out.print(printable.get(i));
		System.out.println("]");
	}
}
