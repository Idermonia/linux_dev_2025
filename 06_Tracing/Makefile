CC = gcc
CFLAGS = -Wall
LDFLAGS = -ldl

all: move protect.so

move: move.c
	$(CC) $(CFLAGS) -o move move.c

protect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -o protect.so protect.c $(LDFLAGS)

test: move protect.so
	chmod +x test.sh
	./test.sh

clean:
	rm -f move protect.so
	rm -f *.txt

.PHONY: all test clean
