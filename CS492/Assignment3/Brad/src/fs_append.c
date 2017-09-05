/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_append.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'file' and an int 'bytes'
 * post: appends 'bytes' number of bytes to the file 'file'
 */
void fs_append(char* file, int bytes)
{
    leaf* target;

    if (bytes < 0)
    {
        printf("usage: append name size\n");
        fflush(stdout);
    }
    else if ((target = findInHierarchy(gl.cur_dir, file)) != NULL)
    {
        /* only append to regular files */
        if (!(((fs_file*)(target->data))->isDirectory))
        {
            ((fs_file*)(target->data))->size += bytes;
            allocateFile((fs_file*)(target->data));
            ((fs_file*)(target->data))->timestamp = time(NULL);
        }
    }
    else if (target == NULL)
    {
        printf("%s: append: no such file or directory: %s\n", gl.executable, file);
        fflush(stdout);
    }
}

