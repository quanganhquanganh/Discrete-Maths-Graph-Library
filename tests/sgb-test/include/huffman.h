#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "graph.h"
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	int size;
	char bits[20]; // maximum 20 bits, it is safe enough
} Coding;

typedef struct
{
	Graph graph;
	int rootID;
} HuffmanTree;

typedef Dllist PriorityQueue;

typedef struct
{
	int size;
	int *nodes;
} HuffmanTreeArray;

void add2Queue(PriorityQueue q, int graphnode, int frequence);
HuffmanTree makeHuffman(int fTable[]);
void createHuffmanTable(HuffmanTree htree, Coding htable[]);
void setBit(char *huffman, int nbit, int val);
int getBit(char *huffman, int nbit);
void addHuffmanChar(char ch, Coding htable[], char *huffman, int *nbit);
void writeHuffmanTable(Coding htable[], FILE *f);
void setRoot(int *cursor);
void goLeft(int *cursor);
void goRight(int *cursor);
HuffmanTreeArray makeHuffmanTreeArray(Coding htable[]);
void destroyHuffmanTreeArray(HuffmanTreeArray htree);

int compress(char *buffer, char *huffman, Coding htable[]);
void compressFile(char *input, char *output);
int decompress(char *huffman, int nbit, Coding htable[], char *buffer);
void decompressFile(char *input, char *output);
#endif /* Huffman header for our JRB graph's implemetation */
