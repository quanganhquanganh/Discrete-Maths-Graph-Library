#include "prufer.h"
#include <stdio.h>

int main()
{
    FILE *f = fopen("files/input.txt", "r");

    Graph g = createGraph();
    int n = pruferInputGraph(f, g);
    int code[100], length;
    prufer(g, code, &length);
    for (int i = 0; i < length; ++i)
    {
        printf("%4d", code[i]);
    }
}