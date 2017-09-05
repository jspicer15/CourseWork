# Bradford Smith (bsmith8)
# Makefile for CS 492 Assignment 2
# 04/04/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=VMsimulator
AUTHOR=bsmith8
PROJECT=cs492-assignment2
SRC=main.c page_table.c isPowTwo.c countProcs.c swapping.c
OBJ=$(SRC:.c=.o)
CC=gcc
LATEX=report.tex
PDF=$(LATEX:.tex=.pdf)
TEX=pdflatex -shell-escape -interaction=nonstopmode -file-line-error
RM=rm -f
INCLPATH=-I../include
LIBPATH=
LDLIBS= -lm
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o
	$(RM) vgcore*

fclean: clean
	$(RM) $(PRG)

re: fclean all

# just a quick test using example parameters
test: debug
	./$(PRG) ../plist ../ptrace 2 FIFO +

plots: re
	./plot.sh

# latex needs to be made in the above directory to properly find files
tex: plots
	cd .. && $(TEX) $(LATEX)

texclean:
	$(RM) ../*.aux
	$(RM) ../*.log
	$(RM) ../*.dat
	$(RM) ../*.png

texfclean: texclean
	$(RM) ../$(PDF)

# call another instance of make to force fclean to run eventhough plots runs it
# and another to cleanup the tex after the archive is made
tar: | tex texclean
	make fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../*
	make texfclean

