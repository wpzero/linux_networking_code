CC=gcc
OBJ:=server.o
CFLAGS:=-g

all: client server

server: $(OBJ)
	$(CC) -o $@ $^ $(CFALGS)

client: client.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	-rm -rf $(OBJ) server client client.o
