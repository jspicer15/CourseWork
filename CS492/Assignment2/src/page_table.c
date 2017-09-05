#include "VMsimulator.h"

/* pre: takes in ints pSize and pTotal
 * post: creates a new page table with page size 'pSize' and number of memory
 *      locations 'pTotal'
 * return: a pointer to the newly created page table or NULL on error
 */
struct pageTable* createPageTable(int pSize, int pTotal)
{
    struct pageTable* ret;
    struct page* p;
    int i;
    int numPages = (int)ceil((double)pTotal / pSize);

    ret = (struct pageTable*)malloc(sizeof(struct pageTable));
    if (ret != NULL)
    {
        ret->pages = (struct page**)malloc(sizeof(struct page*)*numPages);
        if (ret->pages != NULL)
        {
            ret->numPages = numPages;
            ret->numLoaded = 0;

            for (i = 0; i < numPages; i++)
            {
                p = createPage();
                if (p == NULL)
                {
                    printf("Error allocating memory for new page\n");
                    fflush(stdout);
                    break;
                }
                ret->pages[i] = p;
            }

            ret->head = NULL;
        }
    }

    return ret;
}

/* pre: none
 * post: creates a new page with a unique number
 * return: a pointer to the newly created page or NULL on error
 */
struct page* createPage()
{
    struct page* ret;

    ret = (struct page*)malloc(sizeof(struct page));
    if (ret != NULL)
    {
        if (!pageSwapCount)
            pageSwapCount = 0;
        ret->number = ++pageSwapCount;
        ret->validBit = 0;
        ret->timeAccessed = 0;
    }

    return ret;
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable* and an integer
 *      'n' which must be >= 0 and < 'tab'->numPages
 * post: sets page 'n' of 'tab' to validBit and increments the number of loaded
 *      pages in 'tab'
 */
void validatePage(struct pageTable* tab, int n)
{
    tab->pages[n]->validBit = 1;
    tab->numLoaded++;
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable* and an integer
 *      'n' which must be >= 0 and < 'tab'->numPages
 * post: sets page 'n' of 'tab' to invalid and decrements the number of loaded
 *      pages in 'tab'
 */
void invalidatePage(struct pageTable* tab, int n)
{
    tab->pages[n]->validBit = 0;
    tab->numLoaded--;
}

/* pre: takes in a struct pageTable* 'tab' and an int 'num', 'tab' must be a validBit struct pageTable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: allocates and adds an entry to 'tab's head representing the page at
 *      index 'num'
 */
void pushFifo(struct pageTable* tab, int num)
{
    struct fifo* tmp;
    struct fifo* n;

    n = (struct fifo*)malloc(sizeof(struct fifo));
    if (n != NULL)
    {
        n->pageNumber = num;
        n->next = NULL;

        if (tab->head == NULL)
            tab->head = n;
        else
        {
            tmp = tab->head;

            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = n;
        }
    }
    else
        printf("Error allocating memory with struct fifo\n");
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable*
 * post: pops an entry off of 'tab's head
 * return: an integer that is the pageNumber of the entry popped off 'tab' or -1
 *      if no entry existed
 */
int popFifo(struct pageTable* tab)
{
    int ret;
    struct fifo* tmp;

    ret = -1;
    if (tab->head != NULL)
    {
        tmp = tab->head->next;

        ret = tab->head->pageNumber;
        free(tab->head);
        tab->head = tmp;
    }

    return ret;
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable*
 * post: returns the index of the least recently used validBit (loaded) page
 * return: an integer that is the index of the least recently used validBit
 *      (loaded) page in 'tab' or -1 if one does not exist
 */
int indexOfLRUValidPage(struct pageTable* tab)
{
    int i;
    int ret;
    unsigned long min;

    ret = -1;
    min = -1; /* this will set min to the MAX */
    for (i = 0; i < tab->numPages; i++)
    {
        if (!tab->pages[i]->validBit)
            continue;

        if (tab->pages[i]->timeAccessed < min)
        {
            min = tab->pages[i]->timeAccessed;
            ret = i;
        }
    }

    return ret;
}

/* pre: takes in a struct pageTable* 'tab' and an int 'num', 'tab' must be a validBit struct pageTable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: allocates and adds an entry to 'tab's head representing the page at
 *      index 'num' accounting for Clock swapping
 */
void pushClock(struct pageTable* tab, int num)
{
    struct fifo* tmp;
    struct fifo* n;

    n = (struct fifo*)malloc(sizeof(struct fifo));
    if (n != NULL)
    {
        n->pageNumber = num;
        n->repChance = 1;
        n->next = NULL;

        if (tab->head == NULL)
            tab->head = n;
        else
        {
            tmp = tab->head;

            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = n;
        }
    }
    else
        printf("Error pushing with Clock struct fifo\n");
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable*
 * post: pops an entry off of 'tab's head accounting for Clock swapping
 * return: an integer that is the pageNumber of the entry popped off 'tab'
 *      accounting for Clock swapping or -1 if no entry existed
 */
int popClock(struct pageTable* tab)
{
    int ret;
    struct fifo* tmp;
    struct fifo* f;

    ret = -1;
    if (tab->head != NULL)
    {
        tmp = tab->head;

        while (1)
        {
            if (tmp->repChance) /* set repChance to zero and add to end */
            {
                tmp->repChance = 0;

                /* update in place if head has one element */
                if (tab->head->next != NULL)
                    tab->head = tmp->next;

                f = tmp;
                while (f->next != NULL)
                    f = f->next;
                f->next = tmp;
                tmp->next = NULL;

                /* start again at the new head */
                tmp = tab->head;
            }
            else /* return this one */
            {
                ret = tmp->pageNumber;
                tab->head = tmp->next;
                free(tmp);
                break;
            }
        }
    }

    return ret;
}

/* pre: takes in a struct pageTable* 'tab' and an int 'num', 'tab' must be a validBit struct pageTable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: resets the entry in 'tab's head for the page at index 'num' repChance
 *      variable to 1
 */
void accessClock(struct pageTable* tab, int num)
{
    struct fifo* tmp;

    if (tab->head != NULL)
    {
        tmp = tab->head;

        while (tmp->pageNumber != num && tmp->next != NULL)
            tmp = tmp->next;
        if (tmp->pageNumber == num)
            tmp->repChance = 1;
    }
}

/* pre: takes in a struct pageTable* 'tab' which must be a validBit struct pageTable*, and an integer
 *      's' which is >= 0 and < 'tab'->numPages
 * post: returns the index of the next invalid (unloaded) page starting at 's'
 * return: an integer index of the next invalid (unloaded) page in 'tab' or -1
 *      if one does not exist
 */
int indexOfNextInvalidPage(struct pageTable* tab, int s)
{
    int startPos;

    startPos = s;
    while (tab->pages[s]->validBit)
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

