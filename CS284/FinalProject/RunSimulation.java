/*
	@author John Spicer
*/
import java.io.IOException;

public class RunSimulation
{
	/*
		@param agent: TSA agent to check likes and dislikes
	*/
	public static boolean checkPass(TSA agent, Passenger pass)
	{
		int[] dislikes = agent.getDislikes();
		int[] likes = agent.getLikes();
		int dangLev = pass.getDangerLevel();

		for(int i = 0; i < dislikes.length; i++)
		{
			//System.out.println(dislikes[i]);
			//System.out.println(pass.getOrigin());
			if(dislikes[i] == pass.getOrigin())
				dangLev+= 2;
			if(dislikes[i] == pass.getSpecies())
				dangLev+= 2;
			if(dislikes[i] == pass.getGender())
				dangLev+= 2;
		}

		for(int i = 0; i < likes.length; i++)
		{
			if(likes[i] == pass.getOrigin())
				dangLev-= 2;
			if(likes[i] == pass.getSpecies())
				dangLev-= 2;
			if(likes[i] == pass.getGender())
				dangLev-= 2;
		}
	
		if(dangLev >= 10 - agent.getParanoia())
			return true;
		return false;
	}

	/*
		Main file to run simulation
		@exception throws IOException if file not found
	*/
	public static void main(String[] args) throws IOException
	{
		TSA[] agentArr = Sort.sort();
		MyPriorityQueue[] lines = Sort.buildLines();
		
		for(int i = 0; i < agentArr.length; i++)
		{
			int sizeLines = lines[i].getSize();
			for(int j = 0; j < sizeLines; j++)
			{
				//System.out.println(lines[i].getSize());
				if(j == 0)
					System.out.println(agentArr[i].toString() + " gets assigned to line " + i + "\n");
				//System.out.println(lines[i].peek().getIsThreat());
				if((checkPass(agentArr[i], lines[i].peek())) && (lines[i].peek().getIsThreat() == 1))
					System.out.println(agentArr[i].toString() + " checks " + lines[i].peek().toString() + "... To the interrogation room! .... Successfully detained! \n");

				if((checkPass(agentArr[i], lines[i].peek())) && (lines[i].peek().getIsThreat() == 0))
					System.out.println(agentArr[i].toString() + " checks " + lines[i].peek().toString() + "... To the interrogation room! .... Unnecessary Screening! \n");

				if((!checkPass(agentArr[i], lines[i].peek())) && (lines[i].peek().getIsThreat() == 1))
					System.out.println(agentArr[i].toString() + " checks " + lines[i].peek().toString() + "... Free to Go! .... Missed a threat! \n");

				if((!checkPass(agentArr[i], lines[i].peek())) && (lines[i].peek().getIsThreat() == 0))
					System.out.println(agentArr[i].toString() + " checks " + lines[i].peek().toString() + "... Free to Go! .... Was not a threat! \n");
				
				lines[i].dequeue();
				//lines[i].parse();
			}
		}
	}
}
