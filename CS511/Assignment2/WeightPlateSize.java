/*
	@author: John Spicer && Michael Osorio && Sam Pelton
*/
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;

public enum WeightPlateSize
{
	SMALL_3KG,
	MEDIUM_5KG,
	LARGE_10KG;

	private static WeightPlateSize wpSize;
	private static List<WeightPlateSize> VALUES = Collections.unmodifiableList(Arrays.asList(values()));
  	private static int SIZE = VALUES.size();
  	private static Random RANDOM = new Random();
		
	public static WeightPlateSize randomSize()
	{
  		wpSize = VALUES.get(RANDOM.nextInt(SIZE));
  		return wpSize;
	}

	public static List<WeightPlateSize> getVals()
	{
		return VALUES;
	}
}