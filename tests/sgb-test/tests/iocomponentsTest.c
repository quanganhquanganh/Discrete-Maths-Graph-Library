#include "iodot.h"
#include "randomgraph.h"

void componentsTest()
{
    Graph g = createGraph();
    addVertex(g, 0, "a");
    addVertex(g, 1, "b");
    addVertex(g, 2, "c");
    addVertex(g, 3, "d");
    addVertex(g, 4, "e");
    addVertex(g, 5, "f");
    addVertex(g, 6, "g");
    addVertex(g, 7, "h");

    addEdge(g, 0, 1, 1);
    addEdge(g, 0, 2, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 0, 1);
    addEdge(g, 2, 0, 1);
    addEdge(g, 2, 1, 1);

    addEdge(g, 3, 4, 1);
    addEdge(g, 4, 3, 1);

    addEdge(g, 5, 6, 1);
    addEdge(g, 6, 7, 1);
    addEdge(g, 6, 5, 1);
    addEdge(g, 7, 6, 1);

    countComponentsOut(g, "files/component");
}

void stronglyComponentsTest()
{
    Graph g = createGraph();
    addVertex(g, 0, "a");
    addVertex(g, 1, "b");
    addVertex(g, 2, "c");
    addVertex(g, 3, "d");
    addVertex(g, 4, "e");
    addVertex(g, 5, "f");
    addVertex(g, 6, "g");
    addVertex(g, 7, "h");

    addEdge(g, 0, 1, 1);
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 0, 1);
    // addEdge(g, 1, 0, 1);
    // addEdge(g, 2, 0, 1);
    // addEdge(g, 2, 1, 1);

    addEdge(g, 3, 4, 1);
    // addEdge(g, 4, 3, 1);

    addEdge(g, 5, 6, 1);
    addEdge(g, 6, 7, 1);
    // addEdge(g, 6, 5, 1);
    // addEdge(g, 7, 6, 1);

    addEdge(g, 0, 0, 1);
    addEdge(g, 1, 1, 1);
    addEdge(g, 2, 2, 1);
    addEdge(g, 3, 3, 1);
    addEdge(g, 4, 4, 1);
    addEdge(g, 5, 5, 1);
    addEdge(g, 6, 6, 1);
    addEdge(g, 7, 7, 1);
    countStronglyComponentsOut(g, "files/stronglycomponent");
}

int main()
{
    Graph g = createGraph();
    randomUndirectedGraphInit(g, 10, 12);
    countComponentsOut(g, "files/component");

    dropGraph(g);
    g = createGraph();
    randomDirectedGraphInit(g, 10, 12);
    countStronglyComponentsOut(g, "files/stronglycomponent");
}