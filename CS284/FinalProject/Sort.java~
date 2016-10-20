/*
	@author John Spicer
*/
import java.io.IOException;

public class Sort 
{
	public static MyPriorityQueue[] lines;

	private static void swap(Object[] arr, int x, int y) 
	{
        	if (x != y) 
		{
            		Object temp = arr[x];
            		arr[x] = arr[y];
            		arr[y] = temp;
		}
        }

    	private static void insert(TSA[] arr, int n, int s, int incr) 
	{
        	int i, j;
                for (i = s + incr; i < n; i += incr) 
            		for (j = i; (j > s) && (arr[j].compareTo(arr[j-incr]) > 0); j -= incr)
                		swap(arr, j, j-incr);
        }
	
        /*
                @param arr: Array of TSA to sort with ShellSort
                @param n: Number of items in arr to sort
        */
    	public static void shell(TSA[] arr, int n) 
	{
        	int s, incr;
        	if(arr != null && n > 1)
                {
                        if(n > arr.length)
                                n = arr.length;

        		for (incr = n/2; incr < n; incr++) 
			{
            			for (s = 0; s < incr; s++)
                			insert(arr, n, s, incr);
        		}
        		insert(arr, n, 0, 1);
		}
    	}

	/*
		@return array of sorted TSA agents
	*/
	public static TSA[] sort() throws IOException 
	{
		TSA[] agentsArr = ReadFile.buildAgents();
		shell(agentsArr, agentsArr.length);
		return agentsArr;
	}
	
	/*
		@return array of priority queues
		@exception throws IOException if file not found
	*/
	public static MyPriorityQueue[] buildLines() throws IOException
	{
		Passenger[] passArr = ReadFile.buildPass();
		//System.out.println("pass length " + passArr.length);
		int agents = ReadFile.buildAgents().length;
		//System.out.println("number of agents " + agents);
		lines = new MyPriorityQueue[agents];

		for(int i = 0; i < lines.length; i++)
		{
			lines[i] = new MyPriorityQueue((int) Math.ceil((double)passArr.length / agents));
		}

		for(int i = 0; i < passArr.length; i++)
		{
		//	System.out.println("the getIndex of passArr " + passArr[i].getIndex());
			int index = passArr[i].getIndex() % agents;
		//	System.out.println("index " + index);
		//	System.out.println("if checking " + lines[index].getSize());
			//System.out.println("check cap " + ((int) Math.ceil((double)passArr.length/agents)));
			if((lines[index].getSize()) < ((int) Math.ceil((double)passArr.length/agents)))
			{
				//lines[index].parse();
				//System.out.println(i);
		//		System.out.println("inside index " + index);
				lines[index].enqueue(passArr[i]);
				//System.out.println(lines[index].getSize());
			}
			else
			{
				for(int j = 0; j < agents; j++)
				{
					if((lines[(passArr[i].getIndex() + j) % agents].getSize()) < ((int) Math.ceil((double)passArr.length/agents)))
					{
					//System.out.println(passArr[i].getIndex());
					//System.out.println(lines[index].getSize());
					//System.out.println((passArr[i].getIndex() + 1) % agents);
					//lines[(passArr[i].getIndex() + j) % agents].parse();
					lines[(passArr[i].getIndex() + j) % agents].enqueue(passArr[i]);
					}
				}
			}
		}
		return lines;
	}
	

/*		
	public static void main(String[] args) throws IOException
	{
		/*MyPriorityQueue[] lineQueue = buildLines();
		for(int i =0; i < lineQueue.length; i++)
			lineQueue[i].parse();
		
	}
*/
}
