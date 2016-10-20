/*
	@author: John Spicer && Michael Osorio && Sam Pelton
*/
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;

public enum ApparatusType 
{
	LEGPRESSMACHINE,
	BARBELL,
	HACKSQUATMACHINE,
	LEGEXTENSIONMACHINE,
	LEGCURLMACHINE, 
	LATPULLDOWNMACHINE, 
	PECDECKMACHINE,
	CABLECROSSOVERMACHINE;

	private static ApparatusType aType;
	public static List<ApparatusType> VALUES = Collections.unmodifiableList(Arrays.asList(values()));
  	private static int SIZE = VALUES.size();
  	private static Random RANDOM = new Random();
		
	public static ApparatusType randomType()
	{
  		aType = VALUES.get(RANDOM.nextInt(SIZE));
  		return aType;
	}
}