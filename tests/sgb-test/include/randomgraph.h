#ifndef RANDOM_GRAPH_LIB
#define RANDOM_GRAPH_LIB
#include "graph.h"
#include <stdlib.h>
#include <time.h>

#define MAX_V_NUM 10000
#define MAX_E_NUM 10000
#define MAX_DIST 20

void randomDirectedGraphInit(Graph g, int v_num, int e_num);
void randomUndirectedGraphInit(Graph g, int v_num, int e_num);
#endif