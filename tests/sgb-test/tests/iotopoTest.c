#include "iodot.h"
#include "randomgraph.h"

int main()
{
    Graph g = createGraph();
    //addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
    //addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
    //addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
    //addEdge(g, 0, 1, 1); addEdge(g, 0, 2, 1);
    //addEdge(g, 1, 3, 1); addEdge(g, 5, 4, 1); addEdge(g, 3, 4, 1);
    randomDirectedGraphInit(g, 6, 6);
    if (DAG(g) == -1)
    {
        printf("Can not make topological sort\n");
        return 1;
    }
    topoOut(g, "../files/topo");
    dropGraph(g);
}