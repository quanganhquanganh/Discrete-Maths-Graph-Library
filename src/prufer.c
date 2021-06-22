#include "prufer.h"

#include "../libfdr/dllist.h"

int pruferInputGraph(FILE* f, Graph g) {
    int so_dinh = -1, id1 = -1, id2 = -1;
    fscanf(f, "%d", &so_dinh);
    for (int i = 0; i < so_dinh; i++)
    {
        fscanf(f, "%d %d", &id1, &id2);
        addEdge(g, id1, id2, 1);
        addEdge(g, id2, id1, 1);
        addVertex(g, id1, "v");
        addVertex(g, id2, "v");
    }
    return so_dinh;
}

void prufer_2(Graph g, int start, int remainingVertices, int* code, int* length) {
    int min = 1000;
    int temp[100];
    int n, visited[1000] = {0};
    int output[100], u, v;
    *length = 0;
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
        //removeEdge(g, output[0], min);
        code[(*length)++] = output[0];
        //printf("%4d", output[0]);
        remainingVertices--;
        prufer_2(g, start, remainingVertices, code, length);
    }
}

void prufer(Graph g, int output[], int* length) {
    *length = 0;
    /*
    *Malloc and initialize the vertices' degrees array (deg[]) 
    *with all zeroes
    */
    int deg[1000] = {0};
    int outdeg[100], n, v_num;
    double* entry;
    /*
    *Malloc a S[] array for the prufer code and create a
    *size variable that tracks the array's filled slots
    */

    /*
    *Add in the degrees by incrementing
    *elements of indexes from EDGE[]
    */
    v_num = 0;
    JRB node;
    jrb_traverse(node, g.vertices) {
        n = outdegree(g, (node->key).i, outdeg);
        deg[(node->key).i] += n;
        v_num++;
    }
    /*
    *Find the leaf of smallest lable by
    *checking whether it's degree is equal to 1.
    *The lable is min.
    */
    int min = 0;  
    while (deg[min] > 1) 
        min++;
    Dllist ptr, EDG = getAllEdges(g);
    //Create Prufer Sequence
    for (int i = 0; i < v_num - 2 ; i++) {
        //printf("----------------\n");
        dll_traverse(ptr, EDG) {
            double *l = NULL, *n = NULL;
            entry = jval_v(ptr->val);
            //printf("%lf -- %lf\n", entry[1], entry[2]);
            if (entry[1] == min) {
                l = &(entry[1]);
                n = &(entry[2]);
            } else if (entry[2] == min) {
                l = &(entry[2]);
                n = &(entry[1]);
            }
            if(l != NULL) {  
                /*
                *Min leaf is now found. Remove the leaf by incrementing its degree
                *as well as reassigning it's value to 0
                */
                int il = *l;
                deg[il] += 1;
                *l = -1;
                /*
                *Add the neighbor to the sequence and increase it's size.
                *Decrease the neighbor's degree by one
                *as well as reassign it's value to 0
                */
                output[(*length)++] = *n;
                //printf("%d\n", *length);
                int in = *n;
                deg[in] -= 1;
                *n = -1;
            }
        }
        //Get new leaf with the smallest lable
        min = 0;  
        while (deg[min] > 1) min++;
    }
}