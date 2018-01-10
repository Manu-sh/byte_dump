CC=cc
CFLAGS=-O3 -Wall -ffast-math -std=c99
.PHONY: all clean

all:
	$(CC) $(CFLAGS) -o bytedump bytedump.c

clean:
	rm -f bytedump
