#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include "randomgraph.h"
#define MAX_V_NUM 10000
#define MAX_E_NUM 10000
#define MAX_DIST 20

void randomDirectedGraphInit(Graph g, int v_num, int e_num) {
    srand(time(NULL)); double val;
    v_num = (v_num > MAX_V_NUM)? MAX_V_NUM : v_num;
    e_num = (e_num > MAX_E_NUM)? MAX_E_NUM : e_num;
    int i = 0;
    char buff[20] = {0};
    while(i < v_num) {
        sprintf(buff, "%d", i);
        addVertex(g, i, buff);
        i++;
    }
    for(int j = 0; j < e_num; ++j) {
        int l, n;
        l = rand() % v_num;
        do {
            n = rand() % v_num;
        } while((getEdgeValue(g, l, n) != oo) || (getEdgeValue(g, n, l) != oo) || (n==l));
        val = rand() % 20 + 1;
        addEdge(g, l, n, val);
        printf("Random edge: %d -> %d: %lf\n", l, n, val);
    }
}

void randomUndirectedGraphInit(Graph g, int v_num, int e_num) {
    srand(time(NULL)); double val;
    v_num = (v_num > MAX_V_NUM)? MAX_V_NUM : v_num;
    e_num = (e_num > MAX_E_NUM)? MAX_E_NUM : e_num;
    int i = 0;
    char buff[20] = {0};
    while(i < v_num) {
        sprintf(buff, "%d", i);
        addVertex(g, i, buff);
        i++;
    }
    for(int j = 0; j < e_num; ++j) {
        int l, n;
        l = rand() % v_num;
        do {
            n = rand() % v_num;
        } while((getEdgeValue(g, l, n) != oo) || (n==l));
        val = rand() % 20 + 1;
        addEdge(g, l, n, val);
        addEdge(g, n, l, val);
        printf("Random edge: %d -- %d: %lf\n", l, n, val);
    }
}
