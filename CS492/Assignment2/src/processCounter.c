#include "VMsimulator.h"

/* pre: takes in a FILE* 'file' which must be a valid file, pointing to the plist
 *      input parameter from main
 * post: counts the lines in 'file' which is the number of unique processes in
 *      plist
 * return: an integer of the count of the lines in 'file'
 */
int processCounter(FILE* file)
{
    int ret;
    int i;
    char c;

    ret = 0;
    i = 0;
    while (!feof(file))
    {
        c = fgetc(file);
        i++;
        if (c == '\n')
        {
            if (i > 1)
            {
                i = 0;
                ret++;
            }
        }
    }

    return ret;
}

