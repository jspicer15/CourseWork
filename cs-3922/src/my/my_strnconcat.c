#include "../../include/my.h"

char *my_strnconcat(char *a, char *b, int n)
{
	int len_a = my_strlen(a) + 1;
	char *b_n = NULL;
	char *b_copy = NULL;
	char *cat = NULL;

	if ((a == NULL) && (b == NULL))
		return cat;

	if (n <= 0)
	{
		cat = (char*) malloc(len_a*sizeof(char));
		cat = my_strcpy(cat, a);
	}

	else if ((a == NULL) && (b != NULL))
	{
		cat = (char*) malloc(n*sizeof(char));
		cat = my_strncpy(cat, b, n);
	}

	else if ((a != NULL) && (b == NULL))
	{
		cat = (char*) malloc(len_a*sizeof(char));
		cat = my_strcpy(cat, a);
	}

	else
	{
		b_n = (char*) malloc(n*sizeof(char));
		b_copy = my_strncpy(b_n, b, n);
		cat = (char*) malloc((len_a + n)*sizeof(char));
		my_strcpy(cat, a);
		cat = my_strcat(cat, b_copy);
	}

	return cat;
}
