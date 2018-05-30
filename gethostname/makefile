CC=gcc
OBJ=main.o
CFLAGS=-g

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
gethostname: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.DEFAULT_GOAL := gethostname
.PHONY: clean

clean:
	-rm -rf $(OBJ) gethostname
