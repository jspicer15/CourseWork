#include "../../include/my.h"

int my_atoi(char *a)
{
	int i = 0;
	int numFound = 0;
	int negCount = 0;
	int numStart, numStop;
	int n = 0;

	if (a == NULL) return 0;

	while (a[i] != '\0' && (numFound == 0 || (a[i] > 47 && a[i] < 58)))
	{
		if (a[i] == 45) negCount++;
		if (a[i] > 47 && a[i] < 58 && numFound == 0)
		{
			numFound = 1;
			numStart = i;
		}

		i++;
	}

	numStop = i - 1;
	i = 0;

	while (numStop >= numStart)
	{
		n += (a[numStop] - 48) * my_pow(10, i);
		i++;
		numStop--;
	}

	if (negCount % 2 == 0) return n;
	else return n * -1;
}
