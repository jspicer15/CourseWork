/*
	@author: John Spicer && Michael Osorio && Sam Pelton
*/
import java.util.Random;
import java.util.Map;

public class Exercise
{
	private static ApparatusType at;
	private static Map<WeightPlateSize,Integer> weight;
	private int duration;
	private static Random rand = new Random();

	public Exercise(ApparatusType at, Map<WeightPlateSize,Integer> weight, int duration)
	{
		this.at = at;
		this.weight = weight;
		this.duration = duration;
	}

	public static Exercise generateRandom(Map<WeightPlateSize,Integer> numberPlates)
	{
		Exercise excercise = new Exercise(ApparatusType.randomType(), numberPlates, rand.nextInt(100000) + 1);
		return excercise;
	}

	public ApparatusType getAt()
	{
		return this.at;
	}

	public Map<WeightPlateSize,Integer> getPlates()
	{
		return this.weight;
	}
}