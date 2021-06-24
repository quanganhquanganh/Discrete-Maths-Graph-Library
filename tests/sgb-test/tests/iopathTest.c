#include "iodot.h"
#include "randomgraph.h"

int main()
{
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();

    randomDirectedGraphInit(g, 10, 15);

    s = 0;
    t = 7;

    dijkstraOut(g, s, t, "../files/dijkstra");
    bellmanfordOut(g, s, t, "../files/bellmanford");
}