/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_delete.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'name'
 * post: deletes the file or directory referenced by 'name'
 */
void fs_delete(char* name)
{
    leaf* t;
    leaf* p;

    if ((t = findInHierarchy(gl.cur_dir, name)) != NULL)
    {
        if (((fs_file*)(t->data))->isDirectory && t->children != NULL)
        {
            printf("%s: delete: cannot delete `%s`: Directory is not empty\n",
                    gl.executable, name);
            fflush(stdout);
        }
        else
        {
            if ((p = t->parent) != NULL)
                ((fs_file*)(p->data))->timestamp = time(NULL);

            /* TODO: actually remove t */
            /* removeLeaf(&gl.tree, t); */
        }
    }
    else
    {
        printf("%s: delete: cannot delete file `%s`: no such file or directory\n",
                gl.executable, name);
        fflush(stdout);
    }
}

