#include "prufer.h"

#include "../libfdr/dllist.h"

void pruferInputGraph(FILE* f, Graph g) {
    int so_dinh = -1, id1 = -1, id2 = -1;
    fscanf(f, "%d", &so_dinh);
    Graph g = createGraph(so_dinh + 1);
    for (int i = 0; i < so_dinh; i++)
    {
        fscanf(f, "%d %d", &id1, &id2);
        addEdge(g, id1, id2, 1);
        addEdge(g, id2, id1, 1);
    }
}

void prufer(Graph g, int start, int remainingVertices, int* code, int* length) {
    int min = 1000;
    int temp[100];
    int n, visited[1000] = {0};
    int output[100], u, v;
    Dllist node, queue;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            if (outdegree(g, u, temp) == 1)
            {
                if (u < min && u != start)
                    min = u;
            }
            visited[u] = 1;
            n = outdegree(g, u, output);
            for (int i = 0; i < n; i++)
            {
                v = output[i];
                if (!visited[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }

    if (remainingVertices == 2)
    {
        //printf("\n");
        return;
    }
    else
    {
        outdegree(g, min, output);
        removeEdge(g, min, output[0]);
        removeEdge(g, output[0], min);
        code[(*length)++] = output[0];
        //printf("%4d", output[0]);
        remainingVertices--;
        prufer(g, start, remainingVertices, code, length);
    }
}