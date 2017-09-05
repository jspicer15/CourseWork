# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 3
# 05/02/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=fs
AUTHOR=bsmith8
PROJECT=cs492-assignment3
FILES=../file_list.txt
DIRS=../dir_list.txt
# assign '..' to ROOT if ROOT is not already set
ROOT?=..

SRC=main.c usage.c parse_args.c str2vect.c free_vect.c linked_list.c tree.c \
	init.c file.c fs_cd.c fs_ls.c fs_mkdir.c fs_create.c fs_append.c \
	fs_remove.c fs_delete.c fs_exit.c fs_dir.c fs_prfiles.c fs_prdisk.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH= -I../include
LIBPATH=
LDLIBS=
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(OBJ) $(DIRS) $(FILES)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

# generate input files for the program
$(FILES):
	find $(ROOT) -type f -ls > $(FILES)

$(DIRS):
	find $(ROOT) -type d > $(DIRS)

inputs:
	find $(ROOT) -type d > $(DIRS)
	find $(ROOT) -type f -ls > $(FILES)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

test: debug
	./$(PRG) -f $(FILES) -d $(DIRS) -b 16 -s 262144

valgrind: debug
	valgrind --track-origins=yes ./$(PRG) -f $(FILES) -d $(DIRS) -b 16 -s 262144

clean:
	$(RM) *.o
	$(RM) *core*

fclean: clean
	$(RM) $(DIRS)
	$(RM) $(FILES)
	$(RM) $(PRG)

re: fclean all

tar: fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../*

