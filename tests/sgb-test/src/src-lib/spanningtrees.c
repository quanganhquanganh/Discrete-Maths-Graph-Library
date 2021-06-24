#include "spanningtrees.h"
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>

Jval dequeueMinIncident(Dllist q, Graph g) {
    //Get minimum weight edge incident to any of the g.edges
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
    if (node == NULL) return new_jval_v(NULL);
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
    
    //Add minimum weight edge
    queue = getAllEdges(g);
    entry = jval_v(dequeueMinIncident(queue, g));
    if(!entry) return 0;
    min = entry[0];
    u = entry[1];
    v = entry[2];
    addEdge(T, u, v, min);
    addEdge(T, v, u, min);
    addVertex(T, u, getVertex(g, u)); 
    addVertex(T, v, getVertex(g, v));
    printf("#%d choice: %d -- %d\n", 1, u, v);

    for(i = 0; i < v_num - 2; ++i) {
        //Find minimum weight edge incident to any of the T.vertices
        entry = jval_v(dequeueMinIncident(queue, T));
        if(!entry) return 0;
        min = entry[0];
        u = entry[1];
        v = entry[2];
        //Add edge to T and test for acycles
        addEdge(T, u, v, min);
        addEdge(T, v, u, min);
        a = getVertex(T, u)? 0 : 1;
        b = getVertex(T, v)? 0 : 1;
        addVertex(T, u, getVertex(g, u));
        addVertex(T, v, getVertex(g, v));
        if(UAG(T)) {//Acycle(s) exists
            i--;
            removeEdge(T, u, v);
            removeEdge(T, v, u);
            if(a) removeVertex(T, u);
            if(b) removeVertex(T, v);
            //Remove the added edge and rerun this loop
        } else {//No acycle found.
            printf("#%d choice: %d -- %d\n", i + 2, u, v);
        }
        free(entry);
    }
    return 1;
}

int kruskalAlgo(Graph g, Graph T)
{
    int i, u, v, a, b;
    int v_num;
    Dllist queue;
    double min, *entry;
    JRB vertex;

    v_num = 0;
    jrb_traverse(vertex, g.edges)
        v_num++;

    //Add minimum weight edge
    queue = getAllEdges(g);

    for (i = 0; i < v_num; ++i)
    {
        //Find minimum weight edge incident to any of the T.vertices
        entry = jval_v(dequeueMinIncident(queue, g));
        if (!entry)
            return 0;
        min = entry[0];
        u = entry[1];
        v = entry[2];
        //Add edge to T and test for acycles 
        addVertex(T, u, getVertex(g, u));
        addVertex(T, v, getVertex(g, v));
        addEdge(T, u, v, min);
        addEdge(T, v, u, min);
        if (UAG(T))
        { //Acycle(s) exists
            removeEdge(T, u, v);
            removeEdge(T, v, u);
        }
        else
        { //No acycle found.
            printf("#%d choice: %d -- %d\n", i + 1, u, v);
        }
        free(entry);
    }
    return 1;
}