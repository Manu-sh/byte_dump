CC=cc
CFLAGS=-O3 -Wall -ffast-math
.PHONY: all clean

all:
	$(CC) -o bytedump bytedump.c

clean:
	rm -f bytedump
