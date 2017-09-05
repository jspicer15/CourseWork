/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_ls.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: lists all files and sub-directories in the current directory
 */
void fs_ls()
{
    node* n;

    n = NULL;
    if ((n = gl.cur_dir->children) != NULL)
    {
        do
        {
            if (((fs_file*)(((leaf*)(n->data))->data))->isDirectory)
                printf("%s%c\n", ((fs_file*)(((leaf*)(n->data))->data))->name, PATH_SEP);
            else
                printf("%s\n", ((fs_file*)(((leaf*)(n->data))->data))->name);
        }
        while ((n = n->next) != NULL);
        fflush(stdout);
    }
}

