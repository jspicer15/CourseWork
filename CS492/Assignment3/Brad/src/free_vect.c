/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 free_vect.c
 * 04/24/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char** 'vect'
 * post: frees each string in 'vect' then frees 'vect'
 */
void free_vect(char** vect)
{
	int i;

	for (i = 0; vect[i] != NULL; i++)
		free(vect[i]);
	free(vect[i]); /* free the last NULL */
	free(vect);
}

