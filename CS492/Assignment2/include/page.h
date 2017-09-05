#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* create data structures */
struct fifo
{
    int pageNumber;
    int repChance; /* for Clock page replacement second chance */
    struct fifo* next;
};

struct page
{
    int number;
    int validBit;
    unsigned long timeAccessed; /* for LRU page replacement */
};


struct pageTable
{
    struct page** pages;
    int numPages;
    int numLoaded;
    struct fifo* head; /* for FIFO/Clock page replacement */
};

/* global count of pages, so each page can be given a unique number */
long unsigned int pageSwapCount;

/* declare functions */
struct pageTable* createPageTable(int, int);
void deletePageTable(struct pageTable*);
struct page* createPage();
void validatePage(struct pageTable*, int);
void invalidatePage(struct pageTable*, int);
void pushFifo(struct pageTable*, int);
int popFifo(struct pageTable*);
int indexOfLRUValidPage(struct pageTable*);
void pushClock(struct pageTable*, int);
int popClock(struct pageTable*);
void accessClock(struct pageTable*, int);
int indexOfNextInvalidPage(struct pageTable*, int);

#endif
