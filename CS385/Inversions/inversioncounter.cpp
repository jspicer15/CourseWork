/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : John Spicer
 * Version     : 1.0
 * Date        : 11/6/15
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) 
{
	long inversions = 0;
	for(int i = 0; i < length - 1; ++i)
		for(int j = i + 1; j < length; ++j)
			if(array[i] > array[j])
				inversions++;
	return inversions;	
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) 
{
	int *scratch = new int[length];
	long inversions = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return inversions;
}

/**
 * Mergesort to count the inversions
 */
static long mergesort(int array[], int scratch[], int low, int middle, int high)
{
	int i, j, k;
	long inversions = 0;

	i = low;
	j = middle;
	k = low;
	while ((i <= middle - 1) && (j <= high))
	{
		if (array[i] <= array[j])
		{
			scratch[k++] = array[i++];
		}
		else
		{
			scratch[k++] = array[j++];
			inversions += (middle - i);
		}
	}

	while (i <= middle - 1)
	scratch[k++] = array[i++];

	while (j <= high)
	scratch[k++] = array[j++];

	for (i = low; i <= high; i++)
	array[i] = scratch[i];

	return inversions;
}

/**
 * Mergesort to count the inversions
 */
static long mergesort(int array[], int scratch[], int low, int high) 
{
	int mid;
	long inversions = 0;
	if(high > low)
	{
		mid = (low + high) / 2;
		inversions = mergesort(array, scratch, low, mid);
		inversions += mergesort(array, scratch, mid + 1, high);
		inversions += mergesort(array, scratch, low, mid + 1, high);
	}
	return inversions;
}

/**
 * Error Checking and Input Reading
 */
int main(int argc, char *argv[]) 
{
	if(argc > 2)
	{
		cerr << "Usage: ./inversioncounter [slow]";
		return 1;
	}
	bool slow = 0;
	if((argv[1] != NULL) && (strcmp(argv[1],"slow") == 0))
		slow = 1;
	else
		if(argv[1] != NULL)
		{
			cerr << "Error: Unrecognized option '" << argv[1] << "'.";
			return 1;
		}
	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) 
	{
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if(isspace(c) || eoln)
		{
			if(str.length() > 0)
			{
				iss.str(str);
				if(iss >> value)
				{
					values.push_back(value);
				} 
				else
				{
					cerr << "Error: Non-integer value '" << str
					<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if(eoln)
			{
				break;
			}
			str.clear();
		}
		else
		{
			str += c;
		}
	}

	if(values.size() > 0)
	{
		if(slow)
			cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size());
		else
		{
			cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size());
		}
	}
	else
		cout << "Error: Sequence of integers not received." << endl;
	return 0;
}
