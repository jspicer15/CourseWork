#include "../../include/my.h"

int my_pow(int n, int exp)
{
	int count = 0;
	int output = n;

	if (exp == 0) return 1;

	while (count < exp - 1)
	{
		output = output * n;
		count++;
	}
	return output;
}
