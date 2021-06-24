#include "iodot.h"
#include "../libfdr/dllist.h"

int inpath(int id,int path[],int length){
    for(int i=0;length>i;i++){
        if(id==path[i]) return 1;
    }
    return 0;
}

void dijkstraOut(Graph g, int s, int t, const char* output) {
    layout = CIRCO;
    int i, length, path[100];
    double w;
    w = dijkstra(g, s, t, path, &length);
    if(w == oo) {
        printf("Couldn't find a path between two specified points.\n");
        return;
    }
    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    if (w == oo)
    {
         printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Path from %s to %s (with total distance %lg)\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
            if(i == length-1) printf(" => %s",getVertex(g, path[i]));
            else printf(" => %s (%lg)", getVertex(g, path[i]),getEdgeValue(g,path[i],path[i+1]));
        printf("\n");
    }

    FILE *fp = fopen(dotFile,"w+");
    Dllist list = getAllEdges(g);
    Dllist node;
    fprintf(fp,"digraph {\n");
    JRB all;
    jrb_traverse(all,g.vertices){
        if(inpath(all->key.i,path,length)){
            fprintf(fp,"\t%d [fillcolor = yellow, style=filled];\n",all->key.i);
        }
        else fprintf(fp,"\t%d [xlabel = \"%s\"];\n",all->key.i, all->val.i);
    }
    dll_traverse(node,list){
        double *entry = jval_v(node->val);
        if(inpath((int)(entry[1]),path,length)==1&&inpath((int)(entry[2]),path,length)==1) {
            fprintf(fp,"\t%lg -> %lg[label=%lg, color=green, penwidth=2.0];\n",entry[1],entry[2],entry[0]);
            continue;
        }
        else{
            fprintf(fp,"\t%lg -> %lg[label=%lg];\n",entry[1],entry[2],entry[0]);
        }
    }
    fprintf(fp,"}\n");
    fclose(fp);
    dot_to_pdf(dotFile, pdfFile);
}

void bellmanfordOut(Graph g, int s, int t, const char* output) {
    layout = CIRCO;
    int i, length, path[100];
    double w;
    w = bellmanford(g, s, t, path, &length);
    if(w == oo) {
        printf("Couldn't find a path between two specified points.\n");
        return;
    }

    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    if (w == oo)
    {
         printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Path from %s to %s (with total distance %lg)\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
            if(i == length-1) printf(" => %s",getVertex(g, path[i]));
            else printf(" => %s (%lg)", getVertex(g, path[i]),getEdgeValue(g,path[i],path[i+1]));
        printf("\n");
    }


    FILE *fp = fopen(dotFile,"w+");
    Dllist list = getAllEdges(g);
    Dllist node;
    fprintf(fp,"digraph {\n");
    JRB all;
    jrb_traverse(all,g.vertices){
        if(inpath(all->key.i,path,length)){
            fprintf(fp,"\t%d [fillcolor = yellow, style=filled];\n",all->key.i);
        }
        else fprintf(fp,"\t%d [xlabel = \"%s\"];\n",all->key.i, all->val.i);
    }
    dll_traverse(node,list){
        double *entry = jval_v(node->val);
        if(inpath((int)(entry[1]),path,length)==1&&inpath((int)(entry[2]),path,length)==1) {
            fprintf(fp,"\t%lg -> %lg[label=%lg, color=green, penwidth=2.0];\n",entry[1],entry[2],entry[0]);
            continue;
        }
        else{
            fprintf(fp,"\t%lg -> %lg[label=%lg];\n",entry[1],entry[2],entry[0]);
        }
    }
    fprintf(fp,"}\n");
    fclose(fp);
    dot_to_pdf(dotFile, pdfFile);
}