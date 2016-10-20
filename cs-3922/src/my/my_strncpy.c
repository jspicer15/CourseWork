#include "../../include/my.h"

char *my_strncpy(char *dst, char *src, int n)
{
	int i = 0;

	if (n == 1 <<(8*sizeof(int)-1)) 
	{
		return dst;
	}

	if (n <= 0)
		return dst;

	if ((src == NULL) || (dst == NULL))
		return NULL;

	while ((src[i] != '\0') && (n != 0))
	{
		dst[i] = src[i];
		i++;
		n--;
	}

	dst[i] = '\0';
	return dst;
}
