#include "../../include/my.h"

char* my_strindex(char* str, char c)
{
	int i = 0;
	char* found = NULL;

	if (str == NULL)
	{
		return NULL;
	}

	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			if (str[i] == c)
			{
				found = &str[i];
				return found;
			}
			else
				i++;
		}
	}

	return NULL;
}
