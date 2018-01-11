#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

/* 

   a good choice for the size of buffer:
   avoid printing extra padding you should align the buffer size according to chunk size for example for chunk of 5 bytes at times
   8192 isn't a good value but you could use 8000 for example, here there is a little example of what was intended for extra-padding

   | . . . . H | 176 000 000 000 072 | 260 000 000 000 110 | b0 00 00 00 48 |
   | . 5       | 139 053             | 213 065             | 8b 35          | // should be appear only on the last line
   | . / . . H | 188 047 032 000 072 | 274 057 040 000 110 | bc 2f 20 00 48 |

*/

#define BSIZE 8000
#define STREAM_READ stdin
#define STREAM_WRITE stdout

typedef enum { ASCII, INT, OCT, HEX } DisplayAs;

/*
   all these calls to printf cause a little bit of overhead 
   but i don't wanna spend energy to reduce it

   echo -ne 'hello\x0World\t!!!'|./bytedump

   | ASCII     | INT                 | OCT                 | HEX            |
   | h e l l o | 104 101 108 108 111 | 150 145 154 154 157 | 68 65 6c 6c 6f |
   | . W o r l | 000 087 111 114 108 | 000 127 157 162 154 | 00 57 6f 72 6c |
   | d . ! ! ! | 100 009 033 033 033 | 144 011 041 041 041 | 64 09 21 21 21 |

*/

/* return the byte readed (as size, not index), 0 if an error is occurred */
static inline int displayChunk(const char *buf, int size, DisplayAs as, FILE *stream) {

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

			displayChunk(buf+i, n, ASCII, STREAM_WRITE);
			for (int j = n; j < 5; j++) fprintf(STREAM_WRITE, "%-2c", ' '); /* padding */
			fprintf(STREAM_WRITE, "| ");

			displayChunk(buf+i, n, INT,   STREAM_WRITE);
			for (int j = n; j < 5; j++) fprintf(STREAM_WRITE, "%-4c", ' ');
			fprintf(STREAM_WRITE, "| ");
			
			displayChunk(buf+i, n, OCT,   STREAM_WRITE);
			for (int j = n; j < 5; j++) fprintf(STREAM_WRITE, "%-4c", ' ');
			fprintf(STREAM_WRITE, "| ");

			displayChunk(buf+i, n, HEX,   STREAM_WRITE);
			for (int j = n; j < 5; j++) fprintf(STREAM_WRITE, "%-3c", ' ');
			fprintf(STREAM_WRITE, "|\n");
		}
	}

	return EXIT_SUCCESS;
}
