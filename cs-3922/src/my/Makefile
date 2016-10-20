TESTNAME = testmy
LIBNAME = libmy.a

all:
	cc -c *.c -Wall -Werror --pedantic -I../../include
	ar -rc $(LIBNAME) *.o
	ranlib $(LIBNAME)
	mv $(LIBNAME) ../../lib
	cc ../../test/testmy.c -o testmy -Wall -Werror --pedantic -I../include -L../../lib -lmy

clean:
	rm -f *.o
	rm -f *~
	rm -f $(TESTNAME)
	rm -f *.swp

fclean: clean
	rm -f ../../lib/$(LIBNAME)

re: fclean all
