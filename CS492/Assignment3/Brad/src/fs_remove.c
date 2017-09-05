/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_remove.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'file' and an int 'bytes'
 * post: removes 'bytes' number of bytes from the file 'file'
 */
void fs_remove(char* file, int bytes)
{
    leaf* target;

    if (bytes < 0)
    {
        printf("usage: remove name size\n");
        fflush(stdout);
    }
    else if ((target = findInHierarchy(gl.cur_dir, file)) != NULL)
    {
        /* only remove from regular files */
        if (!(((fs_file*)(target->data))->isDirectory))
        {
            ((fs_file*)(target->data))->size -= bytes;
            /* TODO: actually de-allocate file */
            ((fs_file*)(target->data))->timestamp = time(NULL);
        }
    }
    else if (target == NULL)
    {
        printf("%s: remove: no such file or directory: %s\n", gl.executable, file);
        fflush(stdout);
    }
}

