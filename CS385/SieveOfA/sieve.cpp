/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : John Spicer
 * Date        : September 19, 2015
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve
{
	public:
		PrimesSieve(int limit)
	{
		is_prime_ = new bool[limit + 1];
		limit_ = limit;
		for(int i = 0; i < limit_ + 1; i++)
		{
			is_prime_[i] = true;
		}
	       	sieve();
		cout << endl << "Number of primes found: " << count_num_primes() << endl;
		cout << "Primes up to " << limit_ << ":" << endl;
	}

	/*
		Deconstructor
	*/
    	~PrimesSieve()
	{
        	delete [] is_prime_;
    	}

	/*
		returns the number of primes found
	*/
    	inline int num_primes() const
	{
        	return num_primes_;
    	}

	/*
		Prints out the prime numbers using the max_prime_width and setw from iomanip
	*/
        void display_primes()
        {
		const int max_prime_width = num_digits(max_prime()), primes_per_row = 80 / (max_prime_width + 1);
		int count = 0;
		int row = 0;
		for(int i = 2; i <= limit_; i++)
		{
			if(is_prime_[i])
			{
				if(max_prime_width == 2)
				{
					count++;
					if(count < num_primes_)
					{
						cout << i << " ";
					}
					else
					{
						cout << i;
					}
				}
				else if(count == 0)
				{
					cout << setw(max_prime_width) << i;
					count++;
				}
				else if(count < primes_per_row)
				{
					cout << setw(max_prime_width + 1) << i;
					count++;
				}
				else/* if(count >= primes_per_row)*/
				{
					cout << endl << setw(max_prime_width) << i;
					count = 1;
					row++;
				}
			}
		}
    	}

private:
    	bool * is_prime_;
    	int limit_;
    	int num_primes_, max_prime_;

	/*
		counts the number of primes and sets the variable num_primes_ equal to the number
	*/
    	int count_num_primes()
	{
		num_primes_ = 0;
		for(int i = 2; i <= limit_; i++)
		{
			if(is_prime_[i])
			{
				num_primes_++;
			}
		}
		return num_primes_;
    	}

	/*
		returns the number of digits in a number by dividing by 10
	*/
    	int num_digits(int num)
	{
        	int digs = 0;
		while(num >= 1)
		{
			num /= 10;
			digs++;
		}
		return digs;
    	}

	/*
		returns the max prime number up to the limit specified
	*/
	int max_prime()
	{
		for(int i = limit_; i > 2; i--)
		{
			if(is_prime_[i])
			{
				max_prime_ = i;
				return max_prime_;
			}
		}
		max_prime_ = 2;
		return max_prime_ ;
	}

	/*
		uses the sieve of Eratosthenes to find prime number and set all non primes as false in the array is_prime_
	*/
    	void sieve()
	{
		for(int i = 2; i <= sqrt(limit_); i++)
		{
			if(is_prime_[i])
			{

				for(int j = (i * i); j <= limit_; j+= i)
				{
					is_prime_[j] = false;
				}
			}
		}
    	}
};

int main(void)
{
	cout << "**************************** " <<  "Sieve of Eratosthenes" << " ****************************" << endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;
	// Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);
	// Check for error.
	if ( !(iss >> limit) )
	{
        	cerr << "Error: Input is not an integer." << endl;
        	return 1;
    	}

    	if (limit < 2)
	{
        	cerr << "Error: Input must be an integer >= 2." << endl;
        	return 1;
   	}
	PrimesSieve primes = PrimesSieve(limit);
	primes.display_primes();
	return 0;
}
