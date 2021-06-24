#include "iodot.h"
#include "graph.h"
#include "dllist.h"
#include "components.h"
#include <stdio.h>
#include "spanningtrees.h"

void coloringOut(Graph g, const char *output)
{
    layout = CIRCO;
    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    int coloring[100], V;
    V = graphColoring(g, coloring);

    FILE *fptr = open_file(dotFile, "w+");
    fprintf(fptr, "graph dothi\n{\n");

    for (int i = 1; i <= V; i++)
    {
        fprintf(fptr, "\t%d [fillcolor=%s, style=filled];\n", i, color[coloring[i]]);
    }
    Dllist edges = getAllEdges(g), ptr;
    dll_traverse(ptr, edges)
    {
        double *entry = ptr->val.v;
        fprintf(fptr, "\t%d -- %d;\n", entry[1], entry[2]);
    }
    fprintf(fptr, "}");
    fclose(fptr);
    dot_to_pdf(dotFile, pdfFile);
}

void putColors(int vertices[], int n, int color)
{
    //Color must be other than 1
    for (int i = 0; i < n; ++i)
        if (vertices[i] == 1)
            vertices[i] = color;
}

void countComponentsOut(Graph g, const char *filename)
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
    for (int i = 0; i < v_num; ++i)
    {
        if (visited[i] <= MAX_COLOR)
            fprintf(f, "\t%d [fillcolor = %s, style = filled];\n", i, color[visited[i]]);
    }
    Dllist edges = getAllEdges(g), node;
    dll_traverse(node, edges)
    {
        double *edge = node->val.v;
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
    for (int i = 0; i < v_num; i++)
    {
        printf("%d : %d\n", i, LOW[i]);
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
int inpath_dag(int *pathf, int *pathr, int id, int lengthf, int lengthr)
{
    for (int i = 0, j = 0; lengthf > i, lengthr > j; i++, j++)
    {
        if (pathf[i] == id || pathr[j] == id)
        {
            return 1;
        }
    }
    return 0;
}

void dagOut(Graph g, const char *output)
{
    layout = CIRCO;
    JRB node, ptr;
    int pathf[100] = {-oo};
    int lengthf;
    int pathr[100] = {-oo};
    int lengthr;
    int to = DAG(g);
    if (to == -1)
    {
        printf("Can't find a topo order.\n");
        return;
    }
    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    double disf, disr;
    jrb_traverse(node, g.vertices)
    {
        int v = node->key.i;
        disf = dijkstra(g, v, to, pathf, &lengthf);
        disr = dijkstra(g, to, v, pathr, &lengthr);
        if (disf != oo && disr != oo)
        {
            break;
        }
        else
        {
            memset(pathf, -oo, sizeof(pathf));
            memset(pathr, -oo, sizeof(pathr));
        }
    }
    if (disf == oo || disr == oo || lengthf == 0 || lengthr == 0)
    {
        printf("No cycle\n");
        exit(0);
    }
    FILE *fp = fopen(dotFile, "w+");
    fprintf(fp, "digraph {\n");
    jrb_traverse(node, g.vertices)
    {
        if (inpath_dag(pathf, pathr, node->key.i, lengthr, lengthf) == 1)
        {
            fprintf(fp, "\t%d [fillcolor = yellow, style = filled];\n", node->key.i);
        }
        else
        {
            //fprintf(fp,"\t%d [fillcolor = yellow, style = fill];\n",node->key.i);
        }
    }
    jrb_traverse(node, g.vertices)
    {
        int out, output[10];
        out = outdegree(g, node->key.i, output);
        for (int i = 0; out > i; i++)
        {
            //fprintf(fp,"\t%d %d[label= %lg,fillcolor = yellow, style = filled]\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            if (inpath_dag(pathf, pathr, node->key.i, lengthf, lengthr) && inpath_dag(pathf, pathr, output[i], lengthf, lengthr))
            {
                fprintf(fp, "\t%d -> %d[label= %lg,color = green, genwidth = 2.0]\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
            else
            {
                fprintf(fp, "\t%d -> %d[label= %lg];\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
    dot_to_pdf(dotFile, pdfFile);
}
int arrD[100], arrB[100], ii = 0;

void get_init_DFS()
{
    for (int k = 0; 100 > k; k++)
    {
        arrD[k] = -oo;
    }
}

void get_init_BFS()
{
    for (int k = 0; 100 > k; k++)
    {
        arrB[k] = -oo;
    }
}

void addToArrD(int m)
{
    arrD[ii++] = m;
}

void addToArrB(int m)
{
    arrB[ii++] = m;
}

int inarrD(int n)
{
    for (int k = 0; 100 > k; k++)
    {
        if (arrD[k] == n)
        {
            return 1;
        }
    }
    return 0;
}

int inarrB(int n)
{
    for (int k = 0; 100 > k; k++)
    {
        if (arrB[k] == n)
        {
            return 1;
        }
    }
    return 0;
}

void bfsOut(Graph g, int s, int t, const char *output)
{
    layout = CIRCO;
    get_init_BFS();
    BFS(g, s, t, addToArrB);

    JRB node;

    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    // tao file Bfs.dot
    FILE *fpbfs = fopen(dotFile, "w+");
    fprintf(fpbfs, "digraph {\n");
    jrb_traverse(node, g.vertices)
    {
        if (inarrB(node->key.i) == 1)
        {
            fprintf(fpbfs, "\t%d [fillcolor = yellow, style=filled];\n", node->key.i);
            continue;
        }
        else
            fprintf(fpbfs, "\t%d [xlabel = \"\"];\n", node->key.i);
    }
    jrb_traverse(node, g.vertices)
    {
        int out, output[100];
        out = outdegree(g, node->key.i, output);
        for (int i = 0; out > i; i++)
        {
            if (inarrB(node->key.i) == 1 && inarrB(output[i]) == 1)
            {
                fprintf(fpbfs, "\t%d -> %d[label=%lg, color=green, penwidth=2.0];\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
            else
            {
                fprintf(fpbfs, "\t%d -> %d[label=%lg];\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
        }
    }
    fprintf(fpbfs, "}");
    fclose(fpbfs);
    dot_to_pdf(dotFile, pdfFile);
}

void dfsOut(Graph g, int s, int t, const char *output)
{
    layout = CIRCO;
    get_init_DFS();
    DFS(g, s, t, addToArrD);

    JRB node;

    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    // tao file Dfs.dot
    FILE *fpdfs = fopen(dotFile, "w+");
    fprintf(fpdfs, "digraph {\n");
    jrb_traverse(node, g.vertices)
    {
        if (inarrD(node->key.i) == 1)
        {
            fprintf(fpdfs, "\t%d [fillcolor = yellow, style=filled];\n", node->key.i);
            continue;
        }
        else
            fprintf(fpdfs, "\t%d [xlabel = \"\"];\n", node->key.i);
    }
    jrb_traverse(node, g.vertices)
    {
        int out, output[100];
        out = outdegree(g, node->key.i, output);
        for (int i = 0; out > i; i++)
        {
            if (inarrD(node->key.i) == 1 && inarrD(output[i]) == 1)
            {
                fprintf(fpdfs, "\t%d -> %d[label=%lg, color=green, penwidth=2.0];\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
            else
            {
                fprintf(fpdfs, "\t%d -> %d[label=%lg];\n", node->key.i, output[i], getEdgeValue(g, node->key.i, output[i]));
            }
        }
    }
    fprintf(fpdfs, "}\n");
    fclose(fpdfs);

    dot_to_pdf(dotFile, pdfFile);
}

const char *color[] = {
    "red", "green", "blue", "yellow", "purple",
    "orange", "aqua", "bisque", "darkolivegreen1", "gray50", "maroon", "wheat3",
    "blueviolet", "chocolate", "cyan", "darkgreen", "darkorange", "firebrick",
    "lawngreen", "gold", "darkkhaki", "salmon"};
const int MAX_COLOR = sizeof(color) / sizeof(*color);

FILE *open_file(const char *n, const char *mode)
{
    FILE *fp = fopen(n, mode);
    if (fp == NULL)
    {
        printf("Error opening file with designation \"%s\" in local directory.\n", n);
        exit(1);
    }
    return fp;
}

void dot_to_pdf(const char *dot, const char *pdf)
{

    extern const char *layout;
    char command[100];
    sprintf(command, "%s -Tpdf %s -o %s", layout, dot, pdf);
    printf("Running: %s...\n", command);
    system(command);
    system("pause");
}

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
void primOut(Graph g, Graph tree, const char *output)
{
    layout = CIRCO;
    char dotname[100] = {0};
    char pdfname[100] = {0};
    strcat(dotname, output);
    strcat(dotname, ".dot");
    strcat(pdfname, output);
    strcat(pdfname, ".pdf");

    FILE *is = open_file(dotname, "w+");
    if (primAlgo(g, tree) == 1)
    {
        outputfileMST(g, tree, is);
        dot_to_pdf(dotname, pdfname);
    }
    else
        printf("Couldn't find any spanning tree.\n");
}
void kruskalOut(Graph g, Graph tree, const char *output)
{
    layout = CIRCO;
    char dotname[100] = {0};
    char pdfname[100] = {0};
    strcat(dotname, output);
    strcat(dotname, ".dot");
    strcat(pdfname, output);
    strcat(pdfname, ".pdf");
    FILE *is = open_file(dotname, "w+");
    if (primAlgo(g, tree) == 1)
    {
        outputfileMST(g, tree, is);
        dot_to_pdf(dotname, pdfname);
    }
    else
        printf("Couldn't find any spanning tree.\n");
}
int count = 1;

void simple_dfs(Graph g, int id, int *pre, JRB post){
    if(pre[id]==0){
        pre[id] = count;
        count ++;
        int out, output[10];
        out = outdegree(g,id,output);
        for(int i=0;out>i;i++){
            simple_dfs(g,output[i],pre,post);
        }
        jrb_insert_int(post,count,new_jval_i(id));
        count++;
    }
}

void full_simple_dfs(Graph g, int *pre, JRB post){
    JRB node;
    jrb_traverse(node,g.vertices){
        if(pre[node->key.i]==0){
            simple_dfs(g,node->key.i,pre,post);
        }
    }
}

void topoOut(Graph g, const char* output) {
    layout = DOT;
    int pre[100]={0};
    JRB node;
    JRB post = make_jrb();

    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    full_simple_dfs(g,pre,post);
    jrb_rtraverse(node,post){
        printf("%d %d %s\n",pre[node->val.i],node->key.i,getVertex(g,node->val.i));
    }
    char *color[6] = {
        "red","yellow","green","blue","purple","orange"
    };
    int result[100]={0};
    jrb_traverse(node, g.vertices)
    {
        int v = node->key.i;
        result[v] = 0;
        int ou[100],in[100];
        int n = outdegree(g, v, ou);
        int m = indegree(g, v, in);
        for (int i = 0; i < n; i++)
        {
            if (ou[i] != v && result[ou[i]] == result[v])
                result[ou[i]] = result[v]++;
        }
        for (int i = 0; i < m; i++)
        {
            if (in[i] != v && result[in[i]] == result[v])
                result[in[i]] = result[v]++;
        }
    }
    // tao file topo.dot
    FILE *fp = fopen(dotFile,"w+");
    fprintf(fp,"digraph {\n");
    jrb_rtraverse(node,post){
        fprintf(fp,"\t%d [label=%s, xlabel= \"%d,%d\", fillcolor= %s, style=filled];\n",node->val.i,getVertex(g,node->val.i),pre[node->val.i],node->key.i,color[result[node->val.i]]);
    }
    jrb_traverse(node,g.vertices){
        int out, output[100];
        out = outdegree(g,node->key.i,output);
        for(int i=0;out>i;i++){
            fprintf(fp,"\t%d -> %d [label=%lg];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
        }
    }
    jrb_free_tree(post);
    fprintf(fp,"}");
    fclose(fp);
    dot_to_pdf(dotFile, pdfFile);
}