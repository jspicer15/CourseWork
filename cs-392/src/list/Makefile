TESTNAME = testlist
LIBNAME = liblist.a

all:
	cc -c *.c -Wall -Werror --pedantic -I../../include
	ar -rc $(LIBNAME) *.o
	ranlib $(LIBNAME)
	mv $(LIBNAME) ../../lib
	cc ../../test/testlist.c -o $(TESTNAME) -Wall -Werror --pedantic -I../include -L../../lib -lmy -llist 

clean:
	rm -f *.o
	rm -f *~
	rm -f $(TESTNAME)
	rm -f *.swp

fclean: clean
	rm -f ../../lib/$(LIBNAME)

re: fclean all
