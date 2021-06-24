#include "../io/iodot.h"
#include "randomGraph.c"

int main() {
    Graph g = createGraph();/*
    addVertex(g,0,"0");
    addVertex(g,1,"1");
    addVertex(g,2,"2");
    addVertex(g,3,"3");
    addVertex(g,4,"4");
    addVertex(g,5,"5");
    addVertex(g,6,"6");
    addEdge(g,0,1,1);
    addEdge(g,1,2,2);
    addEdge(g,1,3,1);
    addEdge(g,2,3,2);
    addEdge(g,2,4,3);
    addEdge(g,3,4,2);
    addEdge(g,3,2,1);
    addEdge(g,4,5,1);
    addEdge(g,2,1,3);
    addEdge(g,5,6,3);
    addEdge(g,1,4,2);*/
    randomDirectedGraphInit(g, 6, 10);
    bfsOut(g, 1, 5, "../files/bfs");
    dfsOut(g, 1, 5, "../files/dfs");
    dropGraph(g);
}