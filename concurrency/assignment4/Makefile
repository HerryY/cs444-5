CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: assignment3

assignment4: assignment4.o
	$(CC) assignment4.o -o a4 -pthread

assignment3.o:
	$(CC) -c assignment4.c $(CFLAGS)

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o a4 *~ *.aux *.log *.out
