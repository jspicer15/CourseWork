/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 usage.c
 * 04/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'prg'
 * post: prints out a usage message using 'prg' as the executable name
 */
void usage(char* prg)
{
    char* options;

    options = "-f file_list -d dir_list -s disk_size -b block_size";
    printf("usage: %s %s\n", prg, options);
}

