# byte_dump
stupid version of hexdump in ~50 lines


```bash
~> echo -ne 'hello\x0World\t!!!'|./bytedump
| ASCII     | INT                 | OCT                 | HEX            |
| h e l l o | 104 101 108 108 111 | 150 145 154 154 157 | 68 65 6c 6c 6f |
| . W o r l | 000 087 111 114 108 | 000 127 157 162 154 | 00 57 6f 72 6c |
| d . ! ! ! | 100 009 033 033 033 | 144 011 041 041 041 | 64 09 21 21 21 |

```
