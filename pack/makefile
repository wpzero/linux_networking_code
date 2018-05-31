CC=gcc
OBJ=pack.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
pack: $(OBJ)
	$(CC) -o $@ $^ $(CFALGS)

.PHONY: clean
.DEFAULT_GOAL := pack

clean:
	-rm -rf $(OBJ) pack
