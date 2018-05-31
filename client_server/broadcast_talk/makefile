CC=gcc
OBJ=main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
broadcast_talker: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.DEFAULT_GOAL := broadcast_talker
.PHONY: clean

clean:
	-rm -rf $(OBJ) broadcast_talker
