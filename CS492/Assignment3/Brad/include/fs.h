/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs.h
 * 05/02/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _FS_H_
#define _FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* for open */
#include <sys/stat.h> /* for open */
#include <fcntl.h> /* for open */
#include <time.h>

#include "linked_list.h"
#include "tree.h"

/* constant for the prompt string */
#define PROMPT ">"

/* constant for the directory path separator character */
#define PATH_SEP '/'

/* constant for the max length (in charcters) of a single command */
#define CMD_LEN 256

/* struct to define a 'block'
 *      end address should be the next start address, e.g. a single block with
 *      `s_addr = n` will have `e_addr = n + 1`
 */
struct s_block {
    int s_addr; /* start address */
    int e_addr; /* end address */
    char isFree;
};

/* avoid typing `struct` everywhere */
typedef struct s_block fs_block;

/* struct to define a 'file' */
struct s_file {
    char* name;
    int size; /* file size in bytes */
    int allocatedBlocks;
    time_t timestamp;
    char isDirectory;
    node* lfile; /* linked_list of block addresses */
};

/* avoid typing `struct` everywhere */
typedef struct s_file fs_file;

/* global environment wrapper */
struct s_env {
    char* executable; /* name of the executable file */
    int fd_flist; /* file descriptor for file_list.txt */
    int fd_dlist; /* file descriptor for dir_list.txt */
    int dsize; /* disk size */
    int bsize; /* block size */
    int numBlocks; /* total number of blocks (dsize/bsize) */
    node* ldisk; /* lined_list for disk blocks */
    leaf* tree; /* filesystem hierarchy */
    leaf* cur_dir; /* the tree node for the current directory */
} gl;

/* functions ================================================================ */
int         main(int, char**);
void        usage(char*);
void        parse_args(int, char**);
void        startParse();
char**      str2vect(char*);
void        free_vect(char**);

/* grouped in file.c */
fs_block*   createBlock(int, int, char);
fs_file*    createFile(char*, int, char);
void        splitLdiskNode(int);
void        mergeLdiskNodes();
void        allocateFile(fs_file*);
leaf*       findInHierarchy(leaf*, char*);
void        addToHierarchy(fs_file*);
int         countPathSeparations(char*);
char*       getFullPath(fs_file*);

/* functions for handling user commands */
void        changeDir(char*);
void        fs_ls();
void        fs_mkdir(char*);
void        fs_create(char*);
void        fs_append(char*, int);
void        fs_remove(char*, int);
void        fs_delete(char*);
void        fs_exit();
void        fs_dir();
void        fs_prfiles();
void        fs_prdisk();

#endif /* _FS_H_ */
