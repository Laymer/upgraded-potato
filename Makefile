CC=gcc
CFLAGS=-o
LDFLAGS=-lm -pthread -lpthread
SERVER=prog.c
CLIENT=tcp_client.c
UTIL=util.c
WORKOUT=workout.c
CLIENTNAME=client
SERVERNAME=server

all: client server util workout
	$(CC) $(LDFLAGS) $(CFLAGS) $(SERVERNAME) prog.o util.o workout.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(CLIENTNAME) tcp_client.o util.o

client: util
	$(CC) $(LDFLAGS) -Wall -c $(CLIENT)

server: util workout
	$(CC) $(LDFLAGS) -Wall -c $(SERVER)

util:
	$(CC) $(LDFLAGS) -c $(UTIL)

workout:
	$(CC) $(LDFLAGS) -c $(WORKOUT)

# DOES NOT WORK USING MAKE BUT I DON'T UNDERSTAND WHY PLEASE HELP :
# gui:
# 	gcc $( pkg-config --cflags gtk4 ) -o gui gui.c $( pkg-config --libs gtk4 )

clean:
	rm -rdf ./gui
	rm -rdf ./prog.o
	rm -rdf ./util.o
	rm -rdf ./$(SERVERNAME)
	rm -rdf ./$(CLIENTNAME)