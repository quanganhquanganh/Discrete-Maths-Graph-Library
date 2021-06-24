#include "iodot.h"
#include "../libfdr/dllist.h"

int inpath_dag(int *pathf,int *pathr,int id,int lengthf,int lengthr){
    for(int i=0,j=0;lengthf>i,lengthr>j;i++,j++){
        if(pathf[i]==id||pathr[j]==id){
            return 1;
        }
    }
    return 0;
}

void dagOut(Graph g, const char* output) {
    layout = CIRCO;
    JRB node, ptr;
    int pathf[100] = {-oo};
    int lengthf;
    int pathr[100] = {-oo};
    int lengthr;
    int to = DAG(g);
    if(to == -1) {
        printf("Can't find a topo order.\n");
        return;
    }
    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    double disf,disr;
    jrb_traverse(node,g.vertices){
        int v = node->key.i;
        disf = dijkstra(g,v,to,pathf,&lengthf);
        disr = dijkstra(g,to,v,pathr,&lengthr);
        if(disf != oo && disr != oo){
            break;
        }
        else{
            memset(pathf, -oo, sizeof(pathf));
            memset(pathr, -oo, sizeof(pathr));
        }
    }
    if(disf==oo||disr==oo||lengthf==0||lengthr==0){
        printf("No cycle\n");
        exit(0);
    }
    FILE *fp = fopen(dotFile,"w+");
    fprintf(fp,"digraph {\n");
    jrb_traverse(node,g.vertices){
        if(inpath_dag(pathf,pathr,node->key.i,lengthr,lengthf)==1){
            fprintf(fp,"\t%d [fillcolor = yellow, style = filled];\n",node->key.i);
        }
        else{
            //fprintf(fp,"\t%d [fillcolor = yellow, style = fill];\n",node->key.i);
        }
    }
    jrb_traverse(node,g.vertices){
        int out,output[10];
        out = outdegree(g,node->key.i,output);
        for(int i=0;out>i;i++){
            //fprintf(fp,"\t%d %d[label= %lg,fillcolor = yellow, style = filled]\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            if(inpath_dag(pathf,pathr,node->key.i,lengthf,lengthr)&&inpath_dag(pathf,pathr,output[i],lengthf,lengthr)){
                fprintf(fp,"\t%d -> %d[label= %lg,color = green, genwidth = 2.0]\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
            else{
                fprintf(fp,"\t%d -> %d[label= %lg];\n",node->key.i,output[i],getEdgeValue(g,node->key.i,output[i]));
            }
        }
    }
    fprintf(fp,"}\n");
    fclose(fp);
    dot_to_pdf(dotFile, pdfFile);
}