/* 
	@author John Spicer 
*/
public class MySorts
{
        private static void swap(Object[] arr, int x, int y)
        {
                if(x != y)
                {
                        Object tmp = arr[x];
                        arr[x] = arr[y];
                        arr[y] = tmp;
                }
        }

	/*
		@param arr: Array of strings to sort with InsertionSort
		@param n: Number of items in arr to sort
	*/
	public static void insert(String[] arr, int n)
	{
		int i;
		int j;
		if(arr != null && n > 1)
		{
			if(n > arr.length)
				n = arr.length;
		

			for(i = 1; i < n; i++)
				for(j = i; j > 0 && arr[j].compareTo(arr[j-1]) < 0; j--)
					swap(arr, j, j-1);
		}
	}

    	private static void insert(String[] arr, int n, int s, int incr) 
	{
        	int i, j;
        	for (i = s + incr; i < n; i += incr)
            		for (j = i; (j > s) && (arr[j].compareTo( arr[j-incr]) < 0); j -= incr)
                swap(arr, j, j-incr);
        }
	
	/*
		@param arr: Array of strings to sort with QuickSort
		@param n: Number of items in arr to sort
	*/
	public static void quick(String[] arr, int n)
	{
        	if(arr != null && n > 1)
		{
			if(n > arr.length)
				n = arr.length;
        		quick(arr, 0, n-1);
		}
	}

	private static void quick(String[] arr, int l, int r)
	{
        	int p;
        	if(r - l < 5)
                	insert(arr, r + 1, l, 1);
        	else
        	{
                	p = findPivot(arr, l, r);
                	swap(arr, p, r);
                	p = partition(arr, l, r);
                	swap(arr, p, r);
                	quick(arr, l, p - 1);
                	quick(arr, p + 1, r);
        	}
	}

	private static int findPivot(String[] arr, int l, int r)
	{
        	return l + (r - l) / 2;
	}

	private static int partition(String[] arr, int l, int r)
	{
        	int i, j;
        	for(i = l, j = r - 1; i < j;)
        	{
                	for(; arr[i].compareTo(arr[r]) < 0; i++)
                        	;
                	for(; j > l && arr[j].compareTo(arr[r]) >= 0; j--)
                        	;
                	if(i < j)
                        	swap(arr, i++, j--);
        	}
		return i;
	}

    	private static void swap(int[] arr, int x, int y) 
	{
        	if (x != y) 
		{
            		int temp = arr[x];
            		arr[x] = arr[y];
            		arr[y] = temp;
		}
        }

    	private static void insert(int[] arr, int n, int s, int incr) 
	{
        	int i, j;
                for (i = s + incr; i < n; i += incr) 
            		for (j = i; (j > s) && (arr[j] < arr[j-incr]); j -= incr)
                		swap(arr, j, j-incr);
        }
	
        /*
                @param arr: Array of ints to sort with ShellSort
                @param n: Number of items in arr to sort
        */
    	public static void shell(int[] arr, int n) 
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


	private static void print(String[] arr)
	{
		int i;
		System.out.println("\n");
		for(i = 0; i < arr.length; i++)
			System.out.println(arr[i]);
		System.out.println("\n");
	}
    
        private static void print(int[] arr)
        {
                int i;
                System.out.println("\n");
                for(i = 0; i < arr.length; i++)
                        System.out.println(arr[i]);
                System.out.println("\n");
        }
	
	/*
		Testing
	*/
	public static void main(String[] args)
	{
		String[] myArr = {"goodbye", "a", "aaaaa","b","hello", "cat"};
		print(myArr);
		insert(myArr, 6);
		print(myArr);
	
		String[] nullArr = null;
		insert(nullArr, 6);

		String[] quickArr = {"john", "laramie", "dean", "mark", "sam"};
		print(quickArr);
		quick(quickArr, 5);
		print(quickArr);
		
		quick(nullArr, 6);
		
		int[] shellArr = {100, 65, 78, 45, 1000, 1};
		print(shellArr);
		shell(shellArr, 6);
		print(shellArr);


		int[] nullInt = null;
		shell(nullInt, 100);
	}
}
