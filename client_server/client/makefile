CC=gcc
OBJ=main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.DEFAULT_GOAL := client
.PHONY: clean

clean:
	-rm -rf $(OBJ) client
