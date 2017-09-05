/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page_table.c
 * 04/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

/* define NO_SPAM to silence very spammy DEBUG messages */
#define NO_SPAM

#include "page.h"

/* pre: takes in ints pSize and pTotal
 * post: creates a new page table with page size 'pSize' and number of memory
 *      locations 'pTotal'
 * return: a pointer to the newly created page table or NULL on error
 */
ptable* createPageTable(int pSize, int pTotal)
{
    ptable* ret;
    page* p;
    int i;
    int numPages = (int)ceil((double)pTotal / pSize);

#ifdef DEBUG
    printf("[DEBUG]\tCreating page table: page size [%d] num mem locs [%d]\n",
            pSize, pTotal);
    fflush(stdout);
#endif

    ret = (ptable*)malloc(sizeof(ptable));
    if (ret != NULL)
    {
        ret->pages = (page**)malloc(sizeof(page*)*numPages);
        if (ret->pages != NULL)
        {
            ret->numPages = numPages;
            ret->numLoaded = 0;

            for (i = 0; i < numPages; i++)
            {
                p = createPage();
                if (p == NULL)
                {
                    printf("[ERROR]\tCould not malloc a new page!\n");
                    fflush(stdout);
                    break;
                }
                ret->pages[i] = p;
            }

            ret->fifoHead = NULL;
        }
    }

    return ret;
}

/* pre: takes in a ptable* p
 * post: frees the memory associated with the page table p
 */
void deletePageTable(ptable* p)
{
    int i;

    if (p != NULL)
    {
        for (i = 0; i < p->numPages; i++)
        {
            if (p->pages[i] != NULL)
                free(p->pages[i]);
        }
        free(p->pages);
        free(p);
    }
}

/* pre: none
 * post: creates a new page with a unique number
 * return: a pointer to the newly created page or NULL on error
 */
page* createPage()
{
    page* ret;

    ret = (page*)malloc(sizeof(page));
    if (ret != NULL)
    {
        if (!gl_pages_total)
            gl_pages_total = 0;
        ret->number = ++gl_pages_total;
        ret->valid = 0;
        ret->accessed = 0;
    }

    return ret;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable* and an integer
 *      'n' which must be >= 0 and < 'tab'->numPages
 * post: sets page 'n' of 'tab' to valid and increments the number of loaded
 *      pages in 'tab'
 */
void validatePage(ptable* tab, int n)
{
    tab->pages[n]->valid = 1;
    tab->numLoaded++;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable* and an integer
 *      'n' which must be >= 0 and < 'tab'->numPages
 * post: sets page 'n' of 'tab' to invalid and decrements the number of loaded
 *      pages in 'tab'
 */
void invalidatePage(ptable* tab, int n)
{
    tab->pages[n]->valid = 0;
    tab->numLoaded--;
}

/* pre: takes in a ptable* 'tab' and an int 'num', 'tab' must be a valid ptable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: allocates and adds an entry to 'tab's fifoHead representing the page at
 *      index 'num'
 */
void pushFifo(ptable* tab, int num)
{
    fifo* tmp;
    fifo* n;

#if defined (DEBUG) && !defined (NO_SPAM)
    printf("[DEBUG]\tPush FIFO [%d]\n", num);
    fflush(stdout);
#endif

    n = (fifo*)malloc(sizeof(fifo));
    if (n != NULL)
    {
        n->pageNum = num;
        n->next = NULL;

        if (tab->fifoHead == NULL)
            tab->fifoHead = n;
        else
        {
            tmp = tab->fifoHead;

            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = n;
        }
    }
    else
        printf("[ERROR]\tCould not allocate memory for FIFO entry!\n");
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*
 * post: pops an entry off of 'tab's fifoHead
 * return: an integer that is the pageNumber of the entry popped off 'tab' or -1
 *      if no entry existed
 */
int popFifo(ptable* tab)
{
    int ret;
    fifo* tmp;

    ret = -1;
    if (tab->fifoHead != NULL)
    {
        tmp = tab->fifoHead->next;

        ret = tab->fifoHead->pageNum;
        free(tab->fifoHead);
        tab->fifoHead = tmp;
    }

#if defined (DEBUG) && !defined (NO_SPAM)
    printf("[DEBUG]\tPop FIFO [%d]\n", ret);
    fflush(stdout);
#endif

    return ret;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*
 * post: returns the index of the least recently used valid (loaded) page
 * return: an integer that is the index of the least recently used valid
 *      (loaded) page in 'tab' or -1 if one does not exist
 */
int indexOfLRUValidPage(ptable* tab)
{
    int i;
    int ret;
    unsigned long min;

    ret = -1;
    min = -1; /* this will set min to the MAX */
    for (i = 0; i < tab->numPages; i++)
    {
        if (!tab->pages[i]->valid)
            continue;

        if (tab->pages[i]->accessed < min)
        {
            min = tab->pages[i]->accessed;
            ret = i;
        }
    }

    return ret;
}

/* pre: takes in a ptable* 'tab' and an int 'num', 'tab' must be a valid ptable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: allocates and adds an entry to 'tab's fifoHead representing the page at
 *      index 'num' accounting for Clock swapping
 */
void pushClock(ptable* tab, int num)
{
    fifo* tmp;
    fifo* n;

#if defined (DEBUG) && !defined (NO_SPAM)
    printf("[DEBUG]\tPush Clock FIFO [%d]\n", num);
    fflush(stdout);
#endif

    n = (fifo*)malloc(sizeof(fifo));
    if (n != NULL)
    {
        n->pageNum = num;
        n->chance = 1;
        n->next = NULL;

        if (tab->fifoHead == NULL)
            tab->fifoHead = n;
        else
        {
            tmp = tab->fifoHead;

            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = n;
        }
    }
    else
        printf("[ERROR]\tCould not allocate memory for Clock FIFO entry!\n");
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*
 * post: pops an entry off of 'tab's fifoHead accounting for Clock swapping
 * return: an integer that is the pageNumber of the entry popped off 'tab'
 *      accounting for Clock swapping or -1 if no entry existed
 */
int popClock(ptable* tab)
{
    int ret;
    fifo* tmp;
    fifo* f;

    ret = -1;
    if (tab->fifoHead != NULL)
    {
        tmp = tab->fifoHead;

        while (1)
        {
            if (tmp->chance) /* set chance to zero and add to end */
            {
                tmp->chance = 0;

                /* update in place if fifoHead has one element */
                if (tab->fifoHead->next != NULL)
                    tab->fifoHead = tmp->next;

                f = tmp;
                while (f->next != NULL)
                    f = f->next;
                f->next = tmp;
                tmp->next = NULL;

                /* start again at the new head */
                tmp = tab->fifoHead;
            }
            else /* return this one */
            {
                ret = tmp->pageNum;
                tab->fifoHead = tmp->next;
                free(tmp);
                break;
            }
        }
    }

#if defined (DEBUG) && !defined (NO_SPAM)
    printf("[DEBUG]\tPop Clock FIFO [%d]\n", ret);
    fflush(stdout);
#endif

    return ret;
}

/* pre: takes in a ptable* 'tab' and an int 'num', 'tab' must be a valid ptable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: resets the entry in 'tab's fifoHead for the page at index 'num' chance
 *      variable to 1
 */
void accessClock(ptable* tab, int num)
{
    fifo* tmp;

    if (tab->fifoHead != NULL)
    {
        tmp = tab->fifoHead;

        while (tmp->pageNum != num && tmp->next != NULL)
            tmp = tmp->next;
        if (tmp->pageNum == num)
            tmp->chance = 1;
    }
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*, and an integer
 *      's' which is >= 0 and < 'tab'->numPages
 * post: returns the index of the next invalid (unloaded) page starting at 's'
 * return: an integer index of the next invalid (unloaded) page in 'tab' or -1
 *      if one does not exist
 */
int indexOfNextInvalidPage(ptable* tab, int s)
{
    int startPos;

    startPos = s;
    while (tab->pages[s]->valid)
    {
        s = (s + 1) % tab->numPages;

        /* if we get back to the startPos without finding an invalid page */
        if (s == startPos)
        {
            s = -1;
            break;
        }
    }

    return s;
}

