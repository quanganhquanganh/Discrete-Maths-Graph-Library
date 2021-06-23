#include "iodot.h"
#include "../src/huffman.c"

void huffmanOut(const char* buffer, const char* output) {
    HuffmanTree htree;
    JRB node, ptr;
	int i, k, n, nbit, size, output1[5], output2[5];
	char name[100], dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

	FILE* f;
	
	int fTable[256] = {0} ;
	unsigned int ch;
	
	for (i=0; i<strlen(buffer); i++) {
		ch = buffer[i];
		fTable[ch]++;
	}
	
	htree = makeHuffman (fTable);

    f = open_file(dotFile, "w+");
    fprintf(f, "digraph{\n");
    jrb_traverse(node, htree.graph.edges) {
        int m = outdegree(htree.graph, node->key.i, output1);

        for(int i = 0; i < m; ++i) {
            int n = outdegree(htree.graph, output1[i], output2);


            if(n == 0) {
                char* buff = getVertex(htree.graph, output1[i]);
                char c = buff[0];
                if (c != '\0' && c != ' ' && c != '"' && c != '\n') // regular characters
					sprintf(name, "%d\\n%s", output1[i], buff);
				else if (c == ' ')
					sprintf(name, "%d\\n blank", output1[i]);
				else if (c == '"')  //escape
                    sprintf(name, "%d\\n \\\"", output1[i]);
				else if (c == '\n')
                    sprintf(name, "%d\\n /n", output1[i]);
                    
            } else sprintf(name, "%d", output1[i]);

            if(getEdgeValue(htree.graph, node->key.i, output1[i]) == 1)
                fprintf(f, "\t%d -> \"%s\" [color=blue, label=1];\n", 
                        node->key.i, name);
            else fprintf(f, "\t%d -> \"%s\" [color=red, label=0];\n", 
                        node->key.i, name);
        }
    }
    fprintf(f, "}");
    fclose(f);
    dot_to_pdf(dotFile, pdfFile);
}