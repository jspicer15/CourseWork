#include "VMsimulator.h"

/* pre: takes in a char* 'method', pageTable* 'tab', integer 'n', integer 'limit'
 *      and unsigned long 'cycle', where 'method' is either FIFO, LRU,
 *      or CLOCK, 'tab' is a valid pageTable*, 'n' is >= 0 and < 'tab'->numPages,
 *      'limit' is > 0, and cycle is >= 0
 * post: swaps in page 'n' in 'tab' using demand paging and 'method' page replacement
 *      method
 */
void demandSwap(char* method, struct pageTable* tab, int n, int limit, unsigned long cycle)
{
    int i;

    if (!strcmp(method, FIFO))
    {
        /* invalidate one page */
        i = popFifo(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load the faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushFifo(tab, n);
        }
    }
    else if (!strcmp(method, LRU))
    {
        /* invalidate one page */
        i = indexOfLRUValidPage(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load the faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            tab->pages[n]->accessed = cycle;
        }
    }
    else /* Clock replacement */
    {
        /* invalidate one page */
        i = popClock(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushClock(tab, n);
        }
    }
}

/* pre: takes in a char* 'method', pageTable* 'tab', integer 'n', integer 'limit'
 *      and unsigned long 'cycle', where 'method' is either FIFO, LRU,
 *      or CLOCK, 'tab' is a valid pageTable*, 'n' is >= 0 and < 'tab'->numPages,
 *      'limit' is > 0, and cycle is >= 0
 * post: swaps in page 'n' in 'tab' using pre-paging and 'method' page replacement
 *      method
 */
void prePagingSwap(char* method, struct pageTable* tab, int n, int limit, unsigned long cycle)
{
    int i;

    if (!strcmp(method, FIFO))
    {
        /* invalidate two pages */
        i = popFifo(tab);
        if (i > -1)
            invalidatePage(tab, i);
        i = popFifo(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load the faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushFifo(tab, n);
        }

        /* search for the next page that can be loaded */
        n++;
        if (n == tab->numPages)
            n = 0;
        n = indexOfNextInvalidPage(tab, n);
        if (n != -1 && tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushFifo(tab, n);
        }
    }
    else if (!strcmp(method, LRU))
    {
        /* invalidate two pages */
        i = indexOfLRUValidPage(tab);
        if (i > -1)
            invalidatePage(tab, i);
        i = indexOfLRUValidPage(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load the faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            tab->pages[n]->accessed = cycle;
        }

        /* search for the next page that can be loaded */
        n++;
        if (n == tab->numPages)
            n = 0;
        n = indexOfNextInvalidPage(tab, n);
        if (n != -1 && tab->numLoaded < limit)
        {
            validatePage(tab, n);
            tab->pages[n]->accessed = cycle;
        }
    }
    else /* Clock replacement */
    {
        /* invalidate two pages */
        i = popClock(tab);
        if (i > -1)
            invalidatePage(tab, i);
        i = popClock(tab);
        if (i > -1)
            invalidatePage(tab, i);

        /* load the faulted page */
        if (tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushClock(tab, n);
        }

        /* search for the next page that can be loaded */
        n++;
        if (n == tab->numPages)
            n = 0;
        n = indexOfNextInvalidPage(tab, n);
        if (n != -1 && tab->numLoaded < limit)
        {
            validatePage(tab, n);
            pushClock(tab, n);
        }
    }
}

