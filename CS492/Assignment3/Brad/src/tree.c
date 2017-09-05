/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 tree.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "tree.h"

/* pre: takes in a void* 'data'
 * post: allocates a new tree leaf that holds 'data'
 * return: a leaf* pointing to the newly allocated tree leaf, or NULL on error
 */
leaf* createLeaf(void* data)
{
    leaf* ret;

    ret = NULL;
    if (data != NULL)
    {
        if ((ret = (leaf*)malloc(sizeof(leaf))) != NULL)
        {
            ret->data = data;
            ret->parent = NULL;
            ret->children = NULL;
        }
    }

    return ret;
}

/* pre: takes in a leaf** 'tree' and a leaf* 'l'
 * post: appends 'l' to the tree as a child of 'tree'
 */
void appendLeaf(leaf** tree, leaf* l)
{
    if (l != NULL)
    {
        if ((*tree) == NULL)
            (*tree) = l;
        else
        {
            l->parent = (*tree);
            appendNode(&((*tree)->children), createNode((void*)l));
        }
    }
}

/* pre: takes in a leaf** 'tree' and a leaf* 'l'
 * post: removes 'l' from the tree pointed to by 'tree'
 * return: a leaf* pointing to the leaf that was removed from 'tree', or NULL on
 *      error
 */
leaf* removeLeaf(leaf** tree, leaf* l)
{
    leaf* ret;
    node* n; /* temp node storage */
    node* neighbors; /* linked_list to hold the order for BFS */

    ret = NULL;
    if (l != NULL) /* if we're trying to remove NULL skip everything */
    {
        if ((*tree) != NULL) /* if the tree we're removing from is NULL, skip */
        {
            if ((*tree) == l) /* if the root is what we're looking for */
            {
                ret = (*tree);
                tree = NULL;
            }
            else /* else check the children in BFS order */
            {
                /* make sure there are children */
                if ((n = (*tree)->children) != NULL)
                {
                    do /* add all children to queue */
                    {
                        appendNode(&neighbors, n);
                    } while ((n = n->next) != NULL);

                    /* pop the queue and check */
                    while ((n = popNode(&neighbors)) != NULL)
                    {
                        if (n->data == l)
                        {
                            ret = (leaf*)n->data;
                            break;
                        }
                        else if ((n = ((leaf*)(n->data))->children) != NULL)
                        {
                            do /* add all the children of this one to queue */
                            {
                                appendNode(&neighbors, n);
                            } while ((n = n->next) != NULL);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

