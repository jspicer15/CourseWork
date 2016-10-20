#include "../../include/my.h"

char *my_strdup(char *str)
{
	int len = my_strlen(str) + 1;
	char *dup = NULL;

	if (str == NULL)
		return dup;
	else
	{
		dup = (char*) malloc(len*sizeof(char));
		dup = my_strcpy(dup, str);
	}

	return dup;
}
