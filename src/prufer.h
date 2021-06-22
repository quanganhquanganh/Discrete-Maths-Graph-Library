#ifndef PRUFER_H
#define PRUFER_H

#include <stdio.h>

#include "graph.h"

int pruferInputGraph(FILE* f, Graph g);
void prufer(Graph g, /*int start, int verNum,*/ int code[], int* length);

#endif /* Prufer header for our JRB graph's implementation */