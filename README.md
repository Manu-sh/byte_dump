# byte_dump
stupid version of hexdump in ~50 lines


```bash
~> echo -ne 'hello\x0World\t!!!'|./bytedump
| ASCII     | INT                 | OCT                 | HEX            |
| h e l l o | 104 101 108 108 111 | 150 145 154 154 157 | 68 65 6c 6c 6f |
| . W o r l | 000 087 111 114 108 | 000 127 157 162 154 | 00 57 6f 72 6c |
| d . ! ! ! | 100 009 033 033 033 | 144 011 041 041 041 | 64 09 21 21 21 |

```

 added patch to make it more similar to `hexdump -C`:
 
 ```bash
 # to apply
 patch -Nfsp1 bytedump.c < hdump.patch
 
 # to revert
 patch -Rfsp1 bytedump.c < hdump.patch
```

after hdump patch:
```bash
~>  echo -ne 'hello\x0World\t!!!'|./bytedump
00000000  68 65 6c 6c 6f 00 57     6f 72 6c 64 09 21 21 21 |hello.World.!!! |
```


###### Copyright © 2017-2018, [Manu-sh](https://github.com/Manu-sh), s3gmentationfault@gmail.com. Released under the [GPL3 license](LICENSE).
