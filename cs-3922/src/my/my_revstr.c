#include "../../include/my.h"

int my_revstr(char *str)
{
	int end, start;
	char temp1, temp2;

	if (str == NULL)
	{
		return -1;
	}

	end = my_strlen(str) - 1;
	start = 0;

	while (start < end)
	{
		temp1 = str[start];
		temp2 = str[end];
		str[end] = temp1;
		str[start] = temp2;
		start++;
		end--;
	}
	return my_strlen(str);

}
