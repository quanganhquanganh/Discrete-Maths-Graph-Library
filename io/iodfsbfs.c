#include "iodot.h"
#include <stdio.h>

int arrD[100],arrB[100], i = 0;

void get_init_DFS(){
    for(int k=0;100>k;k++){
        arrD[k] = -oo;
    }
}

void get_init_BFS(){
    for(int k=0;100>k;k++){
        arrB[k] = -oo;
    }
}

void addToArrD(int m) {
    arrD[i++] = m;
}

void addToArrB(int m) {
    arrB[i++] = m;
}

int inarrD(int n){
    for(int k=0;100>k;k++){
        if(arrD[k] == n) {
            return 1;
        }
    }
    return 0;
}

int inarrB(int n){
    for(int k=0;100>k;k++){
        if(arrB[k] == n) {
            return 1;
        }
    }
    return 0;
}

void bfsOut(Graph g, int s, int t, const char* output) {
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
    fprintf(fpbfs,"digraph {\n");
    jrb_traverse(node,g.vertices){
        if(inarrB(node->key.i)==1){
            fprintf(fpbfs,"\t%d [fillcolor = yellow, style=filled];\n",node->key.i);
            continue;
        }
        else fprintf(fpbfs,"\t%d [xlabel = \"\"];\n",node->key.i);
    }
    jrb_traverse(node,g.vertices){
        int out, output[100];
        out = outdegree(g,node->key.i,output);
        for(int i=0;out>i;i++){
            if(inarrB(node->key.i)==1&&inarrB(output[i])==1){
                fprintf(fpbfs,"\t%d -> %d[label=%lg, color=green, penwidth=2.0];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
            else{
                fprintf(fpbfs,"\t%d -> %d[label=%lg];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
        } 
    }
    fprintf(fpbfs,"}");
    fclose(fpbfs);
    dot_to_pdf(dotFile, pdfFile);
}

void dfsOut(Graph g, int s, int t, const char* output) {
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
    FILE *fpdfs = fopen(dotFile,"w+");
    fprintf(fpdfs,"digraph {\n");
    jrb_traverse(node,g.vertices){
        if(inarrD(node->key.i)==1){
            fprintf(fpdfs,"\t%d [fillcolor = yellow, style=filled];\n",node->key.i);
            continue;
        }
        else fprintf(fpdfs,"\t%d [xlabel = \"\"];\n",node->key.i);
    }
    jrb_traverse(node,g.vertices){
        int out, output[100];
        out = outdegree(g,node->key.i,output);
        for(int i=0;out>i;i++){
            if(inarrD(node->key.i)==1&&inarrD(output[i])==1){
                fprintf(fpdfs,"\t%d -> %d[label=%lg, color=green, penwidth=2.0];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
            else{
                fprintf(fpdfs,"\t%d -> %d[label=%lg];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
        }
    }
    fprintf(fpdfs,"}\n");
    fclose(fpdfs);
    
    dot_to_pdf(dotFile, pdfFile);
}