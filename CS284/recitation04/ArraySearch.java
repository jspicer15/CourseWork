package recitation04;

public class ArraySearch
{
	public static int search(int[]x, int target)
	{
		for(int i = 0; i < x.length; i++)
		{
			if (x[i] == target)
				return i;
		}		
		return -1;
	}

	public static void main(String[] args)
	{
		int[] arr = new int[]{0,2,3,4,5,8,10};
		int answer= search(arr, 5);
		System.out.println(answer);
	}
}
