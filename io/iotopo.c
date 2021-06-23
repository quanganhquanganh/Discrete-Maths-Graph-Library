#include "iodot.h"
#include "../libfdr/dllist.h"

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