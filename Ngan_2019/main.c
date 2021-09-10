#include <stdio.h>
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int n, m;
void docfile(FILE *f, Graph g)
{
    int id, id1, id2;
    double weight;
    char name[10];
    f = fopen("data.txt", "r");
    fscanf(f, "%d %d\n", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        fscanf(f, "%d %s\n", &id, name);
        addVertex(g, id, name);
    }
    for (int i = 1; i <= m; i++)
    {
        fscanf(f, "%d %d %lf\n", &id1, &id2, &weight);
        addEdge(g, id1, id2, weight);
        addEdge(g, id2, id1, weight);
    }
    fclose(f);
}

void inDSDinh(Graph g)
{
    JRB iter;
    jrb_traverse(iter, g.vertices)
    {
        printf("%d %s\n", jval_i(iter->key), jval_s(iter->val));
    }
}

void timBanThanNhat(Graph g)
{
    int a;
    printf("Nhap ID: ");
    scanf("%d", &a);
    int output[10];
    double max = 0, k = 0;
    int res = indegree(g, a, output);
    if (res == 0)
    {
        puts("-1");
    }
    else
    {
        for (int j = 0; j < res; j++)
        {
            k = getEdgeValue(g, a, output[j]);
            if (k >= max)
            {
                max = k;
            }
        }
        printf("%.1lf\n", max);
        for (int j = 0; j < res; j++)
        {
            k = getEdgeValue(g, a, output[j]);
            if (k == max)
            {
                printf("%d %s\n", output[j], getVertex(g, output[j]));
            }
        }
    }
}

void quanHeBacCau(Graph g)
{
    int id1, id2;
    int count = 0;
    printf("Nhap id1 và id2: ");
    scanf("%d %d", &id1, &id2);

    int output1[10], output2[10];
    if (getEdgeValue(g, id1, id2) != INFINITIVE_VALUE)
    {
        puts("-1");
    }
    else
    {
        int path[10];
        int *length;
        if (shortestPath(g, id1, id2, path, length) != INFINITIVE_VALUE)
        {
            printf("1");
        }
        else
        {
            printf("-1");
        }
    }
}

void banChung(Graph g)
{
    int id1, id2;
    printf("Nhap: ");
    scanf("%d %d", &id1, &id2);

    int output1[10], output2[10], banchung[10], count =0;
    int res1 = indegree(g, id1, output1);
    int res2 = outdegree(g, id2, output2);
    for(int i=0; i<res1; i++){
        for(int j=0; j<res2; j++){
            if(output1[i]==output2[j]){
                count++;
                banchung[count] = output1[i];
            }
        }
    }
    printf("%d\n", count);
    for(int i=1; i<=count;i++){
        printf("%d %s\n", banchung[i], getVertex(g, banchung[i]));
    }
}

int main()
{
    FILE *f;
    Graph g = createGraph();
    docfile(f, g);
    /*JRB iter;
    jrb_traverse(iter, g.vertices){
        printf("%d %s", jval_i(iter->key), jval_s(iter->val));
    }*/
    int choice;
    while (1)
    {
        puts("");
        puts("MENU: ");
        puts("1. In danh sach dinh");
        puts("2. Tim ban than thiet nhat");
        puts("3. Kiem tra quan he bac cau");
        puts("4. Tim ban chung");
        puts("5. Thoat");
        printf(">>> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inDSDinh(g);
            break;
        case 2:
            timBanThanNhat(g);
            break;
        case 3:
            quanHeBacCau(g);
            break;
        case 4:
            banChung(g);
            break;
        case 5:
            dropGraph(g);
            return 0;
        default:
            puts("Nhap sai!");
            break;
        }
    }
}