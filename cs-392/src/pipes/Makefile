SRC= main.c
OBJ=$(SRC:.c=.o)
CFLAGS+= -std=c90 -Wall -Werror --pedantic

all: $(OBJ)
	cc  -L../../lib $(OBJ) -lmy -o pipes

clean:
	rm -f *.o
	rm -f *~
	rm -f *.swp

fclean: clean
	rm -f pipes

re: fclean all
