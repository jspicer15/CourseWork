// "I pledge my honor that I have abided by the Stevens Honor System" - John Spicer"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int gcd_iterative(int m, int n)
{
	if(m == 0)
	{
		return n;
	}
	if(n == 0)
	{
		return m;
	}
	int r = m % n;
	while(r != 0)
	{
		r = m % n;
		m = n;
		n = r;
	}

	return m;
}

int gcd_recursive(int m, int n)
{
	if(m == 0)
	{
		return n;
	}
	if(n == 0)
	{
		return m;
	}
	int r = m % n;
	if(r != 0)
	{
		return gcd_recursive(n, r);
	}
	return n;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}

	istringstream iss;
	iss.str(argv[1]);
	int m;

	if (!(iss >> m) )
	{
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}

	iss >> m;
	iss.clear();
	iss.str(argv[2]);
	int n;

	if (!(iss >> n) )
	{
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}

	iss >> n;

	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;

	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m,n) << endl;
}
