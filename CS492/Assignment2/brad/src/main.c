/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 main.c
 * 04/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

/* define NO_SPAM to silence very spammy DEBUG messages */
#define NO_SPAM

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
    int numProcs; /* number of processes in plist */
    ptable** proc_ptables; /* list of page tables (one for each process in plist) */
    int perProcMem; /* amount of memory locations in main memory per process */
    unsigned long cycle; /* "clock" cycle for LRU */

    /* temporary variables and return codes  */
    int i;
    int j;
    char* line;
    size_t len;
    ssize_t ret;
    ptable* temp_ptable;

    /* verifiy number of arguments */
    if (argc != 6)
    {
        printf("usage: %s <plist> <ptrace> <page size> <FIFO|LRU|Clock> <+|- pre-paging on/off>\n",
                argv[0]);
        return 1;
    }
    else /* parse and error check arguments */
    {
        plist = argv[1];
        ptrace = argv[2];

        pageSize = atoi(argv[3]);
        if (pageSize <= 0 || !isPowTwo(pageSize) || pageSize > MAX_PAGE_SIZE)
        {
            printf("[ERROR]\tInvalid page size [%s]!\n", argv[3]);
            printf("       \tPlease use a positive power of 2 up to 32\n");
            return 1;
        }

        pageReplacement = argv[4];
        if (strcmp(pageReplacement, OPT_FIFO) &&
            strcmp(pageReplacement, OPT_LRU) &&
            strcmp(pageReplacement, OPT_CLOCK))
        {
            printf("[ERROR]\tInvalid page replacement method!\n");
            printf("       \tPlease use one of: [%s], [%s] or [%s]\n",
                    OPT_FIFO, OPT_LRU, OPT_CLOCK);
            return 1;
        }

        if (!strcmp(argv[5], "+"))
            prePaging = 1;
        else if (!strcmp(argv[5], "-"))
            prePaging = 0;
        else
        {
            printf("[ERROR]\tInvalid value for pre-paging!\n");
            printf("       \tPlease use either [+] for on or [-] for off\n");
            return 1;
        }

#ifdef DEBUG
        printf("[DEBUG]\tplist: %s\n[DEBUG]\tptrace: %s\n[DEBUG]\tpageSize: %d\n\
[DEBUG]\tpageReplacement: %s\n[DEBUG]\tprePaging: %d\n",
            plist, ptrace, pageSize, pageReplacement, prePaging);
        fflush(stdout);
#endif
    }

    /* initialize page swap counter to zero for start */
    gl_page_swaps = 0;

    /* open files for reading */
    plistfd = fopen(plist, "r");
    if (plistfd == NULL)
    {
        printf("[ERROR]\tCould not open plist file!\n");
        return 1;
    }
    ptracefd = fopen(ptrace, "r");
    if (ptracefd == NULL)
    {
        printf("[ERROR]\tCould not open ptrace file!\n");
        return 1;
    }

    /* read from plist to count the number of lines (processes) */
    numProcs = countProcs(plistfd);

#ifdef DEBUG
    printf("[DEBUG]\t%d processes detected\n", numProcs);
    fflush(stdout);
#endif

    /* skip over everything if we have zero or less processes */
    if (numProcs > 0)
    {
        /* create a list of page tables (one for each process) */
        proc_ptables = (ptable**)malloc(sizeof(ptable*)*numProcs);
        if (proc_ptables == NULL)
        {
            printf("[ERROR]\t could not allocate memory for page tables!\n");
            return 1;
        }

        /* move the fd back to the start of the file so we can read it again */
        rewind(plistfd);

        /* read from plist again to setup proc_ptables */
        i = 0;
        line = NULL;
        len = 0;
        while ((ret = getline(&line, &len, plistfd)) != -1)
        {
            /* skip over all empty lines */
            if (!strcmp(line, "\n"))
                continue;

#if defined (DEBUG) && !defined (NO_SPAM)
            printf("[DEBUG]\tRead plist line: %s", line);
            fflush(stdout);
#endif

            /* this returns the PID, next strtok will be the mem locs */
            strtok(line, " ");
            proc_ptables[i] = createPageTable(pageSize, atoi(strtok(NULL, " ")));
            if (proc_ptables[i] == NULL)
            {
                printf("[ERROR]\tCould not allocate memory for page table!\n");
                return 1;
            }
            i++;
        }

        /* load initial main memory */
        perProcMem = (int)floor((double)MAX_MEM / (numProcs * pageSize));

#ifdef DEBUG
        printf("[DEBUG]\tEach process gets %d main mem entries\n", perProcMem);
        fflush(stdout);
#endif

        /* for each program set the first perProcMem pages as valid (in main mem ) */
        for (i = 0; i < numProcs; i++)
        {
            for (j = 0; j < perProcMem && j < proc_ptables[i]->numPages; j++)
            {
                validatePage(proc_ptables[i], j);

#if defined (DEBUG) && !defined (NO_SPAM)
                printf("[DEBUG]\tInitial load: [%d] [%d] = [%d]\n",
                        i, j, proc_ptables[i]->pages[j]->valid);
                fflush(stdout);
#endif

                /* if we're using FIFO or Clock page replacement */
                if (!strcmp(pageReplacement, OPT_FIFO))
                    pushFifo(proc_ptables[i], j);
                else if (!strcmp(pageReplacement, OPT_CLOCK))
                    pushClock(proc_ptables[i], j);
            }

#ifdef DEBUG
            printf("[DEBUG]\tProcess [%d] loaded [%d] pages\n",
                    i,
                    proc_ptables[i]->numLoaded);
            fflush(stdout);
#endif
        }

        /* read from ptrace and run the simulation */
        free(line);
        line = NULL;
        len = 0;
        cycle = 1;
        while ((ret = getline(&line, &len, ptracefd)) != -1)
        {
            /* skip over all empty lines */
            if (!strcmp(line, "\n"))
                continue;

#if defined (DEBUG) && !defined (NO_SPAM)
            printf("[DEBUG]\tRead ptrace line: %s", line);
            fflush(stdout);
#endif

            /* this returns the PID, next strtok will be the mem loc to access */
            i = atoi(strtok(line, " "));

            /* set temporary page table to this program's page table */
            temp_ptable = proc_ptables[i];

            /* get mem loc to access */
            j = atoi(strtok(NULL, " "));
            j = (int)ceil((double)j/pageSize);
            j--; /* translate to zero index */

            /* 'i' is now the process number and 'j' is now the page number to access */

#if defined (DEBUG) && !defined (NO_SPAM)
            printf("[DEBUG]\tAbout to access process [%d] page [%d] of [%d] total pages\n",
                    i,
                    j,
                    temp_ptable->numPages);
            fflush(stdout);
#endif

            /* try to access temp_ptable->pages[j] */
            if (temp_ptable->pages[j]->valid) /* page hit (in main memory) */
            {
                if (!strcmp(pageReplacement, OPT_LRU))
                    temp_ptable->pages[j]->accessed = cycle;
                else if (!strcmp(pageReplacement, OPT_CLOCK))
                    accessClock(temp_ptable, j);
            }
            else /* page miss (need to swap) */
            {
                /* record this page fault */
                gl_page_swaps++;

                if (prePaging)
                    prePagingSwap(pageReplacement, temp_ptable, j, perProcMem, cycle);
                else /* demand paging */
                    demandSwap(pageReplacement, temp_ptable, j, perProcMem, cycle);
            }

            /* check to make sure process is within memory limits */
            if (temp_ptable->numLoaded > perProcMem)
            {
                printf("[ERROR]\tProcess has exceeded memory!\n");
                return 1;
            }

            /* update cycle counter for LRU */
            cycle++;
        }
        free(line);
    }

    /* close files, ignoring any errors on close */
    fclose(plistfd);
    fclose(ptracefd);

    /* free memory */
    if (proc_ptables)
    {
        for (i = 0; i < numProcs; i++)
            deletePageTable(proc_ptables[i]);
        free(proc_ptables);
    }

    /* print total number of page swaps on exit */
    printf("Total page swaps: %lu\n", gl_page_swaps);
    return 0;
}

