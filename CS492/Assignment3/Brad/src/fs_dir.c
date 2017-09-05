/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_dir.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: prints out the directory tree in breadth-first order
 */
void fs_dir()
{
    leaf* t; /* temp tree */
    node* n; /* temp node */
    fs_file* f; /* temp file */
    node* neighbors; /* linked_list to hold the order for BFS */

    neighbors = NULL;
    t = gl.tree;

    while (t != NULL)
    {
        f = (fs_file*)(t->data);
        printf("%s\n", getFullPath(f));
        fflush(stdout);

        if ((n = t->children) != NULL)
        {
            do /* add all children to the neighbors queue */
            {
                appendNode(&neighbors, createNode(n->data));
            } while ((n = n->next) != NULL);
        }

        if ((n = popNode(&neighbors)) != NULL)
        {
            /* TODO: might be leaking memory from popping off of neighbors */
            t = (leaf*)(n->data);
        }
        else
            t = NULL;
    }
}

