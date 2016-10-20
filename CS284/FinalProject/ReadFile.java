/*
	@author John Spicer
*/
import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;
//import java.util.regex.Pattern;

public class ReadFile 
{
	public static int[] likesArr;
	public static int[] dislikesArr;
	public static TSA[] agentsArr;
	public static Passenger[] passArr;	
	public static final String FILE = "input.dat";
	public static String agentCount;
	public static String passCount;
	public static int emptyLines = 0;
	//public static Pattern pattern = Pattern.compile("[0-9]*");

	/*
		@return number of agents read from file
		@exception throws FileNotFoundException if file not found
	*/
	public static int getAgents() throws FileNotFoundException 
	{	
		int agents = 0;
		FileInputStream is = new FileInputStream(FILE);
	    	Scanner scan = new Scanner(is);
		scan.useDelimiter("\n");
		agentCount = scan.nextLine();
		if(agentCount.trim().isEmpty())
		{
			agentCount = scan.next();
			//emptyLines = 5;
		}
		String[] agentsLine = agentCount.split(" ");
	    	agents = Integer.parseInt(agentsLine[0]);
		return agents;
	}
	
	/*
		@return number of passengers read from file
		@exception throws FileNotFoundException if file not found
	*/
	public static int getPass() throws FileNotFoundException 
	{	
		int pass = 0;
		FileInputStream is = new FileInputStream(FILE);
		Scanner scan = new Scanner(is);
		passCount = scan.nextLine();
		while(passCount.trim().isEmpty())
		{
			passCount = scan.nextLine();
		}
	    	String[] passLine = passCount.split(" ");
	    	pass = Integer.parseInt(passLine[1]);
		return pass;
	}
	
	/*
		@return string array of the whole file
		@exception throws IOException if file not found
	*/
	public static String[] data() throws IOException 
	{
		int agents = getAgents();
		int pass = getPass();
		
		int i = 0;
		int j = 1;
		
		int agentLines = agents * 7;
		int passLines = pass * 8;
		
		int totalLines = 2 + agentLines + passLines + emptyLines;
		String[] readFile = new String[totalLines];
		
		for(String readLine : Files.readAllLines(Paths.get(FILE), Charset.defaultCharset())) 
		{
			//System.out.println(readLine);
			if(readLine.length() <= 0)
				;
			else
			{
				if( (i >= j*7) && (i <= j*7 + 1) && (j <= agents)) 
				{
					readFile[i] = readLine;
					i++;

					if((i  < j*7) || (i > j*7 + 1))
						j++;
				}
			
				else 
				{
					for(String part : readLine.split(" ")) 
					{
						//System.out.println(part);
						readFile[i] = part;
						i++;
					}
				}
			}
		}

		return readFile;
	}
	
	/*
		@param agents: number of agents in the file
		@return int array of the likes of an agent
		@exception throws IOException if file not found
	*/
	public static int[] getLikes(int agents) throws IOException 
	{
		String data[] = data();
		String likes = data[agents*7 + emptyLines];
		String[] numArr = likes.split(" ");
		//System.out.println(numArr[0]);
		likesArr = new int[numArr.length];

		for(int i = 0; i < numArr.length; i++) 
		{
			//System.out.println(Integer.parseInt(numArr[i]));
			likesArr[i] = Integer.parseInt(numArr[i]);
		}

		return likesArr;
	}
	
	/*
		@param agents: number of agents in the file
		@return int array of the dislikes of an agent
		@exception throws IOException if file not found
	*/
	public static int[] getDislikes(int agents) throws IOException 
	{
		String data[] = data();
		String dislikes = data[agents*7+1];
		String[] numArr = dislikes.split(" ");

		dislikesArr = new int[numArr.length];

		for(int i = 0; i < numArr.length; i++) {
			dislikesArr[i] = Integer.parseInt(numArr[i]);
		}
		return dislikesArr;
	}
	
	/*
		@return array of TSA agents from the file
		@exception throws IOException if file not found
	*/
	public static TSA[] buildAgents() throws IOException 
	{
		int agents = getAgents();
		String[] data = data();
		agentsArr = new TSA[agents];

		for(int i = 0; i < agentsArr.length; i++)
		{
			//System.out.println(data[7*i+2+emptyLines]);
			agentsArr[i] = new TSA(data[7*i+2+emptyLines], data[7*i+3+emptyLines], Integer.parseInt(data[7*i+4+emptyLines]), Integer.parseInt(data[7*i+5+emptyLines]), Integer.parseInt(data[7*i+6+emptyLines]), getLikes(i+1), getDislikes(i+1));
		}
		
		return agentsArr;
	}
	
	/*
		@return array of passengers from the file
		@exception throws IOException if file not found
	*/
	public static Passenger[] buildPass() throws IOException 
	{
		int pass = getPass();
		int agents = getAgents();

		int agentLines = agents * 7;

		String[] data = data();
		passArr = new Passenger[pass];

		for(int i = 0; i < passArr.length; i++) 
		{
			passArr[i] = new Passenger(data[agentLines+2+i*8+emptyLines], data[agents*7+3+i*8+emptyLines], Integer.parseInt(data[agentLines+4+i*8+emptyLines]), Integer.parseInt(data[agentLines+5+i*8+emptyLines]), Integer.parseInt(data[agentLines+6+i*8+emptyLines]), Integer.parseInt(data[agentLines+7+i*8+emptyLines]), Integer.parseInt(data[agentLines+8+i*8+emptyLines]), Integer.parseInt(data[agentLines+9+i*8+emptyLines]));
		}
		return passArr;
	}

}
