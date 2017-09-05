/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 str2vect.c
 * 04/30/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#define SILENCED

#include "fs.h"

/* pre: takes in a char* 's'
 * post: returns a char** that is the vector
 *      representation of 's' broken into substrings on whitespace
 */
char** str2vect(char *s)
{
    char **vect;
    int i;
    int w; /* word count */
    int c; /* count */
    int len;
    char last;

    if (s == NULL)
        return NULL;
    w = 0;
    len = 1;
    last = '\0';
#if defined(DEBUG) && !defined(SILENCED)
    printf("[str2vect.c]\nstart loop 1\n");
    fflush(stdout);
#endif
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != ' ' && s[i] != '\t')
            if (last == ' ' || last == '\t' || last == '\0')
                w++;
        last = s[i];
        len++;
    } /* found number of words and length */
#if defined(DEBUG) && !defined(SILENCED)
    printf("length: %d\nwords: %d\n", len, w);
    fflush(stdout);
#endif
    if (w > 0)
        vect = (char**)malloc((w+1)*sizeof(char*));
    else
    {
        vect = (char**)malloc(sizeof(char*));
        *vect = NULL;
        return vect;
    }
    c = 0;
    w = 0;
    last = '\0';
#if defined(DEBUG) && !defined(SILENCED)
    printf("start loop 2\n");
    fflush(stdout);
#endif
    for (i = 0; i <= len; i++)
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
            c++;
        else if (c != 0)
        {
#if defined(DEBUG) && !defined(SILENCED)
            printf("Word size: %d\n", c);
            fflush(stdout);
#endif
            vect[w++] = (char*)malloc((c+1)*sizeof(char));
            c = 0;
        }
        last = s[i];
    } /* found size of each word */
    vect[w] = (char*)malloc(sizeof(char)); /* allocate for last NULL */
    c = 0;
    w = 0;
    last = '\0';
#if defined(DEBUG) && !defined(SILENCED)
    printf("start loop 3\n");
    fflush(stdout);
#endif
    for (i = 0; i <= len; i++)
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
        {
#if defined(DEBUG) && !defined(SILENCED)
            printf("adding a letter\n");
            fflush(stdout);
#endif
            vect[w][c++] = s[i];
        }
        else if (last != ' ' && last != '\t' && last != '\0')
        {
#if defined(DEBUG) && !defined(SILENCED)
            printf("adding a \\0\n");
            fflush(stdout);
#endif
            vect[w++][c] = '\0';
            c = 0;
        }
        last = s[i];
    } /* copied words to vect */
    vect[w] = NULL; /* added last NULL */
#if defined(DEBUG) && !defined(SILENCED)
    printf("[str2vect.c] returning\n");
    fflush(stdout);
#endif
    return vect;
}

