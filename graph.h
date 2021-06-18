#ifndef GRAPH_LIB
#define GRAPH_LIB
#include "jrb.h"

#define INFINITIVE_VALUE  10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
int removeEdge(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);
int setEdgeValue(Graph graph, int v1, int v2, double val);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
double shortestPath(Graph graph, int s, int t, int* path, int*length);
void dropGraph(Graph graph);
int DAG(Graph graph);
#endif /* Graph Library */