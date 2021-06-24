
/* file nay de tranh tinh trang mat het du lieu trong file src/main,c */

#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"

char text[6000][10];
int canh = 0;
int canhb = 0;
int vsted[10000];

int Compare_strA(char *s1, char *s2)
{
    int cnt = 0;
    for (int i = 0; i < 5; i++)
    {
        if (s1[i] != s2[i])
            cnt++;
    }
    if (cnt == 1)
        return 1;
    return 0;
}
int Compare_strB(char *str1, char *str2)
{
    int n = strlen(str1);
    int check = 0;
    int visit[10];
    for (int i = 0; i < n; i++)
    {
        visit[i] = i;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visit[j] == -1)
                continue;
            if (str1[i] == str2[visit[j]])
            {
                check++;
                visit[j] = -1;
                break;
            }
        }
    }
    if (check == 4)
        return 1;
    return 0;
}

int Input(Graph g, Graph g1)
{
    char word[10];
    int count = 0;
    FILE *inp = fopen("sgb-words.txt", "r");
    while (!feof(inp) && fgets(word, 100, inp))
    {
        word[strlen(word) - 1] = 0;
        strcpy(text[count], word);
        addVertex(g1, count, strdup(word));
        count += addVertex(g, count, strdup(word));
    }
    for (int i = 0; i <= count; i++)
    {
        for (int j = 0; j <= count; j++)
        {

            if (Compare_strA(text[i], text[j]) == 1)
            {
                addEdge(g, i, j, "");
                canh++;
            }
            if (Compare_strB(text[i], text[j]) == 1)
            {
                addEdge(g1, i, j, "");
                canhb++;
            }
        }
    }

    fclose(inp);
    return count;
}
int lienthong(Graph g)
{
    JRB node;
    int dem;
    int visited[INFINITIVE];
    memset(visited, 0, sizeof(visited));
    jrb_traverse(node, g->vertices)
    {
        if (!visited[node->key.i])
        {
            dem++;
            DFS(g, node->key.i, -1, visited);
        }
    }
    return dem;
}
/* Bai 2 */
int Min(int a, int b)
{
    return a < b ? a : b;
}
int LOW[6000];
int DIST[6000];
int onStack[6000];
int ids = -1, sscCount = 0;

void TarjanDFS(Graph graph, int start, Dllist stack)
{
    Dllist node;
    int n, output[100], i, u, v;
    dll_append(stack, new_jval_i(start));
    onStack[start] = TRUE;
    DIST[start] = ids++;
    LOW[start] = ids;

    n = outdegree(graph, start, output);
    for (i = 0; i < n; i++)
    {
        v = output[i];
        if (DIST[v] == -1)
        {
            TarjanDFS(graph, v, stack);
            LOW[start] = Min(LOW[start], LOW[v]);
        }
        else if (onStack[v] == TRUE)
            LOW[start] = Min(LOW[start], DIST[v]);
    }
    if (LOW[start] == DIST[start])
    {
        while (1)
        {
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);

            onStack[u] = FALSE;
            LOW[u] = DIST[start];
            if (u == start)
                break;
        }
        sscCount++;
    }
}

int lienthongmanh(Graph g)
{
    JRB node;
    int dem, u;
    memset(LOW, -1, sizeof(LOW));
    memset(DIST, -1, sizeof(DIST));
    memset(onStack, FALSE, sizeof(onStack));
    Dllist temp, stack;

    stack = new_dllist();

    jrb_traverse(node, g->vertices)
    {
        if (DIST[node->key.i] == -1)
        {
            TarjanDFS(g, node->key.i, stack);
        }
    }
    return sscCount;
}

int main()
{
    char begin[10], end[10];
    Graph graph = createGraph();
    Graph graph1 = createGraph();
    JRB node;
    int count = Input(graph, graph1);
    memset(vsted, 0, sizeof(vsted));
    int sum = 0;
    system("clear");
    printf("DO THI 1\n");
    printf("Tong so dinh: %d\n", count);
    printf("Tong so canh: %d\n", canh);
    printf("Tong so thanh phan lien thong : %d\n", lienthong(graph));

    printf("Nhap tu bat dau: ");
    scanf("%s", begin);
    __fpurge(stdin);
    printf("Nhap tu ket thuc: ");
    scanf("%s", end);
    __fpurge(stdin);
    int s = getId(graph, begin);
    int t = getId(graph, end);
    dijkstra(graph, s, t);
    printf("\n-------------------------------------------------------------------------\n");
    printf("DO THI 2\n");
    // Graph graph2 = createGraph();
    // addVertex(graph2, 1, " 1 ");
    // addVertex(graph2, 2, " 2 ");
    // addVertex(graph2, 3, " 3 ");
    // addVertex(graph2, 4, " 4 ");
    // addVertex(graph2, 5, " 5 ");
    // addVertex(graph2, 6, " 6 ");
    // addVertex(graph2, 7, " 7 ");
    // addVertex(graph2, 8, " 8 ");
    // addEdge(graph2, 1, 2, "");
    // addEdge(graph2, 2, 3, "");
    // addEdge(graph2, 3, 1, "");
    // addEdge(graph2, 4, 2, "");
    // addEdge(graph2, 4, 3, "");

    // addEdge(graph2, 4, 5, "");
    // addEdge(graph2, 5, 4, "");
    // addEdge(graph2, 6, 3, "");

    // addEdge(graph2, 5, 6, "");
    // addEdge(graph2, 6, 7, "");
    // addEdge(graph2, 8, 5, "");

    // addEdge(graph2, 7, 6, "");
    // addEdge(graph2, 8, 8, "");
    // addEdge(graph2, 8, 7, "");

    printf("Tong so dinh: %d\n", count);
    printf("Tong so canh: %d\n", canhb);
    printf("Tong so thanh phan lien thong manh : %d\n", lienthongmanh(graph1));
    // for (int i = 1; i < 9; i++)
    // {
    //     printf("%d-%d-%d\n", LOW[i], DIST[i], onStack[i]);
    // }

    //b
    printf("\n\nNhap u: ");
    scanf("%s", begin);
    __fpurge(stdin);
    s = getId(graph, begin);

    for (int i = 0; i < ids; i++)
    {
        if (LOW[s] == LOW[i])
            printf("%7s\n", getVertex(graph1, i));
    }
    // //C
    printf("\n\nNhap tu bat dau: ");
    scanf("%s", begin);
    __fpurge(stdin);
    printf("Nhap tu ket thuc: ");
    scanf("%s", end);
    __fpurge(stdin);
    s = getId(graph, begin);
    t = getId(graph, end);
    dijkstra(graph1, s, t);
    printf("\n");
    dijkstra(graph1, t, s);
    printf("\n");
    dropGraph(graph);
}
