#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define BSIZE 8192
#define STREAM_READ stdin
#define STREAM_WRITE stdout

typedef enum _display_as { ASCII, INT, OCT, HEX } DisplayAs;

/*
   all these calls to printf cause a little bit of overhead 
   but i don't wanna spend energy to reduce it

   echo -ne 'hello\x0World\t!!!'|./bytedump

   | ASCII     | INT                 | OCT                 | HEX            |
   | h e l l o | 104 101 108 108 111 | 150 145 154 154 157 | 68 65 6c 6c 6f |
   | . W o r l | 000 087 111 114 108 | 000 127 157 162 154 | 00 57 6f 72 6c |
   | d . ! ! ! | 100 009 033 033 033 | 144 011 041 041 041 | 64 09 21 21 21 |
*/

// return the byte readed (as size, not index), 0 if an error is occurred
static inline int displayLine(char *buf, int size, DisplayAs as, FILE *stream) {

	unsigned char c = 0;
	int i = 0;

	switch (as) {
		case ASCII:
			while (i < size) fprintf(stream, "%c ", (isgraph((c = buf[i++])) ? c : '.'));
			break;
		case INT:
			while (i < size) fprintf(stream, "%03d ", (c = buf[i++]));
			break;
		case OCT:
			while (i < size) fprintf(stream, "%03o ", (c = buf[i++]));
			break;
		case HEX:
			while (i < size) fprintf(stream, "%02x ", (c = buf[i++]));
			break;
	}

	return i;
}

int main() {

	char buf[BSIZE];
	int rb;

	fprintf(STREAM_WRITE, "| ASCII     | INT %17c OCT %17c HEX %12c\n", '|', '|', '|');
	while ((rb = fread(buf, 1, BSIZE, STREAM_READ)) != 0) {
		for (int i = 0, n; i < rb; i+=5) {
			n = (5 > rb-i ? rb-i : 5); fprintf(STREAM_WRITE, "| ");
			displayLine(buf+i, n, ASCII, STREAM_WRITE), fprintf(STREAM_WRITE, "| ");
			displayLine(buf+i, n, INT,   STREAM_WRITE), fprintf(STREAM_WRITE, "| ");
			displayLine(buf+i, n, OCT,   STREAM_WRITE), fprintf(STREAM_WRITE, "| ");
			displayLine(buf+i, n, HEX,   STREAM_WRITE), fprintf(STREAM_WRITE, "|\n");
		}
	}

	return EXIT_SUCCESS;
}
