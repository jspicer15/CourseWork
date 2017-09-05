/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 file.c
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in an int 's', int 'e' and char 'isFree' which should only have
 *      the values zero or one (respectively false or true)
 * post: creates a new fs_block with the start address of 's', end address of
 *      'e' and 'isFree' to signify if this block is free or used
 * return: a fs_block* pointing to the newly allocated block, or NULL on error
 */
fs_block* createBlock(int s, int e, char isFree)
{
    fs_block* ret;

    if ((ret = (fs_block*)malloc(sizeof(fs_block))) != NULL)
    {
        ret->s_addr = s;
        ret->e_addr = e;
        ret->isFree = isFree;
    }

    return ret;
}

/* pre: takes in a char* 'name', int 'size' and char 'isDirectory' which should
 *      only have the values zero or one (respectively false or true)
 * post: creates an new fs_file with the name 'name' of size 'size' and
 *      'isDirectory' to signify if this file is a regular file or a directory
 * return: a fs_file* pointing to the newly allocated file, or NULL on error
 */
fs_file* createFile(char* name, int size, char isDirectory)
{
    fs_file* ret;

    if ((ret = (fs_file*)malloc(sizeof(fs_file))) != NULL)
    {
        ret->name = strdup(name); /* make sure this gets freed */
        ret->size = size;
        ret->allocatedBlocks = 0; /* file hasn't been allocated yet */
        ret->timestamp = time(NULL);
        ret->isDirectory = isDirectory;
        ret->lfile = NULL; /* empty linked_list */
    }

    return ret;
}

/* pre: takes in an int 'index' and gl.ldisk has been created
 * post: splits gl.ldisk at 'index' such that 'index' starts a new node in
 *      gl.ldisk, and sets the block on the left of the split as used
 */
void splitLdiskNode(int index)
{
    node* n; /* temp node */
    fs_block* b; /* temp block */

    n = gl.ldisk;
    b = (fs_block*)(n->data);

    /* if first node needs to be split */
    if (index < b->e_addr && index >= b->s_addr)
    {
        b->s_addr = index;
        prependNode(&gl.ldisk, createNode((void*)createBlock(0, index, 0)));
    }
    else
    {
        /* while node is not NULL and index is not in this block */
        for (; n != NULL; n = n->next)
        {
            b = (fs_block*)(n->data);
            if (index < b->e_addr && index >= b->s_addr)
                break;
        }

        if (n != NULL)
        {
#ifdef DEBUG
            printf("[DEBUG]\t next free node is block %d\n",
                    ((fs_block*)(n->data))->s_addr);
            fflush(stdout);
#endif
            insertNode(n, createNode((void*)createBlock(index, b->e_addr, 1)));
            b->e_addr = index;
            b->isFree = 0;
        }
        /* else fail silently, future me might hate me for this */
    }
}

/* pre: gl.ldisk has been created
 * post: merges all contiguous nodes in gl.ldisk that are in the same state
 *      (free/used)
 */
void mergeLdiskNodes()
{
    node* n; /* temp node */
    fs_block* b; /* temp block */
    fs_block* nb; /* temp next block */

    n = gl.ldisk;
    b = (fs_block*)(n->data);

    while (n != NULL && n->next != NULL)
    {
        nb = (fs_block*)(n->next->data);

        /* if this block and the next block have the same state, merge them */
        if (b->isFree == nb->isFree)
        {
            b->e_addr = nb->e_addr;
            free(removeNode(n, n->next));
        }

        n = n->next;
    }
}

/* pre: takes in a fs_file* 'file' that has been initialized, and gl.ldisk has
 *      been created
 * post: allocates blocks for 'file'
 */
void allocateFile(fs_file* file)
{
    int numBlocksNeeded; /* the number of blocks needed by the file */
    int i; /* loop counter */
    fs_block* b; /* temp block */
    node* n; /* temp node */

    numBlocksNeeded = (file->size / gl.bsize) - file->allocatedBlocks;
    n = gl.ldisk;

#ifdef DEBUG
    printf("[DEBUG]\tAllocating file <%s> needs %d blocks\n",
            file->name, numBlocksNeeded);
    fflush(stdout);
#endif

    /* only allocate if the number of needed blocks has changed */
    while (numBlocksNeeded > 0)
    {
#ifdef DEBUG
        printf("[DEBUG]\tAllocated %d blocks so far\n", file->allocatedBlocks);
        fflush(stdout);
#endif
        /* iterate forward over gl.ldisk to find the next free node */
        for (; n != NULL && !(((fs_block*)(n->data))->isFree); n = n->next)
            ; /* note empty loop */

        /* if we reached the end without allocating the whole file */
        if (n == NULL)
        {
            fprintf(stderr, "%s: Out of space\n", gl.executable);
            fflush(stderr);

            break;
        }
        else
        {
#ifdef DEBUG
            printf("[DEBUG]\tfound a free node to allocate\n");
            fflush(stdout);
#endif
            b = (fs_block*)(n->data);

            /* if only part of the node is needed */
            if (b->e_addr - b->s_addr > numBlocksNeeded)
            {
#ifdef DEBUG
                printf("[DEBUG]\tonly need part of it\n");
                fflush(stdout);
#endif
                /* update file->lfile */
                for (i = b->s_addr; i < b->s_addr + numBlocksNeeded; i++)
                    appendNode(&(file->lfile), createNode((void*)createBlock(i, i + 1, 0)));

                file->allocatedBlocks += numBlocksNeeded;

#ifdef DEBUG
                printf("[DEBUG]\tneed to split the ldisk node now\n");
                fflush(stdout);
#endif

                /* update gl.ldisk */
                splitLdiskNode(b->s_addr + numBlocksNeeded);
                numBlocksNeeded -= numBlocksNeeded;
            }
            else /* else the whole node is needed */
            {
#ifdef DEBUG
                printf("[DEBUG]\tneed the whole node\n");
                fflush(stdout);
#endif
                file->allocatedBlocks += b->e_addr - b->s_addr;
                numBlocksNeeded -= b->e_addr - b->s_addr;

                /* update file->lfile */
                for (i = b->s_addr; i < b->e_addr; i++)
                    appendNode(&(file->lfile), createNode((void*)createBlock(i, i + 1, 0)));

                /* update gl.ldisk */
                b->isFree = 0;
            }
        }
    }

    /* merge nodes in gl.ldisk */
    mergeLdiskNodes();
#ifdef DEBUG
    printf("[DEBUG]\tAllocated File\n");
    fflush(stdout);
#endif
}

/* pre: takes in a leaf* 'start' and a char* 'name', the data stored in the
 *      nodes of gl.tree must be of the type fs_file*
 * post: finds the the tree node in gl.tree that holds a fs_file* with the name
 *      'name' starting at the node 'start'
 * return: a leaf* that points to the node in gl.tree that holds an fs_file*
 *      with the name 'name', or NULL if such a node is not found
 */
leaf* findInHierarchy(leaf* start, char* name)
{
    leaf* ret;
    leaf* t; /* temp tree */
    node* n;
    node* neighbors; /* linked_list to hold the order for BFS */

    ret = NULL;
    neighbors = NULL;
    t = start;

#ifdef DEBUG
    printf("[DEBUG]\tFind <%s> in global tree\n", name);
    fflush(stdout);
#endif

    /* while node is not null and it's name doesn't match */
    while (t != NULL && strcmp(name, ((fs_file*)(t->data))->name))
    {
#ifdef DEBUG
        printf("[DEBUG]\tBFS working on <%s>\n", ((fs_file*)(t->data))->name);
        fflush(stdout);
#endif
        if ((n = t->children) != NULL)
        {
            do /* add all children to the neighbors queue */
            {
#ifdef DEBUG
                printf("[DEBUG]\tBFS found child <%s>\n",
                        ((fs_file*)(((leaf*)(n->data))->data))->name);
                fflush(stdout);
#endif
                appendNode(&neighbors, createNode(n->data));
            } while ((n = n->next) != NULL);
        }

        if ((n = popNode(&neighbors)) != NULL)
        {
            /* TODO: might be leaking memory from popping off of neighbors */
            t = (leaf*)(n->data);
#ifdef DEBUG
            printf("[DEBUG]\tBFS popped <%s>\n", ((fs_file*)(t->data))->name);
            fflush(stdout);
#endif
        }
        else
            t = NULL;
    }

    if (t != NULL)
#ifdef DEBUG
    {
        printf("[DEBUG]\tfound <%s> in global tree\n", ((fs_file*)(t->data))->name);
        fflush(stdout);
#endif
        ret = t;
#ifdef DEBUG
    }
    else
    {
        printf("[DEBUG]\tdid not find <%s> in global tree\n", name);
        fflush(stdout);
    }
#endif

    return ret;
}

/* pre: takes in a fs_file* 'file' which must be either a valid file or
 *      directory
 * post: adds 'file' to the appropriate position in gl.tree, if the name of
 *      'file' contains 'PATH_SEP' then these are followed to add 'file' as a
 *      child of the appropriate tree node, else 'file' is added as a child of
 *      gl.cur_dir
 */
void addToHierarchy(fs_file* file)
{
    char* name;
    char* part;
    char delim[2];
    leaf* l; /* temp tree node */
    leaf** pd; /* temp tree node (parent dir) */
    int p; /* num path separations */

    pd = NULL;
    if (file != NULL)
    {
        delim[0] = PATH_SEP;
        delim[1] = '\0';
        name = strdup(file->name);

#ifdef DEBUG
        printf("[DEBUG]\tAdding <%s> to the global tree\n", file->name);
        fflush(stdout);
#endif

        if ((p = countPathSeparations(name)))
        {
            part = strtok(name, delim);
            if (part == NULL) /* this is meant to cover '/' as the root */
                part = delim;
            if ((l = findInHierarchy(gl.tree, part)) != NULL)
                pd = &l;
            while (p--)
            {
                part = strtok(NULL, delim);
                if (p > 0)
                    if ((l = findInHierarchy(gl.tree, part)) != NULL)
                        pd = &l;
            }

            if (pd == NULL || (*pd) == NULL)
            {
                fprintf(stderr, "%s: could not find directory\n", gl.executable);
                fflush(stderr);

                return;
            }
            else
            {

#ifdef DEBUG
                printf("[DEBUG]\t<%s> name shortened to <%s> in parent dir <%s>\n",
                        file->name, part, ((fs_file*)((*pd)->data))->name);
                fflush(stdout);
#endif

                /* we're making the file name shorter so strcpy should be fine */
                file->name = strcpy(file->name, part);

#ifdef DEBUG
                printf("[DEBUG]\tsanity check <%s>\n", file->name);
                fflush(stdout);
#endif
                /* TODO: possible memory leak? */
            }
        }
        else
        {
            if (gl.cur_dir != NULL)
                pd = &gl.cur_dir;
            else
                pd = &gl.tree;
        }


        free(name);

        /* append to the tree */
        appendLeaf(pd, createLeaf((void*)file));
    }
}

/* pre: takes in a char* 'fname' which is a file name
 * post: counts the number of occurances of the path separator 'PATH_SEP' in
 *      'fname'
 * return: an integer which is the number of occurances of 'PATH_SEP' in 'fname'
 */
int countPathSeparations(char* fname)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < strlen(fname); i++)
        if (fname[i] == PATH_SEP)
            count++;

    return count;
}

/* pre: takes in a fs_file* 'file'
 * post: build the full path name of 'file' from the gl.tree
 * return: a char* that is the full path name of 'file'
 */
char* getFullPath(fs_file* file)
{
    char* ret;
    char* parent;
    leaf* target;

    ret = (char*)malloc(1024*sizeof(char));
    target = findInHierarchy(gl.tree, file->name);

    if (target->parent != NULL)
    {
        /* TODO: probably leaking memory here */
        parent = getFullPath((fs_file*)target->parent->data);
        if (file->isDirectory)
        {
            sprintf(ret, "%s%s%c",
                    parent,
                    file->name,
                    PATH_SEP);
        }
        else
        {
            sprintf(ret, "%s%s",
                    parent,
                    file->name);
        }
    }
    else
    {
        if (file->isDirectory)
        {
            sprintf(ret, "%s%c",
                    file->name,
                    PATH_SEP);
        }
        else
        {
            sprintf(ret, "%s",
                    file->name);
        }
    }

    return ret;
}

