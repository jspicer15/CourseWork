#ifndef _VMSIMULATOR_H_
#define _VMSIMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "page.h"

/* maximum number of memory locations */
#define MAX_MEM 512

/* maximum page size */
#define MAX_PAGE_SIZE 32

/* options for defining page replacement method */
#define FIFO "FIFO"
#define LRU "LRU"
#define CLOCK "Clock"

/* global counter of page swaps */
unsigned long gl_page_swaps;

int main(int, char**);
int powerChecker(int);
int processCounter(FILE*);
void demandSwap(char*, struct pageTable*, int, int, unsigned long);
void prePagingSwap(char*, struct pageTable*, int, int, unsigned long);

#endif