#include "../../include/my.h"

char **my_str2vect(char* x)
{
	int i = 0;
	int index = 0;
	int words = 0;
	int len = 0;
	int ind = 0;
	char **vect = NULL;

	if (x == NULL)
		return NULL;

	else
	{

		while (x[i] != '\0')
		{
			while ((x[i] == '\t') || (x[i] == '\n') || (x[i] == ' ') || (x[i] == ','))
			{
				i++;
			}

			while ((x[i] != '\t') && (x[i] != '\n') && (x[i] != ' ') && (x[i] != '\0') && (x[i] != ','))
			{
				i++;
			}

			words++;
		}

		vect = (char**) malloc(words*sizeof(char*));
		i = 0;

		while (x[i] != '\0')
		{

			len = 0;

			while ((x[i] == '\t') || (x[i] == '\n') || (x[i] == ' ') || (x[i] == ','))
				i++;

			while ((x[i] != '\t') && (x[i] != '\n') && (x[i] != ' ') && (x[i] != '\0') && (x[i] != ','))
			{
				len++;
				i++;
			}

			vect[index] = (char*) malloc((len + 1) * sizeof(char));
			index++;
		}

		index = 0;
		i = 0;
		while (x[i] != '\0')
		{			
			len = 0;

			while ((x[i] == '\t') || (x[i] == '\n') || (x[i] == ' ') || (x[i] == ','))
			{
				i++;
			}

			ind = i;

			while ((x[i] != '\t') && (x[i] != '\n') && (x[i] != ' ') && (x[i] != '\0') && (x[i] != ','))
			{
				len++;
				i++;
			}
			my_strncpy(vect[index], &x[ind], len);
			index++;
		}

		vect[index] = NULL;
		return vect;
	}
}
