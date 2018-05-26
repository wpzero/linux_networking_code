CC=gcc
OBJ=main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
showip: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.DEFAULT_GOAL := showip
.PHONY: clean

clean:
	-rm -rf $(OBJ) showip
