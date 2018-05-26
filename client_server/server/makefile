CC=gcc
OBJ=main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.DEFAULT_GOAL := server
.PHONY: clean

clean:
	-rm -rf $(OBJ) server
