#include "../../include/my.h"
void my_str(char* str)
{
	int i = 0;

	if (str == 0)
	{
		return;
	}

	while(str[i] != '\0')
	{
		my_char(str[i]);
		i++;
	}

}
