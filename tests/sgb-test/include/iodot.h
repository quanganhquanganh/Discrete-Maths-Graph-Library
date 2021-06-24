#ifndef IO_GRAPHVIZ_H
#define IO_GRAPHVIZ_H

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOT "dot"
#define NEATO "neato"
#define CIRCO "circo"

extern const char *color[];
extern const int MAX_COLOR;
const char* layout;

void countComponentsOut(Graph g, const char* filename);
void countStronglyComponentsOut(Graph g, const char* filename);
void huffmanOut(const char* input, const char* output);
void pruferOut(Graph g, const char* filename);
void coloringOut(Graph g, const char* filename);
void bfsOut(Graph g, int s, int t, const char* filename);
void dfsOut(Graph g, int s, int t, const char* filename);
void dijkstraOut(Graph g, int s, int t, const char* filename);
void bellmanfordOut(Graph g, int s, int t, const char* filename);
void dagOut(Graph g, const char* filename);
void topoOut(Graph g, const char* filename);
void primOut(Graph g, Graph tree, const char* filename);
void kruskalOut(Graph g, Graph tree, const char* filename);
FILE* open_file(const char* n, const char* mode);
void dot_to_pdf(const char* dot, const char* pdf);

#endif /* Graphviz Output Header */