#include "../../include/my.h"

char *my_vect2str(char **x)
{
	int i = 0;
	int len = 0;
	char *str = NULL;

	if (x == NULL)
		return NULL;

	else
	{
		while (x[i] != NULL)
		{
			len += my_strlen(x[i]);
			i++;
		}

		str = (char*) malloc(len*sizeof(char));
		i = 0;

		while (x[i] != NULL)
		{
			if (i == 0)
			{
				my_strcpy(str, x[i]);
			}

			else
			{
				my_strcat(str, " ");
				my_strcat(str, x[i]);
			}
			i++;
		}

		return str;
	}
}
