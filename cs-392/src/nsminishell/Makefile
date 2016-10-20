SRC= main.c
OBJ=$(SRC:.c=.o)
CFLAGS+= -std=c90 -Wall -Werror --pedantic

all: $(OBJ)
	cc  -L../../lib $(OBJ) -lmy -o nsminishell -lncurses

clean:
	rm -f *.o
	rm -f *~
	rm -f *.swp

fclean: clean
	rm -f nsminishell
	rm -f .nsmshistory
	rm -f .temp

re: fclean all
