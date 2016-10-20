/*
	@author John Spicer
*/
public class TSA extends Person 
{

	private int paranoia;
	private int[] likes;
	private int[] dislikes;

	/*
		@param f: firstName
		@param l: lastName
		@param a: age
		@param g: gender
		@param p: paranoia
		@param likesArr: array of likes
		@param dislikesArr: array of dislikes
	*/
	public TSA(String f, String l, int a, int g, int p, int[] likesArr, int[] dislikesArr) 
	{
		firstName = f;
		lastName = l;
		age = a;
		gender = g;
		paranoia = p;
		likes = likesArr;
		dislikes = dislikesArr;
	}
	
	/*
		@return paranoia of the TSA agent
	*/
	public int getParanoia() 
	{
		return paranoia;
	}
	
	/*
		@return likes array of the TSA agent
	*/
	public int[] getLikes() 
	{
		/*for(int i = 0; i < likes.length; i++)
			System.out.println(likes[i]);
		*/
		return likes;
	}

	/*
		@return dislikes array of the TSA agent
	*/
	public int[] getDislikes() 
	{
		/*for(int i = 0; i < dislikes.length; i++)
			System.out.println(dislikes[i]);
		*/
		return dislikes;
	}
	
	/*
		@return first name and last name of the TSA agent
	*/
	public String toString() 
	{
		return firstName + " " + lastName;
	}
	
	
	/*
		@param agent: TSA object
		@return positive if this.getAge()is higher than pass.getAge(), negative if this.getAge()is lower than pass.getAge(), zero if this.getAge()is equal to pass.getAge()
	*/
	public int compareTo(TSA agent) 
	{
		return (this.getAge() - agent.getAge());
	}

}
