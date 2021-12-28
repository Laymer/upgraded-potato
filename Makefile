CC=gcc
CFLAGS=-o
LDFLAGS=-lm -pthread -lpthread
SERVER=prog.c
CLIENT=tcp_client.c
UTIL=util.c
CLIENTNAME=client
SERVERNAME=server

all: client server util
	$(CC) $(LDFLAGS) $(CFLAGS) $(SERVERNAME) prog.o util.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLIENTNAME) tcp_client.o util.o

client: util
	$(CC) $(LDFLAGS) -Wall -c $(CLIENT)

server: util
	$(CC) $(LDFLAGS) -Wall -c $(SERVER)

util:
	$(CC) $(LDFLAGS) -c $(UTIL)

clean:
	rm -rdf ./prog.o
	rm -rdf ./util.o
	rm -rdf ./$(SERVERNAME)
	rm -rdf ./$(CLIENTNAME)