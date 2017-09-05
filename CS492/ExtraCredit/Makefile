NAME1 = server
NAME2 = client

SRC1 = server.c
SRC2 = client.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all:
	cc $(SRC1) -o $(NAME1) -Wall -Werror --pedantic
	cc $(SRC2) -o $(NAME2) -Wall -Werror --pedantic

clean:
	rm -f $(OBJ1)
	rm -f $(NAME1)
	rm -f $(OBJ2)
	rm -f $(NAME2)

fclean: clean

re: 	fclean all
