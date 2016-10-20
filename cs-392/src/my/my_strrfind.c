#include "../../include/my.h"

int my_strrfind(char *src, char c)
{
	int i = 0;
	int index = -1;

	if (src == NULL)
	{
		return -1;
	}

	else
	{
		while (src[i] != '\0')
		{
			if (src[i] == c)
			{
				index = i;
				i++;
			}
			else
				i++;
		}

		return index;
	}
}
