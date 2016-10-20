/*******************************************************************************
 * Name        : unique.cpp
 * Author      : John Spicer
 * Date        : 9/25/15
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

/*
Returns true if all letters in the string are lowercase, false if any are not
*/
bool is_all_lowercase(const string &s)
{
	for(unsigned int i = 0; i < s.size(); i++)
	{
		if((s[i] < 96) || (s[i] > 123))
		{
			cout << "Error: String must contain only lowercase letters." << endl;
			return false;
		}
	}
	return true;
}

/*
Returns true if all letters in the string are unique, false if they are not
*/
bool all_unique_letters(const string &s)
{
	unsigned int check = 0;
	for(unsigned int i = 0; i < s.size(); i++)
	{
		if(((check) & (1 << (s[i] - 'a'))) > 0)
		{
			cout << "Duplicate letters found." << endl;
			return false;
		}
		check |= (1 << (s[i] - 'a'));
	}
	cout << "All letters are unique." << endl;
	return true;
}

/*
Checks if input is a string of only letters, then calls is_all_lowercase and all_unique_letters .
*/
int main(int argc, char * const argv[])
{
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	if(!is_all_lowercase(argv[1]))
		return 1;
	all_unique_letters(argv[1]);
	return 0;
}
