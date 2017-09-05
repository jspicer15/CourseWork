/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_exit.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: de-allocates data structures and exits the program
 */
void fs_exit()
{
    node* n;
    node* neighbors;
    fs_file* f;
    leaf* t;

    /* close open file descriptors */
    close(gl.fd_flist);
    close(gl.fd_dlist);

    /* free gl.ldisk */
    while ((n = popNode(&gl.ldisk)) != NULL)
        free(n);

    /* free gl.tree */
    t = gl.tree;
    neighbors = NULL;
    while (t != NULL)
    {
        f = (fs_file*)(t->data);

        /* free the file */
        free(f->name);
        while ((n = popNode(&(f->lfile))) != NULL)
            free(n);
        free(f);

        if ((n = t->children) != NULL)
        {
            do
            {
                appendNode(&neighbors, createNode(n->data));
            } while ((n = n->next) != NULL);
        }

        /* free the tree node */
        free(t);

        if ((n = popNode(&neighbors)) != NULL)
        {
            /* TODO: might be leaking memory from popping off of neighbors */
            t = (leaf*)(n->data);
        }
        else
            t = NULL;
    }
}

