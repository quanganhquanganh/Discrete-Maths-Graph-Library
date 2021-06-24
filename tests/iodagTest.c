#include "../io/iodot.h"
#include "randomGraph.c"

int main() {
    Graph g = createGraph();
    /*
    addVertex(g, 0, "a"); addVertex(g, 1, "b");
    addVertex(g, 2, "c"); addVertex(g, 3, "d");
    addVertex(g, 4, "e");

    //addEdge(g, 0, 0, 1);
    //addEdge(g, 1, 1, 1);
    //addEdge(g, 2, 2, 1);
    //addEdge(g, 3, 3, 1);
    //addEdge(g, 4, 4, 1);

    addEdge(g, 1, 0, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 1, 1);
    
    addEdge(g, 3, 4, 1);
    addEdge(g, 4, 0, 1);
    */

    randomDirectedGraphInit(g, 10, 12);

    dagOut(g, "../files/dag");
    dropGraph(g);
}