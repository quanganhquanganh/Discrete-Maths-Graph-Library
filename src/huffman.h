#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct {
	int size;
	char bits[20]; // maximum 20 bits, it is safe enough
} Coding;

int compress(char* buffer, char* huffman, Coding htable[]);
void compressFile(char* input, char* output);
int decompress(char* huffman, int nbit, Coding htable[], char* buffer);
void decompressFile(char* input, char* output);
#endif /* Huffman header for our JRB graph's implemetation */
