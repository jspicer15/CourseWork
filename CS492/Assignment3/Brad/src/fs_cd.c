/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_cd.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'dir'
 * post: sets directory 'dir' as the current directory, or sets the parent
 *      directory as the current directory when 'dir' is '..'
 */
void fs_cd(char* dir)
{
    leaf* l;

    if (!strcmp(dir, ".."))
    {
        if ((l = gl.cur_dir->parent) != NULL)
            gl.cur_dir = l;
        else
        {
            printf("%s: cd: no such file or directory: %s\n", gl.executable, dir);
            fflush(stdout);
        }
    }
    else
    {
        if ((l = findInHierarchy(gl.cur_dir, dir)) != NULL)
            gl.cur_dir = l;
        else
        {
            printf("%s: cd: no such file or directory: %s\n", gl.executable, dir);
            fflush(stdout);
        }
    }
}

