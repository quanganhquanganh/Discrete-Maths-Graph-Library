#include "coloring.h"
#include <stdlib.h>

int graphColoring(Graph g, int* result)  {
    JRB node;
    result[0] = 0;
    int v_num, total, output[100];
    jrb_traverse(node, g.vertices) 
        v_num++;

    for (int i = 1; i < v_num; i++)
        result[i] = -1;

    int* available = calloc(v_num, sizeof(int));

    for (int i = 1; i < v_num; i++)
    {
        total = getAdjacentVertices(g, i, output);
        for (int j = 0; j < total; j++) {
            int adj = output[j];

            if (result[adj] != -1)
                available[result[adj]] = 1;
        }
        
        int cl = 0;
        for (; cl < v_num; cl++)
            if (available[cl] == 0)
                break;
 
        result[i] = cl;

        for (int j = 0; j < total; j++) {
            int adj = output[j];

            if (result[adj] != -1)
                available[result[adj]] = 0;
        }
    }

    free(available);
    return v_num;
}
