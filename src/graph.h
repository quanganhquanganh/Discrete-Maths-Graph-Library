#ifndef GRAPH_LIB
#define GRAPH_LIB
#include "../libfdr/jrb.h"

#define oo 10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

typedef struct dllist* Dllist;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
char *removeVertex(Graph graph, int id);
Dllist getAllEdges(Graph graph);
void addEdge(Graph graph, int v1, int v2, double weight);
int removeEdge(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);
int setEdgeValue(Graph graph, int v1, int v2, double val);
int getAdjacentVertices(Graph graph, int v, int* output);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
void topologicalSort(Graph graph, int* out, int* n);
double dijkstra(Graph graph, int s, int t, int* path, int* length);
double bellmanford(Graph graph, int s, int t, int* path, int* length);
void dropGraph(Graph graph);
int UAG(Graph graph);
int DAG(Graph graph);
#endif /* Graph Library */