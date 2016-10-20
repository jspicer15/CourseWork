/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : John Spicer
 * Date        : 10/4/15
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > ways;
vector<int> steps;

/*
Uses recursion to produce a vector containing vectors of every possible combination of steps to reach the desired number of stairs
*/
vector< vector<int> > get_ways(int num_stairs)
{
    	if(num_stairs == 0)
	{
		ways.push_back(steps);
	}

	if(num_stairs >= 1)
	{
		steps.push_back(1);
		get_ways(num_stairs - 1);
	}

	if(num_stairs >= 2)
	{
		steps.push_back(2);
		get_ways(num_stairs - 2);
	}

	if(num_stairs >= 3)
	{
		steps.push_back(3);
		get_ways(num_stairs - 3);
	}
	
	steps.pop_back();
	return ways;
}

/*
Prints out each inner vector
*/
void display_ways(const vector< vector<int> > &ways)
{
	unsigned int num_vects = ways.size();
	for(unsigned int i = 0; i < num_vects; i++)
	{
		if(num_vects > 9)
		{
			if(i < 9)
				cout << " " << i + 1 << ". [";
			else
				cout << i + 1 << ". [";
		}
		else
			cout << i + 1 << ". [";
		for(unsigned int j = 0; j < ways[i].size(); j++)
		{
			if(j != ways[i].size() - 1)
				cout << ways[i][j] << ", ";
			else
				cout << ways[i][j];
		}
		cout << "]" << endl;
	}
}

/*
Error checking and input handling
*/
int main(int argc, char * const argv[])
{
	if(argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	if(atoi(argv[1]) <= 0)
	{
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	vector< vector<int> > stairs = get_ways(atoi(argv[1]));

	if(atoi(argv[1]) == 1)
	{
		cout << "1 way to climb 1 stair." << endl;
	}

	else
	{
		cout << ways.size() << " ways to climb " << argv[1] << " stairs." << endl;
	}

	display_ways(stairs);
}
