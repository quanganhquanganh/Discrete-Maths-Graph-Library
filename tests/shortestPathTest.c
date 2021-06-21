#include "../src/graph.h"
#include <stdio.h>

void dijkstraTest() {
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 3);
    addEdge(g, 1, 3, 1);
    addEdge(g, 3, 2, 1);
    s = 0;
    t = 2;
    w = dijkstra(g, s, t, path, &length);
    if (w == oo)
    {
         printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Path from %s to %s (with total distance %f)\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
             printf(" => %s", getVertex(g, path[i]));
    }
    printf("\n");    
    dropGraph(g);
}

void bellmanfordTest() {
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 3);
    addEdge(g, 1, 3, 1);
    addEdge(g, 3, 2, 1);
    s = 0;
    t = 2;
    w = bellmanford(g, s, t, path, &length);
    if (w == oo)
    {
         printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Path from %s to %s (with total distance %f)\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
             printf(" => %s", getVertex(g, path[i]));
    }
    printf("\n");
    dropGraph(g);
}

int main() {
    dijkstraTest();
    bellmanfordTest();
}