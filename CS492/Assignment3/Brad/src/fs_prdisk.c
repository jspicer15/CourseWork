/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_prdisk.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: prints out disk space information
 */
void fs_prdisk()
{
    leaf* t;
    fs_file* f;
    node* n;
    node* neighbors;
    fs_block* b;
    int frag;

    frag = 0;
    neighbors = NULL;

    /* for each node in gl.ldisk */
    for (n = gl.ldisk; n != NULL; n = n->next)
    {
        b = (fs_block*)(n->data);
        if (b->isFree)
        {
            printf("Free:\t%d-%d\n", b->s_addr, b->e_addr - 1);
        }
        else
        {
            printf("In Use:\t%d-%d\n", b->s_addr, b->e_addr - 1);
        }
    }

    /* count fragmentation */
    t = gl.tree;

    /* BFS over all files */
    while (t != NULL)
    {
        f = (fs_file*)(t->data);

        /* if file takes up less than it's last block */
        if (f->size % gl.bsize)
        {
            frag += f->size % gl.bsize;
        }

        if ((n = t->children) != NULL)
        {
            do /* add children to the neighbors queue */
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

    printf("Fragmentation: %d\n", frag);
    fflush(stdout);
}

