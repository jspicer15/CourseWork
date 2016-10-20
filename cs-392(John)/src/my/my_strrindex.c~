#include "../../include/my.h"

char* my_strrindex(char* str, char c)
{
	if ((str == NULL) && (c != '\0'))
	{
		my_str("error: string or character cannot be NULL\n");
		return NULL;
	}

	if (my_strlen(str) == 0)
	{
		return NULL;
	}

	int i = 0;
	char *found = NULL;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			found = &str[i];
		i++;
	}

	return found;
}

