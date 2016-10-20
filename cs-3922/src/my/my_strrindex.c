#include "../../include/my.h"

char* my_strrindex(char* str, char c)
{
	char* found = NULL;
	int i = 0;

	if ((str == NULL) && (c != '\0'))
	{
		return NULL;
	}

	if (my_strlen(str) == 0)
	{
		return NULL;
	}

	while (str[i] != '\0')
	{
		if (str[i] == c)
			found = &str[i];
		i++;
	}

	return found;
}

