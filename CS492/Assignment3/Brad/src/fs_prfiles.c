/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_prfiles.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: prints out all file information
 */
void fs_prfiles()
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
        printf("%s\t%d blocks\t%d bytes\t%ld timestamp\n",
                getFullPath(f),
                f->allocatedBlocks,
                f->size,
                f->timestamp);
        printf("\tBlock addresses: ");
        for (n = f->lfile; n != NULL; n = n->next)
        {
            printf("%d ", ((fs_block*)(n->data))->s_addr);
        }
        printf("\n");
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

