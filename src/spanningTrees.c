#include "spanningTrees.h"
#include "../libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>

Dllist getAllEdges(Graph g) {
    Graph usedEdges = createGraph();
    JRB child, father;
    double* entry;
    int f, c;
    Dllist list = new_dllist();
    jrb_traverse(father, g.edges)
        jrb_traverse(child, ((JRB)jval_v(father->val))) {
            f = jval_i(father->key);
            c = jval_i(child->key);
            if(getEdgeValue(usedEdges, c, f) == oo) {
                addEdge(usedEdges, f, c, 1);
                entry = malloc(sizeof(double[3]));
                entry[0] = getEdgeValue(g, f, c);
                entry[1] = (double)f;
                entry[2] = (double)c;
                dll_append(list, new_jval_v(entry));
            }
        }
    dropGraph(usedEdges);
    return list;
}

Jval dequeueMinIncident(Dllist q, Graph g) {
    Dllist ptr, node = NULL;
    double min, *entry;
    Jval val;

    if(dll_empty(q)) return new_jval_v(NULL);
    min = oo;
    dll_traverse(ptr, q)
    {
        entry = jval_v(ptr->val);              
        if ((getVertex(g, (int)entry[1]) != NULL ||
            getVertex(g, (int)entry[2]) != NULL) &&
            min > entry[0])
            {
                min = entry[0];
                node = ptr;
            }          
    }
    val = node->val;
    entry = jval_v(val);
    dll_delete_node(node);
    return val;
}

int primAlgo(Graph g, Graph T) {
    int out[100];
    int i, j, u, v, a, b; 
    int n, v_num;
    Dllist ptr, queue, node;
    double min, *entry;
    JRB vertex;

    v_num = 0;
    jrb_traverse(vertex, g.vertices)
        v_num++;
    
    queue = getAllEdges(g);
    entry = jval_v(dequeueMinIncident(queue, g));
    if(!entry) return 0;
    min = entry[0];
    u = entry[1];
    v = entry[2];
    addEdge(T, u, v, min);
    addEdge(T, v, u, min);
    addVertex(T, u, "v"); 
    addVertex(T, v, "v");
    printf("#%d choice: %d -- %d\n", 1, u, v);
    for(i = 0; i < v_num - 2; ++i) {
        entry = jval_v(dequeueMinIncident(queue, T));
        if(!entry) return 0;
        min = entry[0];
        u = entry[1];
        v = entry[2];
        addEdge(T, u, v, min);
        addEdge(T, v, u, min);
        a = getVertex(T, u)? 0 : 1;
        b = getVertex(T, v)? 0 : 1;
        addVertex(T, u, "u");
        addVertex(T, v, "v");
        if(UAG(T)) {
            i--;
            removeEdge(T, u, v);
            removeEdge(T, v, u);
            if(a) removeVertex(T, u);
            if(b) removeVertex(T, v);
        } else {
            printf("#%d choice: %d -- %d\n", i + 2, u, v);
        }
        free(entry);
    }
}