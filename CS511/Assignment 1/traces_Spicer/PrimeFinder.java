/*
	@author John Spicer
*/

import java.util.List;
import java.util.ArrayList;

public class PrimeFinder implements Runnable
{
	private Integer start;
	private Integer end;
	private List<Integer> primes;

	PrimeFinder(Integer startNum, Integer endNum)
	{
		this.start = startNum;
		this.end = endNum;
		this.primes = new ArrayList<Integer>();
	}

	public List<Integer> getPrimesList()
	{
		return this.primes;
	}

	public Boolean isPrime(int n)
	{
		if (n % 2 == 0)
			return false;
    
    		for(int i = 3; i * i <= n; i += 2)
		{
        		if(n % i == 0)
            			return false;
    		}
   
		return true;
	}

	public void run()
	{
		for (int i = start; i < end; i++)
			if (isPrime(i))
				primes.add(new Integer(i));
	}
}
