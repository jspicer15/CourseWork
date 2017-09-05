/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_mkdir.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'name'
 * post: creates a new directory named 'name' in the current directory
 */
void fs_mkdir(char* name)
{
    /* only add if 'name' does not exist in the current directory */
    if (findInHierarchy(gl.cur_dir, name) != NULL)
    {
        printf("%s: mkdir: cannot create directory `%s`: File exists\n", gl.executable, name);
        fflush(stdout);
    }
    else
        addToHierarchy(createFile(name, 0, 1));
}

