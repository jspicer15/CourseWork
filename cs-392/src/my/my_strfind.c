#include "../../include/my.h"

int my_strfind(char *src, char c)
{
	int i = 0;

	if (src == NULL)
	{
		return -1;
	}

	if (src != NULL)
	{
		while (src[i] != '\0')
		{
			if (src[i] == c)
			{
				return i;
			}
			else
				i++;
		}
	}

	return -1;
}
