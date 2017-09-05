/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 tree.h
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "linked_list.h"

struct s_leaf {
    void* data;
    struct s_leaf* parent;
    node* children; /* a linked_list which holds other leaves */
};

typedef struct s_leaf leaf;

leaf* createLeaf(void*);
void  appendLeaf(leaf**, leaf*);
leaf* removeLeaf(leaf**, leaf*);

#endif /* _TREE_H_ */
