/*
	@author: John Spicer && Michael Osorio && Sam Pelton
*/
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Semaphore;
import java.util.Set;
import java.util.concurrent.Executors;
import java.util.HashSet;
import java.util.Arrays;
import java.util.Random;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class Gym implements Runnable
{
	private static int counter = 0;
	private static int routineCounter = 0;
	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private static Map<WeightPlateSize,Integer> noOfWeightPlates = new LinkedHashMap<WeightPlateSize,Integer>();
	private Set<Integer> clients;
	private Client[] clientele;
	private ExecutorService executor = Executors.newFixedThreadPool(30);

	private Semaphore[] machines = new Semaphore [] {new Semaphore(1), new Semaphore(1), 
		new Semaphore(1), new Semaphore(1), new Semaphore(1), new Semaphore(1), 
		new Semaphore(1), new Semaphore(1)};
	private Semaphore[] freeWeights = new Semaphore [] {new Semaphore(40), new Semaphore(30),
		new Semaphore(20)}; // [LARGE, MEDIUM, SMALL] (same as noOfWeightPlates)

	private Random RANDOM = new Random();

	public Gym()
	{

	}

	public void run()
	{
		int[] ids = new int[10000];
		Client[] clientele = new Client[10000];

		for (int i = 0; i < 10000; i++)
		{
			ids[i] = i;
			clientele[i] = new Client(i);
		}

		clients = new HashSet(Arrays.asList(ids));

		for (int i = 0; i < 10000; i++)
		{
			noOfWeightPlates.clear();
			noOfWeightPlates.put(WeightPlateSize.getVals().get(0), RANDOM.nextInt(20));
			noOfWeightPlates.put(WeightPlateSize.getVals().get(1), RANDOM.nextInt(20));
			noOfWeightPlates.put(WeightPlateSize.getVals().get(2), RANDOM.nextInt(20));
	
			for (int j = 0; j < RANDOM.nextInt(10); j++)
			{
				clientele[i].addExercise(Exercise.generateRandom(noOfWeightPlates));
			}
		}

		executor.execute(new Runnable()	
		{
			public void run() 
			{
				routineCounter = 0;
				while (counter < 10000)
				{

					for (int k = 0; k < 8; k++)
					{
						if (clientele[counter].getRoutine().size() > routineCounter)
						{
							if (clientele[counter].getRoutine().get(routineCounter).getAt() == ApparatusType.VALUES.get(k))
							{
								try 
								{
									machines[k].acquire();

									for (int j = 0; j < 3; j++)
									{
										freeWeights[j].acquire(clientele[counter].getRoutine().get(routineCounter).getPlates().get(WeightPlateSize.getVals().get(0)));
									}

									for (int j = 0; j < 3; j++)
									{
										freeWeights[j].release(clientele[counter].getRoutine().get(routineCounter).getPlates().get(WeightPlateSize.getVals().get(0)));
									}

									routineCounter++;

									machines[k].release();
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
							}
						}
					}
					counter++;								
				}
				executor.shutdown();
			}
		});
		executor.shutdown();
	}
}