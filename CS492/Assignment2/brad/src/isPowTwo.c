/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 isPowTwo.c
 * 03/29/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "VMsimulator.h"

/* pre: takes in an integer 'n' which is a positive number
 * post: checks if 'n' is a power of 2
 * return: 1 if 'n' is a power of 2, else 0
 */
int isPowTwo(int n)
{
    while (((n % 2) == 0) && n > 1)
        n /= 2;
    return (n == 1);
}

