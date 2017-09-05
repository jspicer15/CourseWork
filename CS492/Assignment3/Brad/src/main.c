/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 main.c
 * 05/01/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in int 'argc' and char** 'argv' command line arguments which
 *      include:
 *      -f <file_list>
 *      -d <dir_list>
 *      -s <disk size>
 *      -b <block size>
 * post: runs the filesystem simulation program
 * return: 0 on sucessful exit, something else on error
 */
int main(int argc, char** argv)
{
    int n;
    char* line;
    char** v;

    /* parse args and setup global environment */
    parse_args(argc, argv);

    /* read input files and initialize filesystem */
    init();

    /* main command reading loop */
    line = (char*)malloc(CMD_LEN * sizeof(char));
    bzero((void*)line, CMD_LEN * sizeof(char));
    while (1)
    {
        /* prompt */
        printf("%s ", PROMPT);
        fflush(stdout);

        /* fd 0 is stdin */
        if ((n = read(0, line, CMD_LEN)) == -1)
        {
            perror(argv[0]);

            fs_exit();
            exit(-1);
        }
        else if (n == 0)
        {
            fs_exit();
            break;
        }
        else
        {
            /* overwrite newline with NULL-byte */
            line[n - 1] = '\0';

#ifdef DEBUG
            printf("[DEBUG]\tRead line: <%s>\n", line);
            fflush(stdout);
#endif

            /* use str2vect to break 'line' into a list of whitespace separated
             * strings
             */
            v = str2vect(line);

            /* check for commands and execute the proper function */
            if (!strcmp(v[0], "append"))
            {
                if (v[1] != NULL && v[2] != NULL)
                    fs_append(v[1], atoi(v[2]));
                else
                {
                    printf("usage: append name size\n");
                    fflush(stdout);
                }
            }
            else if (!strcmp(v[0], "cd"))
            {
                if (v[1] != NULL)
                    fs_cd(v[1]);
                else
                {
                    printf("usage: cd directory\n");
                    fflush(stdout);
                }
            }
            else if (!strcmp(v[0], "cd..")) /* just in case this is the intended command */
            {
                fs_cd("..");
            }
            else if (!strcmp(v[0], "create"))
            {
                if (v[1] != NULL)
                    fs_create(v[1]);
                else
                {
                    printf("usage: create name\n");
                    fflush(stdout);
                }
            }
            else if (!strcmp(v[0], "delete"))
            {
                if (v[1] != NULL)
                    fs_delete(v[1]);
                else
                {
                    printf("usage: delete name\n");
                    fflush(stdout);
                }
            }
            else if (!strcmp(v[0], "dir"))
            {
                fs_dir();
            }
            else if (!strcmp(v[0], "exit"))
            {
                /* free the vector immediately and break to exit */
                free_vect(v);
                break;
            }
            else if (!strcmp(v[0], "ls"))
            {
                fs_ls();
            }
            else if (!strcmp(v[0], "mkdir"))
            {
                if (v[1] != NULL)
                    fs_mkdir(v[1]);
                else
                {
                    printf("usage: mkdir directory\n");
                    fflush(stdout);
                }
            }
            else if (!strcmp(v[0], "prdisk"))
            {
                fs_prdisk();
            }
            else if (!strcmp(v[0], "prfiles"))
            {
                fs_prfiles();
            }
            else if (!strcmp(v[0], "remove"))
            {
                if (v[1] != NULL && v[2] != NULL)
                    fs_remove(v[1], atoi(v[2]));
                else
                {
                    printf("usage: remove name size\n");
                    fflush(stdout);
                }
            }
            else
            {
                printf("%s: command not found: %s\n", argv[0], v[0]);
                fflush(stdout);
            }

            /* free the vector to avoid memory leaks */
            free_vect(v);
        }
    }
    free(line);

    fs_exit();
    return 0;
}

