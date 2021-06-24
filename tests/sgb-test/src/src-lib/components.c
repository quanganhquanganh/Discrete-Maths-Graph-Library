#include "components.h"
#include "dllist.h"
#include <stdlib.h>
#include <string.h>

int Min(int a, int b)
{
    return a < b ? a : b;
}

void countComponentsUtil(Graph graph, int start, int stop, int *visited)
{
    int n, output[100], i, u, v;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            visited[u] = 1;
            if (u == stop)
                return;
            n = outdegree(graph, u, output);
            for (i = 0; i < n; i++)
            {
                v = output[i];
                if (!visited[v])
                    dll_append(stack, new_jval_i(v));
            }
        }
    }
}

int countConnected(Graph g) {
    JRB node;
    int dem = 0;
    int* visited = malloc(sizeof(int) * 10000);
    memset(visited, 0, sizeof(visited));
    jrb_traverse(node, g.vertices)
    {
        if (!visited[node->key.i])
        {
            dem++;
            countComponentsUtil(g, node->key.i, -1, visited);
        }
    }
    free(visited);
    return dem;
}

int* DIST; 
int* onStack;
int ids = -1, sscCount = -1;

void TarjanDFS(Graph graph, int start, Dllist stack, int LOW[])
{
    Dllist node;
    int n, output[100], i, u, v;
    dll_append(stack, new_jval_i(start));
    onStack[start] = 1;
    DIST[start] = ids++;
    LOW[start] = ids;

    n = outdegree(graph, start, output);
    for (i = 0; i < n; i++)
    {
        v = output[i];
        if (DIST[v] == -1)
        {
            TarjanDFS(graph, v, stack, LOW);
            LOW[start] = Min(LOW[start], LOW[v]);
        }
        else if (onStack[v] == 1)
            LOW[start] = Min(LOW[start], DIST[v]);
    }
    if (LOW[start] == DIST[start])
    {
        while (1)
        {
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);

            onStack[u] = 0;
            LOW[u] = DIST[start];
            if (u == start)
                break;
        }
        sscCount++;
    }
}

int countStronglyConnected(Graph g, int LOW[], int n)
{
    JRB node;
    int dem, u;
    DIST = malloc(sizeof(int) * 20000);
    onStack = DIST + 10000;
    memset(LOW, -1, sizeof(int) * n);
    memset(DIST, -1, sizeof(n) * 10000);
    memset(onStack, 0, sizeof(n) * 10000);
    Dllist temp, stack;

    stack = new_dllist();
    jrb_traverse(node, g.vertices)
    {
        addEdge(g, node->key.i, node->key.i, 1);
    }
    jrb_traverse(node, g.vertices)
    {
        if (DIST[node->key.i] == -1)
        {
            TarjanDFS(g, node->key.i, stack, LOW);
        }
    }
    jrb_traverse(node, g.vertices)
    {
        removeEdge(g, node->key.i, node->key.i);
    }
    free(DIST);
    return sscCount;
}