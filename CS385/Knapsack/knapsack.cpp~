/*
** Author: John Spicer
** Date: 12/8/15
** Assignment: Knapsack
** Pledge: I pledge my honor that I have abided by the Stevens Honor System
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Item
{
	unsigned int item_number, weight, value;
	std::string description;
	explicit Item(const unsigned int item_number, 
		      const unsigned int weight, 
		      const unsigned int value,
		      const std::string &description) :
				item_number(item_number),
				weight(weight),
				value(value),
				description(description) { }

friend std::ostream& operator<<(std::ostream& os, const Item &item) 
{
	os << "Item " << item.item_number << ": " << item.description
		<< " (" << item.weight
		<< (item.weight == 1 ? " pound" : " pounds") << ", $"
		<< item.value << ")";
	os.flush();
	return os;
}
};

/*
	Finds the max of two ints
*/
int max(int i, int j) 
{
	if (i >= j)
	{
		return i;
	}

	else
	{
		return j;
	}
}

/*
	Uses dynamic programming to build an 2D vector of the values used
*/
std::vector<std::vector<unsigned int> > knapsack(unsigned int cap, std::vector<Item> items, unsigned int n)
{
	std::vector<std::vector<unsigned int> > K(n + 1, std::vector<unsigned int>(cap + 1));
	for (unsigned int i = 0; i <= n; ++i)
	{
		for (unsigned int j = 0; j <= cap; ++j)
		{
			if (i == 0 || j == 0)
			{
				K[i][j] = 0;
			}

			else if (items[i - 1].weight <= j)
			{
				K[i][j] = max(items[i - 1].value + K[i - 1][j - items[i - 1].weight],
						K[i - 1][j]);
			}

			else
			{
				K[i][j] = K[i - 1][j];
			}
		}
	}

	return K;
}

/*
	Splits the line read from the file into a vector separated by the character delim
*/
void split(const std::string &s, std::vector<std::string> &elems, char delim) 
{
 	elems.clear();
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

/*
	Error checking, file reading, print formatting
*/
int main(int argc, char * const argv[])
{
	std::vector<std::string> elems;
	std::vector<Item> items;
	std::ifstream fi(argv[2]);
	int capacity;
	int weight;
	int value;
	int line = 1;

	if (argc != 3)
	{
		std::cerr << "Usage: ./knapsack <capacity> <filename>";
		return -1;
	}


	std::stringstream iss(argv[1]);

	if (!(iss >> capacity) || (capacity < 0))
	{
		std::cerr << "Error: Bad value '" << argv[1] << "' for capacity." << std::endl;
		return -1;
	}	

	std::string inp;
	if (fi.is_open())
	{
		while (getline(fi, inp))
		{
			std::string descpt1;
			std::string descpt2;
			std::string description;
			split(inp, elems, ',');

			if (elems.size() != 3)
			{
				std::cerr << "Error: Line number " << line << " does not contain 3 fields." << std::endl;
				return -1;
			}

			std::stringstream iss;
			iss.str(elems[0]);
			iss >> descpt1;
			getline(iss, descpt2);
			description = descpt1 + descpt2;

			bool isintweight = std::istringstream(elems[1]) >> weight;

			if ((!isintweight) || (weight < 0))
			{
				std::cerr << "Error: Invalid weight '" << elems[1] << "' on line number " << line << "." << std::endl;
				return -1;
			}

			bool isintvalue = std::istringstream(elems[2]) >> value;
			if ((!isintvalue) || (value < 0))
			{
				std::cerr << "Error: Invalid value '" << elems[2] << "' on line number " << line << "." << std::endl;
				return -1;
			}
			Item item = Item(line, weight, value, description);
			items.push_back(item);
			line++;
	  	}

		fi.close();
		std::cout << "Candidate items to place in knapsack:\n";

		for (unsigned int i = 0; i < items.size(); i++)
			std::cout << "   " << items[i] << "\n";

		std::vector<std::vector<unsigned int> >  sack = knapsack(capacity, items, items.size());
		int n = items.size();
		std::vector<int> stolen;
		int total_val = sack[n][capacity];
		int total_weight = 0;

 		(capacity > 1 ? std::cout << "Capacity: " << capacity << " pounds\n" : std::cout << "Capacity: " << capacity << " pound\n");

		while ((n > 0) && (capacity > 0))
		{
			if (sack[n][capacity] != sack[n - 1][capacity])
			{
				n = n - 1;
				capacity = capacity - items[n].weight;
				stolen.push_back(n);
			}
			else
				n = n - 1;
		}

		std::cout << "Items to place in knapsack:\n";

		for (int i = stolen.size() - 1; i >= 0; i--)
		{
			std::cout << "   " << items[stolen[i]] << "\n";
			total_weight += items[stolen[i]].weight;
		}
		
		(stolen.size() > 1 ? std::cout << "Total weight: " << total_weight << " pounds\n" : std::cout << "Total weight: " << total_weight << " pound\n");

		std::cout << "Total value : $" << total_val; 
	}

	else
	{
		std::cerr << "Error: Cannot open file '" << argv[2] << "'." << std::endl;
		return -1;
	}
		
  	return 0;
}
