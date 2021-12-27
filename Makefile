CC=gcc
CFLAGS=-o
SERVER=prog.c
CLIENT=tcp_client.c
UTIL=util.c
CLIENTNAME=client
SERVERNAME=server

all: client server util
	$(CC) $(CFLAGS) $(SERVERNAME) prog.o util.o
	$(CC) $(CFLAGS) $(CLIENTNAME) tcp_client.o util.o

client: util
	$(CC) -Wall -c $(CLIENT)

server: util
	$(CC) -Wall -c $(SERVER)

util:
	$(CC) -Wall -c $(UTIL)

clean:
	rm -rdf ./prog.o
	rm -rdf ./util.o
	rm -rdf ./$(SERVERNAME)
	rm -rdf ./$(CLIENTNAME)