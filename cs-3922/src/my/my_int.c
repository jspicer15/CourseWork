#include "../../include/my.h"

void my_int(int n)
{
	int count, n_copy, i;
	char c;

	if (n == 1 <<(8*sizeof(int)-1)) my_str("Max Neg");
	else if (n == 0) my_char('0');
	else
	{
		if (n < 0)
		{
			my_char('-');
			n = n * -1;
		}

		count = 0;
		n_copy = n;		

		while (n_copy > 0)
		{
			n_copy = n_copy / 10;
			count++;
		}

		i = 0;

		while (i < count - 1)
		{
			n_copy = n % my_pow(10, count - i - 1);
			n = n / my_pow(10, count - i - 1);
			c = n + '0';

			my_char(c);

			n = n_copy;

			i++;
		}

		c = n + '0';

		my_char(c);
	}
}
