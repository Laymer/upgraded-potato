CC=gcc
CFLAGS=-g
SOURCE=prog.c

all:
	$(CC) $(SOURCE)

clean:
	rm -rdf ./a.out