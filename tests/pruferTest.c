#include "../src/prufer.h"
#include <stdio.h>

int main() {
    FILE* f = fopen("../files/input.txt", "r");
    Graph g = createGraph();
    pruferInputGraph(f, g);
    int code[100], length;
    prufer(g, )
}