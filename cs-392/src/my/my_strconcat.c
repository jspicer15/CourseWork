#include "../../include/my.h"

char *my_strconcat(char *a, char *b)
{
	int len_a = my_strlen(a) + 1;
	int len_b = my_strlen(b) + 1;
	char *cat = NULL;

	if ((a == NULL) && (b == NULL))
		return cat;

	else if ((a == NULL) && (b != NULL))
	{
		cat = (char*) malloc(len_b*sizeof(char));
		cat = my_strcpy(cat, b);
	}

	else if ((a != NULL) && (b == NULL))
	{
		cat = (char*) malloc(len_a*sizeof(char));
		cat = my_strcpy(cat, a);
	}

	else
	{
		cat = (char*) malloc((len_a + len_b)*sizeof(char));
		my_strcpy(cat, a);
		cat = my_strcat(cat, b);
	}

	return cat;
}
