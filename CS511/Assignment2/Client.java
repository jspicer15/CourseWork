/*
	@author: John Spicer && Michael Osorio && Sam Pelton
*/
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import java.util.ArrayList;

public class Client
{
	private int id;
	private static List<Exercise> routine;

	public Client(int id)
	{
		this.id = id;
		this.routine = new ArrayList<Exercise>();
	}

	public void addExercise(Exercise e)
	{
		this.routine.add(e);
	}

	public static Client generateRandom(int id)
	{
		Client client = new Client(id);
		return client;
	}

	public List<Exercise> getRoutine()
	{
		return this.routine;
	}
}

