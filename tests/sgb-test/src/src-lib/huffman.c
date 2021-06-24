
#include "huffman.h"

void add2Queue(PriorityQueue q, int graphnode, int frequence) {
	printf("-------------------------- \n");
	printf("Adding graphnode %d and frequence %d \n", graphnode, frequence);

	Dllist node = dll_first(q);
	while (node!=q) {
		printf("Node %d %d \n", dll_val(node).iarray[0], dll_val(node).iarray[1] );
		if ( frequence <= dll_val(node).iarray[1] ) break;
		node =  dll_next(node);
	}
	if ( node==q ) {
		printf("Node nil\n");	

		dll_append(q, new_jval_iarray(graphnode, frequence));
	} else {
		printf("Before %d %d\n", dll_val(node).iarray[0], dll_val(node).iarray[1] );
		dll_insert_b(node, new_jval_iarray(graphnode, frequence));	
	}
	printf("============================ \n");
}

HuffmanTree makeHuffman(int fTable[]) {
	int lastNodeID = 0;
	HuffmanTree	hTree;
	int i;
	Dllist n1, n2;
	char buff[2]; buff[1] = 0;
	PriorityQueue queue = new_dllist();
	hTree.graph = createGraph();

	for (i=0; i<256; i++)
		if (fTable[i]) {
			// make new graphNode to add to the priority queue
			lastNodeID++;
			buff[0] = i;
			addVertex(hTree.graph, lastNodeID, buff);
			add2Queue(queue, lastNodeID, fTable[i]);
			printf("last %d %c %d\n", lastNodeID, i, fTable[i]);
		}
	
	printf("list-out queue \n");
	for (n1 = dll_first(queue); n1!=queue; n1=dll_next(n1))
	{
		printf("%d %d\n", dll_val(n1).iarray[0], dll_val(n1).iarray[1]);
	}

	// regroup nodes in priority queue
	for (;;)
	{
		n1 = dll_first(queue);
		if ( n1==queue ) break;
		n2 = dll_next(n1);
		if ( n2==queue ) break;
		// add new node in the graph
		lastNodeID++;
		buff[0] = -1;
		addVertex(hTree.graph, lastNodeID, buff);
		printf("id1 %d \n", dll_val(n1).iarray[0]);
		addEdge(hTree.graph, lastNodeID, dll_val(n1).iarray[0], 0); 
		printf("id2 %d \n", dll_val(n2).iarray[0]);
		addEdge(hTree.graph, lastNodeID, dll_val(n2).iarray[0], 1); 
		printf("last %d \n", lastNodeID);
		// modify the queue
		dll_delete_node(n1);
		dll_delete_node(n2);
		add2Queue(queue, lastNodeID, dll_val(n1).iarray[1]+dll_val(n2).iarray[1] );
	}
	n1 = dll_first(queue);
	if ( n1==queue ) 
		hTree.rootID = 0;
	else
		hTree.rootID = dll_val(n1).iarray[0];	
	
	free_dllist(queue);


	return hTree;
}

void getCode(int node, Graph g, int len, char code[], Coding htable[]) 
{
	int ch, k, i;
	int output[10];
	ch = getVertex(g, node)[0];
	if (ch != -1) {
		htable[ch].size = len;
		memcpy(htable[ch].bits, code, len);	
	} else {
		k = outdegree(g, node, output);
		for (i=0; i<k; i++) {
			code[len] = (char)getEdgeValue(g, node, output[i]);
			getCode(output[i], g, len+1, code, htable);
		}
	}
}

void createHuffmanTable(HuffmanTree htree, Coding htable[]) {
	int i;
	char code[20];
	for (i=0; i<256; i++) {
		htable[i].size=0;
	}
	if (htree.rootID == 0) return;
	printf("rootID %d \n ", htree.rootID);
	getCode(htree.rootID, htree.graph, 0, code, htable); 
}

void setBit(char* huffman, int nbit, int val) {
	int i, byte, bit;
	byte = nbit/8;
	bit = nbit%8;
	if (val==0) {
		huffman[byte] &= ~(1 << bit);
	} else {
		huffman[byte] |= (1 << bit);
	}
}

int getBit(char* huffman, int nbit) {
	//printf("nbit %d \n", nbit);
	int i, byte, bit;
	byte = nbit/8;
	bit = nbit%8;
	i =	huffman[byte] & (1 << bit);
	//printf("i %d, and %d \n", i, i!=0);

	return i!=0;
}

void addHuffmanChar(char ch, Coding htable[], char* huffman, int* nbit) {
	int i;
	for (i=0; i<htable[ch].size; i++) {
		setBit(huffman, *nbit, htable[ch].bits[i]);
		(*nbit)++;
	}
}

// return number of bits
int compress(char* buffer, char*huffman, Coding htable[]) {
	HuffmanTree htree;
	int i, k, n, nbit;
	
	int fTable[256] = {0} ;
	unsigned int ch;
	
	for (i=0; i<strlen(buffer); i++) {
		ch = buffer[i];
		fTable[ch]++;
	}
	printf("frequency table \n");
	for (i = 0; i < 256; i++){
		printf("char %c with frequency %d \n ", i, fTable[i]);
	}

	htree = makeHuffman (fTable);
	createHuffmanTable(htree, htable);
	printf("Huffman Table Code:\n");
	for (i=0; i<256; i++) {
		printf("index %d with size %d\n", i, htable[i].size);
		if (htable[i].size > 0) {
			printf ("Char %c \n ", i);
			for (k=0; k<htable[i].size; k++)
			   printf ("%d", htable[i].bits[k]);
			printf ("\n");   
		}
	}
	
	printf("Original size: %d bytes\n", strlen(buffer));
	printf("%s\n", buffer);
	// Compress
	n = strlen(buffer);
	nbit = 0;
	for (i=0; i<n; i++)
		addHuffmanChar(buffer[i], htable, huffman, &nbit);
	printf("Compressed size: %d bytes\n", (nbit/8)+1);
	for (i=0; i<nbit; i++)
		printf("%d", getBit(huffman, i));
	printf("\n");
	return nbit;
}

void writeHuffmanTable(Coding htable[], FILE* f) {
	int i, num=0, n, k;
	char buffer[10];
	num=0;
	for (i=0; i<256; i++) {
		if (htable[i].size > 0) {
			num++;  
		}
	}
	printf("Num of chars: %d\n", num);
	fwrite(&num, sizeof(int), 1, f);
	for (i=0; i<256; i++) {
		if (htable[i].size > 0) {
			fputc(i, f);
			fwrite(&htable[i].size, sizeof(int), 1, f);
			printf("%c: %d bits\n", i, htable[i].size);
			for (k=0; k<htable[i].size; k++)
				setBit(buffer, k, htable[i].bits[k]);
			n = htable[i].size/8;
			if (htable[i].size%8) n++;
			fwrite(buffer, n, 1, f);			  
		}
	}
}

void compressFile(char* input, char*output) {
	HuffmanTree htree;
	Coding htable[256] = {0};
	int i, k, n, nbit, size;
	
	FILE* f1, *f2;

	int fTable[256] = {0} ;
	
	char* huffman;
	
	f1 = fopen(input, "rb");
	if (f1==NULL) {
		perror("Can not open input file\n");
		exit(2);
	}
	
	size = 0;
	while ( (i=fgetc(f1)) != -1 ) {
		fTable[i]++;
		size++;
	}
	
	printf("Input: %d bytes\n", size);
	
	if (size==0) return;
	
	htree = makeHuffman (fTable);
	createHuffmanTable(htree, htable);
	
	f2 = fopen(output, "w+b");
	if (f2==NULL) {
		perror("Can not open output file\n");
		exit(2);
	}
	fwrite("HM", 2, 1, f2);
	writeHuffmanTable(htable, f2);
	
	fseek(f1, 0, SEEK_SET);
	nbit = 0;
	huffman = malloc(size);
	while ( (i=fgetc(f1)) != -1 ) {
		addHuffmanChar(i, htable, huffman, &nbit);
	}
	fwrite(&nbit, sizeof(int), 1, f2);
	n = nbit/8;
	if (nbit%8) n++;
	fwrite(huffman, n, 1, f2);
	free(huffman);
	printf("Compressed: %d bytes\n", n);
	
	fclose(f1);
	fclose(f2);
}



void setRoot(int* cursor) {
	*cursor = 0;
}

void goLeft(int* cursor) {
	*cursor = 2*(*cursor) + 1;
}

void goRight(int* cursor) {
	*cursor = 2*(*cursor) + 2;
}

HuffmanTreeArray makeHuffmanTreeArray(Coding htable[]) 
{
	int i, k, maxlen, size, exp2, cursor;
	HuffmanTreeArray hArray;
	
	maxlen = 0;
	for (i=0; i<256; i++)
		if (htable[i].size > maxlen) maxlen = htable[i].size;
	size = 1;
	exp2 = 1;
	for (i=1; i<=maxlen; i++) {
		exp2 *= 2;	
		size += exp2;
	}
	hArray.size = size;
	hArray.nodes = malloc(hArray.size*sizeof(int));
	for (i=0; i<hArray.size; i++) hArray.nodes[i] = -1;
	for (i=0; i<256; i++) {
		setRoot(&cursor);
		if (htable[i].size) {
			for (k=0; k<htable[i].size; k++) {
				if (htable[i].bits[k]==0) goLeft(&cursor);
				else goRight(&cursor);
			}
			if (cursor<hArray.size) hArray.nodes[cursor] = i;
		}
	}
	
	//printf("size = %d\n", hArray.size);
	/*for (i=0; i<hArray.size; i++) {
		if (hArray.nodes[i]==-1) printf("-");
		else printf("%c", hArray.nodes[i]);
	}
	printf("\n");
	*/

	return hArray;
}

void destroyHuffmanTreeArray(HuffmanTreeArray htree)
{
	free(htree.nodes);
}

int decompress(char * huffman, int nbit, Coding htable[], char * buffer) 
{
	HuffmanTreeArray hArray;
	int i, n, cursor;
	hArray = makeHuffmanTreeArray(htable);
	n = 0;
	setRoot(&cursor);
	for (i=0; i<nbit; i++) {
		if (getBit(huffman, i)==0) goLeft(&cursor);
		else goRight(&cursor);
		if (cursor >= hArray.size) {
			perror("Decompress error\n");
			exit(1);
		}
		if (hArray.nodes[cursor] != -1) {
			buffer[n++] = (char) hArray.nodes[cursor];
			setRoot(&cursor);
		}
	}
	destroyHuffmanTreeArray(hArray);
	return n;
}

void decompressFile(char *input, char *output) {
	HuffmanTree htree;
	HuffmanTreeArray hArray;
	Coding htable[256] = {0};
	int i, k, n=0, nbit, size, ch, cursor;
	char bits[10];
	char code[2];
	
	FILE* f1, *f2;

	char* huffman;
	
	f1 = fopen(input, "rb");
	if (f1==NULL) {
		perror("Can not open input file\n");
		exit(2);
	}
	
	fread(code, 2, 1, f1);
	if (code[0]!='H'&&code[1]!='M') {
		perror("Bad format\n");
		exit(2);
	}
	
	/* read huffman code into table */
	fread(&n, sizeof(int), 1, f1);
	printf("Read huffman table: %d chars\n", n);
	for (i=0; i<256; i++)
		htable[i].size = 0;

	for (i=0; i<n; i++)
	{
		ch = fgetc(f1);
		fread(&nbit, sizeof(int), 1, f1);
		printf("%c: %d bits\n", ch, nbit);
		htable[ch].size = nbit;
		k = nbit/8;
		if (nbit%8) k++;
		fread(bits, k, 1, f1);
		for (k=0; k<nbit; k++)
			htable[ch].bits[k] = getBit(bits, k);
	}
	hArray = makeHuffmanTreeArray(htable);
	
	f2 = fopen(output, "w+b");
	if (f2==NULL) {
		perror("Can not open output file\n");
		exit(2);
	}
	
	/* read huffman data */
	fread(&nbit, sizeof(int), 1, f1);
	size = nbit/8;
	if (nbit%8) size++;
	huffman = (char*) malloc(size);
	printf("Read huffman data: %d chars\n", size);
	fread(huffman, size, 1, f1);
	setRoot(&cursor);
	for (i=0; i<nbit; i++) {
		if (getBit(huffman, i)==0) goLeft(&cursor);
		else goRight(&cursor);

		if (cursor >= hArray.size) {
			perror("Decompress error\n");
			exit(1);
		}

		if (hArray.nodes[cursor] != -1) {
			printf("char %c \n", hArray.nodes[cursor]);
			fputc(hArray.nodes[cursor], f2);
			setRoot(&cursor);
		}
	}
	free(huffman);
	destroyHuffmanTreeArray(hArray);
	
	fclose(f1);
	fclose(f2);
	
}
