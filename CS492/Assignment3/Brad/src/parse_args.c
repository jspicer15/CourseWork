/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 parse_args.c
 * 04/27/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in int 'argc' and char** 'argv' command line arguments which
 *      include:
 *      -f <file_list>
 *      -d <dir_list>
 *      -s <disk size>
 *      -b <block size>
 * post: parses args using `getopt` and sets up the global environment
 */
void parse_args(int argc, char** argv)
{
    int opt;

    /* print usage if we don't have the correct number of arguments */
    if (argc != 9)
    {
        usage(argv[0]);
        exit(-1);
    }

    /* parse options looking for 'f', 'd', 's' and 'b', each requiring an
     *      argument which will be set in 'optarg'
     */
    while ((opt = getopt(argc, argv, "f:d:s:b:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                if ((gl.fd_flist = open(optarg, O_RDONLY)) < 0)
                {
                    perror(argv[0]);

                    exit(-1);
                }
                break;
            case 'd':
                if ((gl.fd_dlist = open(optarg, O_RDONLY)) < 0)
                {
                    perror(argv[0]);

                    exit(-1);
                }
                break;
            case 's':
                gl.dsize = atoi(optarg);
                break;
            case 'b':
                gl.bsize = atoi(optarg);
                break;
            default: /* invalid option */
                usage(argv[0]);
                exit(-1);
        }
    }

    /* save the name of the executable in the global environment */
    gl.executable = argv[0];
}

