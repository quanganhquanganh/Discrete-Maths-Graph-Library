#include "iodot.h"
#include "../src/coloring.c"
#include "../libfdr/dllist.h"

void coloringOut(Graph g, const char* output) {
    layout = CIRCO;
    char dotFile[100] = {0}, pdfFile[100] = {0};

    strcat(dotFile, output);
    strcat(dotFile, ".dot");

    strcat(pdfFile, output);
    strcat(pdfFile, ".pdf");

    int coloring[100], V;
    V = graphColoring(g, coloring);

    FILE *fptr = open_file(dotFile,"w+");
    fprintf(fptr,"graph dothi\n{\n");

    for(int i = 1; i <= V; i++){
        fprintf(fptr,"\t%d [fillcolor=%s, style=filled];\n", i, color[coloring[i]]);
    }
    Dllist edges = getAllEdges(g), ptr;
    dll_traverse(ptr, edges) {
        double* entry = ptr->val.v;
        fprintf(fptr,"\t%d -- %d;\n",entry[1],entry[2]);
    }
    fprintf(fptr,"}");
    fclose(fptr);
    dot_to_pdf(dotFile, pdfFile);
}
