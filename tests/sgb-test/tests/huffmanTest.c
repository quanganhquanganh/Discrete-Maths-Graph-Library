#include <stdio.h>
#include "huffman.h"
int main()
{
   char buffer[1000] = "abcadsaglkdlgvnxvdlkgajedlk dsgdsagd";
   char huffman[1000];
   Coding htable[256];
   int nbit, bytes;
   nbit = compress(buffer, huffman, htable);
   bytes = decompress(huffman, nbit, htable, buffer);
   buffer[bytes] = '\0';
   printf("%s\n", buffer);
}