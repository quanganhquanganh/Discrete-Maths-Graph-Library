#include "iodot.h"
#include "../src/spanningTrees.c"

int checkEdge(Graph g1, Graph g2, int u, int v)
{
    int a, b;
    a = getEdgeValue(g1, u, v);
    b = getEdgeValue(g2, u, v);
    if (a != oo && b != oo)
        return 1;
    else
        return 0;
}
void outputfileMST(Graph graph, Graph tree, FILE *out)
{
    int ou[10000], in[10000], n, m, v, colour[10000] = {0}, max;
    JRB node, node1;
    double *entry;
    int x1, x2;
    fprintf(out, "digraph G {\n");
    jrb_traverse(node, graph.vertices)
    {
        v = node->key.i;
        colour[v] = 1;
        n = outdegree(graph, v, ou);
        m = indegree(graph, v, in);
        for (int i = 0; i < n; i++)
        {
            if (ou[i] != v && colour[ou[i]] == colour[v])
                colour[ou[i]] = colour[v]++;
        }
        for (int i = 0; i < m; i++)
        {
            if (in[i] != v && colour[in[i]] == colour[v])
                colour[in[i]] = colour[v]++;
        }
    }

    jrb_traverse(node, graph.edges)
    {
        v = node->key.i;

        switch (colour[v])
        {
        case 1:
        {
            fprintf(out, "%s [fillcolor=green, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 2:
        {
            fprintf(out, "%s [fillcolor=red, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 3:
        {
            fprintf(out, "%s [fillcolor=blue, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 4:
        {
            fprintf(out, "%s [fillcolor=yellow, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 5:
        {
            fprintf(out, "%s [fillcolor=pink, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 6:
        {
            fprintf(out, "%s [fillcolor=white, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 7:
        {
            fprintf(out, "%s [fillcolor=black, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 8:
        {
            fprintf(out, "%s [fillcolor=orange, style=filled];", getVertex(graph, v));
            break;
        }
        case 9:
        {
            fprintf(out, "%s [fillcolor=purple, style=filled];\n", getVertex(graph, v));
            break;
        }
        case 10:
        {
            fprintf(out, "%s [fillcolor=brown, style=filled];\n", getVertex(graph, v));
            break;
        }
        }

        n = outdegree(graph, v, ou);
        for (int i = 0; i < n; i++)
        {
            if (v != ou[i])
            {
                if (getEdgeValue(graph, ou[i], v) != oo && getEdgeValue(graph, v, ou[i]) != oo)
                {
                    if (ou[i] < v)
                    {
                        fprintf(out, "%s -> %s [dir=none] [label = %g]", getVertex(graph, v), getVertex(graph, ou[i]), getEdgeValue(graph, v, ou[i]));

                        if (checkEdge(graph, tree, ou[i], v) == 1)
                            fprintf(out, "[style =bold] [color =red ];\n");
                        else
                            fprintf(out, ";\n");
                    }
                }
                else
                {
                    fprintf(out, "%s -> %s[label = %g] ;\n", getVertex(graph, v), getVertex(graph, ou[i]), getEdgeValue(graph, v, ou[i]));
                    if (checkEdge(graph, tree, ou[i], v) == 1)
                        fprintf(out, "[style =bold] [color =red ];\n");
                    else
                        fprintf(out, ";\n");
                }
            }
        }
    }
    fprintf(out, "}");
    fclose(out);
}
void primOut(Graph g, Graph tree, const char* output) {
    layout = CIRCO;
    char dotname[100] = {0};
    char pdfname[100] = {0};
    strcat(dotname, output); strcat(dotname, ".dot");
    strcat(pdfname, output); strcat(pdfname, ".pdf");

    FILE* is = open_file(dotname, "w+");
    if(primAlgo(g, tree) == 1) {
        outputfileMST(g, tree, is);
        dot_to_pdf(dotname, pdfname);
    } else printf("Couldn't find any spanning tree.\n");
}
void kruskalOut(Graph g, Graph tree, const char* output) {
    layout = CIRCO;
    char dotname[100] = {0};
    char pdfname[100] = {0};
    strcat(dotname, output); strcat(dotname, ".dot");
    strcat(pdfname, output); strcat(pdfname, ".pdf");
    FILE* is = open_file(dotname, "w+");
    if(primAlgo(g, tree) == 1) {
        outputfileMST(g, tree, is);
        dot_to_pdf(dotname, pdfname);
    } else printf("Couldn't find any spanning tree.\n");
}