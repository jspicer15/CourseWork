/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 linked_list.c
 * 05/01/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "linked_list.h"

/* pre: takes in a void* 'data'
 * post: allocates a new linked list node holding 'data'
 * return: a node* pointing to the newly allocated linked list node, or NULL on
 *      error
 */
node* createNode(void* data)
{
    node* ret;

    ret = NULL;
    if (data != NULL)
    {
        if ((ret = (node*)malloc(sizeof(node))) != NULL)
        {
            ret->data = data;
            ret->next = NULL;
        }
    }

    return ret;
}

/* pre: takes in a node** 'list' and a node* 'n'
 * post: appends 'n' to the end of the linked list pointed to by 'list'
 */
void appendNode(node** list, node* n)
{
    node* tmp;

    if (n != NULL)
    {
        if ((*list) == NULL)
            (*list) = n;
        else
        {
            for (tmp = (*list); tmp->next != NULL; tmp = tmp->next)
                ; /* note the empty loop */
            tmp->next = n;
        }
    }
}

/* pre: takes in a node** 'list' and a node* 'n'
 * post: prepends 'n' to the beginning of the linked list pointed to by 'list'
 */
void prependNode(node** list, node* n)
{
    n->next = (*list);
    (*list) = n;
}

/* pre: takes in a node* 'first' and a node* 'second'
 * post: inserts 'second' into the linked list right after 'first'
 */
void insertNode(node* first, node* second)
{
    second->next = first->next;
    first->next = second;
}

/* pre: takes in a node** 'list'
 * post: removes the first node from 'list'
 * return: a node* pointing to the node removed from 'list'
 */
node* popNode(node** list)
{
    node* ret;

    ret = NULL;
    if ((*list) != NULL)
    {
        ret = (*list);
        (*list) = (*list)->next;
    }

    return ret;
}

/* pre: takes in a node* 'first' and a node* 'second', where 'second' is the
 *      node to be removed and 'first' is the node immediately before it
 * post: removes 'second' from the linked list
 * return: a node* pointing to the node that was removed
 */
node* removeNode(node* first, node* second)
{
    node* ret;

    ret = second;
    first->next = second->next;
    second->next = NULL;

    return ret;
}

