#include "graph.h"
#include "components.h"
#include "iodot.h"
#include "randomgraph.h"
#include <stdio.h>

int arr[100], i = 0;
void addToArr(int m) {
    arr[i++] = m;
}

int main() {
    /*
    Graph g = createGraph();
    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 2, 4, 1);
    addEdge(g, 4, 5, 1);
    addEdge(g, 1, 0, 1);
    addEdge(g, 2, 1, 1);
    addEdge(g, 3, 1, 1);
    addEdge(g, 3, 2, 1);
    addEdge(g, 4, 2, 1);
    addEdge(g, 5, 4, 1);

    
    */
    Graph g = createGraph();
    randomDirectedGraphInit(g, 10, 12);
    BFS(g, 0, -1, addToArr);
    for(int j = 0; j < i; ++j)
        printf("%4d", arr[j]);
    printf("\n");
    countStronglyComponentsOut(g, "files/randomComponents");
}