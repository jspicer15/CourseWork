#include "../../include/my.h"

char *my_strcat(char *dst, char *src)
{
	int i = 0;
	int j = 0;

	if (src == NULL)
	{
		return dst;
	}

	if (dst == NULL)
		return NULL;
	else
	{
		while (dst[j] != '\0')
			j++;

		while (src[i] != '\0')
		{
			dst[j] = src[i];
			i++;
			j++;
		}

		dst[j] = '\0';
	}

	return dst;
}
