/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 countProcs.c
 * 04/01/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "VMsimulator.h"

/* pre: takes in a FILE* 'fd' which must be a valid file, pointing to the plist
 *      input parameter from main
 * post: counts the lines in 'fd' which is the number of unique processes in
 *      plist
 * return: an integer of the count of the lines in 'fd'
 */
int countProcs(FILE* fd)
{
    int ret;
    int i;
    char c;

    ret = 0;
    i = 0;
    while (!feof(fd))
    {
        c = fgetc(fd);
        i++;
        if (c == '\n')
        {
            if (i > 1)
            {
                i = 0;
                ret++;
            }
        }
    }

    return ret;
}

