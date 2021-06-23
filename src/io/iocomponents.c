#include "iodot.h"
#include "../components.c"
#include <string.h>

void putColors(int vertices[], int n, int color) {
    //Color must be other than 1
    for(int i = 0; i < n; ++i)
        if(vertices[i] == 1) vertices[i] = color;
}

void countComponentsOut(Graph g, const char* filename) {
    char dotname[100];
    char pdfname[100];
    
    strcpy(dotname, filename);
    strcpy(pdfname, filename);
    strcat(dotname, ".dot");
    strcat(pdfname, ".pdf");

    FILE* f = open_file(dotname, "w");
    JRB ptr;
    int dem = 0, v_num = 0;
    int visited[10000];

    memset(visited, 0, sizeof(visited));
    jrb_traverse(ptr, g.vertices) v_num++;
    jrb_traverse(ptr, g.vertices)
    {
        if (!visited[ptr->key.i])
        {
            dem++;
            countComponentsUtil(g, ptr->key.i, -1, visited);
            putColors(visited, v_num, dem + 1);
        }
    }
    fprintf(f, "digraph {\n");
    for(int i = 0; i < v_num; ++i) {
        if(visited[i] <= MAX_COLOR)
            fprintf(f, "\t%d [fillcolor = %s, style = filled];\n", i, color[visited[i]]);
    }
    Dllist edges = getAllEdges(g), node;
    dll_traverse(node, edges) {
        double* edge = node->val.v;
        int l = edge[1], n = edge[2];
        fprintf(f, "\t%d -- %d;\n", l, n);
    }
    fprintf(f, "}");
    fclose(f);
    dot_to_pdf(dotname, pdfname);
}