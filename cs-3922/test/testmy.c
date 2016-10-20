#include "../include/my.h"
#include <limits.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

void printvect(char** vect)
{
	int i = 0;

	if (vect != NULL)
	{
		my_str("vector is: ");
		while (vect[i] != NULL)
		{
			my_str(vect[i]);
			my_char(' ');
			i++;
		}
	}
}

int main (int argc, char const *argv[])
{
        char str1[] = { 'H', 'E', 'L', 'L', 'O', '\0'};
	char str2[] = { 'O', 'S', 'O', 'R', 'I', 'O', '\0'};
	char str3[] = { 'H', 'E', 'L', 'P', '\0' };
	char str4[] = { 'H', 'E', 'L', 'L', 'A', '\0' };
	char str5[] = { 'T', 'E', 'S', 'T' };

	char* vect[] = { "Hello", "my", "name", "is", "John", NULL };
	char* nullvect[] = { NULL };
	char** vectreturn;

	int maxneg = INT_MIN;
	
/*	char* newstr1 = (char*) malloc(20 * sizeof(char));
	char* newstr2 = (char*) malloc(20 * sizeof(char));	*/
	char newstr1[20] = "HELLO";
	char newstr2[20] = "WORLD";

        /*testing my_strfind()*/
        my_str("testing my_strfind() --------------------\n\n");
        my_int(my_strfind(NULL, '\0'));
        my_char('\n');
        my_int(my_strfind(str1, 'E'));
        my_char('\n');
        my_int(my_strfind(str1, 'e'));
        my_char('\n');
        my_int(my_strfind(str1, '\0'));
        my_char('\n');
        my_char('\n');

        /*testing my_strrfind()*/
        my_str("testing my_strrfind() --------------------\n\n");
        my_int(my_strrfind(NULL, '\0'));
        my_char('\n');
	my_int(my_strrfind(NULL, '\0'));
	my_char('\n');
        my_int(my_strrfind(str1, 'E'));
        my_char('\n');
        my_int(my_strrfind(str1, 'e'));
        my_char('\n');
	my_int(my_strrfind(str1, 'L'));
	my_char('\n');
	my_int(my_strrfind(str1, 'l'));
	my_char('\n');
        my_int(my_strrfind(str1, '\0'));
        my_char('\n');
        my_char('\n');

	/*testing my_strcmp()*/
	my_str("testing my_strcmp() --------------------\n\n");
	my_int(my_strcmp(NULL, str1));
	my_char('\n');
	my_int(my_strcmp(str1, NULL));
	my_char('\n');
	my_int(my_strcmp(NULL, NULL));
	my_char('\n');
	my_int(my_strcmp(str1, str1));
	my_char('\n');
	my_int(my_strcmp(str1, str2));
	my_char('\n');
	my_char('\n');

	/*testing my_strncmp()*/
	my_str("testing my_strncmp() --------------------\n\n");
	my_int(my_strncmp(NULL, str1, 100));
	my_char('\n');
	my_int(my_strncmp(str1, str2, 3));
	my_char('\n');
	my_int(my_strncmp(str1, str3, 3));
	my_char('\n');
	my_int(my_strncmp(str1, str4, 4));
	my_char('\n');
	my_int(my_strncmp(str1, str4, maxneg));
	my_char('\n');
	my_int(my_strncmp(str1, str2, -5));
	my_char('\n');
	my_int(my_strncmp(NULL, str1, -5));
	my_char('\n');
	my_int(my_strncmp(str1, str4, 100));
	my_char('\n');
	my_char('\n');

	/*testing my_strcpy()*/
        my_str("testing my_strcpy() --------------------\n\n");
	my_str(my_strcpy(NULL, NULL));
	my_char('\n');
	my_str(my_strcpy(NULL, str2));
	my_char('\n');
	my_str(my_strcpy(str2, NULL));
	my_char('\n');
	my_str(my_strcpy(str4, str1));	/*str4 becomes "HELLO"*/
	my_char('\n');
	my_str(my_strcpy(str2, str3));	/*str2 becomes "HELP"*/
	my_char('\n');
	my_char('\n');

	/*testing my_strncpy()*/
	my_str("testing my_strncpy() --------------------\n\n");
	my_str(my_strncpy(NULL, NULL, 0));
	my_char('\n');
	my_str(my_strncpy(NULL, str2, -10));
	my_char('\n');
	my_str(my_strncpy(str2, NULL, 0));
	my_char('\n');
	my_str(my_strncpy(str2, str1, maxneg));
	my_char('\n');
	my_str(my_strncpy(str2, str1, 4));	/*str2 becomes "HELL"*/
	my_char('\n');
	my_str(my_strncpy(str2, str5, 100));	/*str2 becomes "TEST"*/
	my_char('\n');
	my_char('\n');

	/*testing my_strcat()*/
	my_str("testing my_strcat() --------------------\n\n");
	my_str(my_strcat(newstr1, newstr2));		/*str1 becomes "HELLOWORLD"*/
	my_char('\n');
	my_str(my_strcat(newstr1, NULL));
	my_char('\n');
	my_str(my_strcat(NULL, newstr1));
	my_char('\n');
	my_str(my_strcat(NULL, NULL));
	my_char('\n');
	my_char('\n');
	
	/*testing my_strdup()*/
	my_str("testing my_strdup() --------------------\n\n");
	my_str(my_strdup(NULL));
	my_char('\n');
	my_str(my_strdup(newstr2));
	my_char('\n');
	my_char('\n');

	/*testing my_strconcat()*/
	my_str("testing my_strconcat() ---------------------\n\n");
	my_str(my_strconcat(NULL, NULL));
	my_char('\n');
	my_str(my_strconcat(NULL, newstr2));
	my_char('\n');
	my_str(my_strconcat(newstr2, NULL));
	my_char('\n');
	my_str(my_strconcat(newstr2, newstr1));	/*returns "WORLDHELLOWORLD"*/
	my_char('\n');
	my_char('\n');

	/*testing my_strnconcat()*/
	my_str("testing my_strnconcat() ---------------------\n\n");
	my_str(my_strnconcat(NULL, NULL, 100));
	my_char('\n');
	my_str(my_strnconcat(NULL, newstr2, maxneg));
	my_char('\n');
	my_str(my_strnconcat(newstr2, NULL, 10));
	my_char('\n');
	my_str(my_strnconcat(newstr2, newstr1, maxneg));
	my_char('\n');
	my_str(my_strnconcat(newstr2, newstr1, 5));	/*returns "WORLDHELLO"*/
	my_char('\n');
	my_char('\n');

	/*testing my_vect2str()*/
	my_str("testing my_vect2str() ---------------------\n\n");
	my_str(my_vect2str(NULL));
	my_char('\n');
	my_str(my_vect2str(vect));
	my_char('\n');
	my_str(my_vect2str(nullvect));
	my_char('\n');
	my_char('\n');

	/*testing my_str2vect*/
	my_str("testing my_str2vect() ---------------------\n\n");
	vectreturn = my_str2vect(NULL);
	printvect(vectreturn);
	my_char('\n');
	vectreturn = my_str2vect("Hi \tmy\n\n \t,name     is John");
	printvect(vectreturn);
	my_char('\n');
	my_char('\n');

	/*testing my_atoi*/
	my_str("testing my_atoi() ---------------------\n\n");
	my_int(my_atoi(NULL));
	my_char('\n');
	my_int(my_atoi("56"));
	my_char('\n');
	my_int(my_atoi("--56"));
	my_char('\n');
	my_int(my_atoi("ad-flkjhs--sab559dfkjh---392"));
	my_char('\n');

        return 0;
}
