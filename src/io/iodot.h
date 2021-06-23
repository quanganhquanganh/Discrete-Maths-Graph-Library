#ifndef IO_GRAPHVIZ_H
#define IO_GRAPHVIZ_H

#include "../graph.h"

void countComponentsOut(Graph g, const char* filename);
void countStronglyComponentsOut(Graph g, const char* filename);
void huffmanOut(Graph g, const char* filename);
void pruferOut(Graph g, const char* filename);
void coloringOut(Graph g, const char* filename);
void bfsOut(Graph g, const char* filename);
void dfsOut(Graph g, const char* filename);
void dijkstraOut(Graph g, const char* filename);
void bellmanfordOut(Graph g, const char* filename);
void dagOut(Graph g, const char* filename);
void topoOut(Graph g, const char* filename);
void primOut(Graph g, const char* filename);
void kruskalOut(Graph g, const char* filename);

#endif /* Graphviz Output Header */