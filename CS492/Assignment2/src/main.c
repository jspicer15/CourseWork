#include "VMsimulator.h"

/* pre: takes in int argc and char** argv command line agruments
 * post: runs the virtual memory simulation program
 * return: 0 on success, else 1
 */
int main(int argc, char** argv)
{
    /* parameters */
    char* plist; /* path to plist file */
    char* ptrace; /* path to ptrace file */
    int pageSize; /* page size */
    char* pageReplacement; /* page replacement method */
    int prePaging; /* "boolean" for pre-paging vs demand */

    /* other variables */
    FILE* plistfd; /* file handle for plist file */
    FILE* ptracefd; /* file handle for ptrace file */
    int processCount; /* number of processes in plist */
    struct pageTable** pageTables; /* list of page tables (one for each process in plist) */
    int perProcMem; /* amount of memory locations in main memory per process */
    unsigned long cycle; /* "clock" cycle for LRU */

    /* temporary variables and return codes  */
    int i;
    int j;
    char* line;
    size_t len;
    ssize_t ret;
    struct pageTable* temp_ptable;

    /* verifiy number of arguments */
    if (argc != 6)
    {
        printf("usage: %s <path to plist> <path to ptrace> <page size> <page replacement algorithm> <pre-paging on/off (+/-)>\n",
                argv[0]);
        return -1;
    }
    else /* parse and error check arguments */
    {
        plist = argv[1];
        ptrace = argv[2];

        pageSize = atoi(argv[3]);
        if (pageSize <= 0 || !powerChecker(pageSize) || pageSize > MAX_PAGE_SIZE)
        {
            printf("Error in page size\n");
            printf("Use a power of 2 up to max of 32\n");
            return -1;
        }

        pageReplacement = argv[4];
        if (strcmp(pageReplacement, FIFO) &&
            strcmp(pageReplacement, LRU) &&
            strcmp(pageReplacement, CLOCK))
        {
            printf("Incorrect page replacement algorithmn");
            printf("Use FIFO, LRU, or CLOCK");
            return -1;
        }

        if (!strcmp(argv[5], "+"))
            prePaging = 1;
        else if (!strcmp(argv[5], "-"))
            prePaging = 0;
        else
        {
            printf("Incorrect pre-paging value\n");
            printf("Use either + or -\n");
            return -1;
        }

    }

    /* initialize page swap counter to zero for start */
    pageSwapCount = 0;

    /* open files for reading */
    plistfd = fopen(plist, "r");
    if (plistfd == NULL)
    {
        printf("Could not find plist file\n");
        return -1;
    }
    ptracefd = fopen(ptrace, "r");
    if (ptracefd == NULL)
    {
        printf("Could not find ptrace file\n");
        return -1;
    }

    /* read from plist to count the number of lines (processes) */
    processCount = processCounter(plistfd);

    /* skip over everything if we have zero or less processes */
    if (processCount > 0)
    {
        /* create a list of page tables (one for each process) */
        pageTables = (struct pageTable**)malloc(sizeof(struct pageTable*)*processCount);
        if (pageTables == NULL)
        {
            printf("Error allocating memory\n");
            return -1;
        }

        /* move the fd back to the start of the file so we can read it again */
        rewind(plistfd);

        /* read from plist again to setup pageTables */
        i = 0;
        line = NULL;
        len = 0;
        while ((ret = getline(&line, &len, plistfd)) != -1)
        {
            /* skip over all empty lines */
            if (!strcmp(line, "\n"))
                continue;

            /* this returns the PID, next strtok will be the mem locs */
            strtok(line, " ");
            pageTables[i] = createPageTable(pageSize, atoi(strtok(NULL, " ")));
            if (pageTables[i] == NULL)
            {
                printf("Error allocating memory\n");
                return 1;
            }
            i++;
        }

        /* load initial main memory */
        perProcMem = (int)floor((double)MAX_MEM / (processCount * pageSize));


        /* for each program set the first perProcMem pages as valid (in main mem ) */
        for (i = 0; i < processCount; i++)
        {
            for (j = 0; j < perProcMem && j < pageTables[i]->numPages; j++)
            {
                validatePage(pageTables[i], j);

                /* if we're using FIFO or Clock page replacement */
                if (!strcmp(pageReplacement, FIFO))
                    pushFifo(pageTables[i], j);
                else if (!strcmp(pageReplacement, CLOCK))
                    pushClock(pageTables[i], j);
            }

        }

        /* read from ptrace and run the simulation */
        line = NULL;
        len = 0;
        cycle = 1;
        while ((ret = getline(&line, &len, ptracefd)) != -1)
        {
            /* skip over all empty lines */
            if (!strcmp(line, "\n"))
                continue;

            /* this returns the PID, next strtok will be the mem loc to access */
            i = atoi(strtok(line, " "));

            /* set temporary page table to this program's page table */
            temp_ptable = pageTables[i];

            /* get mem loc to access */
            j = atoi(strtok(NULL, " "));
            j = (int)ceil((double)j/pageSize);
            j--; /* translate to zero index */

            /* 'i' is now the process number and 'j' is now the page number to access */


            /* try to access temp_ptable->pages[j] */
            if (temp_ptable->pages[j]->valid) /* page hit (in main memory) */
            {
                if (!strcmp(pageReplacement, LRU))
                    temp_ptable->pages[j]->accessed = cycle;
                else if (!strcmp(pageReplacement, CLOCK))
                    accessClock(temp_ptable, j);
            }
            else /* page miss (need to swap) */
            {
                /* record this page fault */
                pageSwapCount++;

                if (prePaging)
                    prePagingSwap(pageReplacement, temp_ptable, j, perProcMem, cycle);
                else /* demand paging */
                    demandSwap(pageReplacement, temp_ptable, j, perProcMem, cycle);
            }

            /* check to make sure process is within memory limits */
            if (temp_ptable->numLoaded > perProcMem)
            {
                printf("Process exceeded available memory\n");
                return 1;
            }

            /* update cycle counter for LRU */
            cycle++;
        }
    }

    /* close files, ignoring any errors on close */
    fclose(plistfd);
    fclose(ptracefd);

    /* print total number of page swaps on exit */
    printf("Total page swaps: %lu\n", pageSwapCount);
    return 0;
}

