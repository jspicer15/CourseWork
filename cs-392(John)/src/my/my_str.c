#include "../../include/my.h"
void my_str(char* str)
{
	if (str == 0)
	{
		my_str("error: string cannot be NULL\n");
		return;
	}

	int i = 0;
	while(str[i] != '\0')
	{
		my_char(str[i]);
		i++;
	}

}
