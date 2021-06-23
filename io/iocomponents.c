#include "iodot.h"
#include "../src/components.c"

void putColors(int vertices[], int n, int color) {
    //Color must be other than 1
    for(int i = 0; i < n; ++i)
        if(vertices[i] == 1) vertices[i] = color;
}

void countComponentsOut(Graph g, const char* filename) {
    layout = CIRCO;
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

    jrb_traverse(ptr, g.vertices) v_num++;
    printf("%d\n", v_num);
    memset(visited, 0, sizeof(visited));
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
        fprintf(f, "\t%d -> %d [dir=none];\n", l, n);
    }
    fprintf(f, "}");
    fclose(f);
    dot_to_pdf(dotname, pdfname);
}


void countStronglyComponentsOut(Graph g, const char *filename)
{
    layout = CIRCO;
    char dotname[100];
    char pdfname[100];

    strcpy(dotname, filename);
    strcpy(pdfname, filename);
    strcat(dotname, ".dot");
    strcat(pdfname, ".pdf");

    FILE *f = open_file(dotname, "w");
    JRB ptr;
    int dem = 0, v_num = 0;
    int LOW[10000];
    int cl[10000];
    memset(LOW, 0, sizeof(LOW));
    printf("%d\n", countStronglyConnected(g, LOW, 10000));

    fprintf(f, "digraph {\n");
    jrb_traverse(ptr, g.vertices) v_num++;
    /*
    for (int i = 0; i < v_num; i++)
    {
        cl[i] = LOW[i];
        printf("%d-%d\n", i, cl[i]);
    }*/
    for (int i = 0; i < v_num; i++)
    {
        /*
        printf("%d-%d\n", i, LOW[i]);
        
        if (LOW[i] != i)
        {
            dem++;
            LOW[i] = LOW[cl[i]];
        }
        else
            LOW[i] -= dem;
        printf("---------%d-%d\n", i, LOW[i]);*/

        if (LOW[i] <= MAX_COLOR)
            fprintf(f, "\t%s [fillcolor = %s, style = filled];\n", getVertex(g, i), color[LOW[i] % MAX_COLOR]);
    }

    int v, n, ou[10000];
    jrb_traverse(ptr, g.edges)
    {
        v = ptr->key.i;
        n = outdegree(g, v, ou);
        for (int i = 0; i < n; i++)
        {
            if (v != ou[i])
            {
                if (getEdgeValue(g, ou[i], v) != oo && getEdgeValue(g, v, ou[i]) != oo)
                {
                    if (ou[i] < v)
                        fprintf(f, "%s -> %s [dir=none] [label = %g];\n", getVertex(g, v), getVertex(g, ou[i]), getEdgeValue(g, v, ou[i]));
                }
                else
                    fprintf(f, "%s -> %s[label = %g];\n", getVertex(g, v), getVertex(g, ou[i]), getEdgeValue(g, v, ou[i]));
            }
        }
    }
    fprintf(f, "label=stronglyConnectComponent}");
    fclose(f);
    dot_to_pdf(dotname, pdfname);
}