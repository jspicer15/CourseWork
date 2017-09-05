#include "VMsimulator.h"

int powerChecker(int x)
{
    while (((x % 2) == 0) && x > 1)
        x /= 2;
    return (x == 1);
}

