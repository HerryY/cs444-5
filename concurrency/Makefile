CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g

all: assignment1

assignment1: assignment1.o
	$(CC) assignment1.o -o a1 -lpthread

assignment1.o:
	$(CC) -c assignment1.c $(CFLAGS)

clean:
	rm -rf *.o a1 *~ *#
