AUTHOR=jspicer
SRC=main.c page_table.c powerChecker.c processCounter.c swapping.c
OBJ=$(SRC:.c=.o)
CC=gcc
INCLPATH=-I../include
LDLIBS= -lm
LDFLAGS+=
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
PRG=VMsimulator


all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

clean:
	rm -f *.o

fclean: clean
	rm -f $(PRG)

re: fclean all
