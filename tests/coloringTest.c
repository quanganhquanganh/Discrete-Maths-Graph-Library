#include "../src/coloring.h"
#include <stdio.h>

int main() {
    Graph g = createGraph();
    addVertex(g, 0, "1"); addVertex(g, 1, "2");
    addVertex(g, 2, "3"); addVertex(g, 3, "4");
    addVertex(g, 4, "5");
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 0, 1);
    addEdge(g, 0, 4, 1);
    addEdge(g, 1, 0, 1);
    addEdge(g, 2, 1, 1);
    addEdge(g, 3, 2, 1);
    addEdge(g, 0, 3, 1);
    addEdge(g, 4, 0, 1);
    int coloring[100], V;
    V = graphColoring(g, coloring);
    for (int u = 0; u < V; u++)
        printf("Vertex %s --->  Color %d\n", getVertex(g, u), coloring[u]);
}