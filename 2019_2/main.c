#include <stdio.h>
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void read_file(Graph G)
{
    FILE* f = fopen("data.txt", "r");
    int m, n; // m dinh, n canh
    int id1, id2;
    char name[1000];
    double distance;
    fscanf(f, "%d %d\n", &m, &n);
    for (int i = 0; i < m; ++i)
    {
        fscanf(f, "%d %s\n", &id1, name);
        addVertex(G, id1, name);
    }

    for (int i = 0; i < n; ++i)
    {
        fscanf(f, "%d %d %lf\n", &id1, &id2, &distance);
        addEdge(G, id1, id2, distance);
        addEdge(G, id2, id1, distance);
    }
}

void hienThiCacDinh(Graph G)
{
    printf("Danh sach dinh: \n");
    JRB iter;
    jrb_traverse(iter, G.vertices)
        printf("%d %s\n", jval_i(iter->key), jval_s(iter->val));
}

void timBanThanThiet(Graph G)
{
    int id;
    printf("Nhap ID = "); scanf("%d", &id);
    if (!jrb_find_int(G.vertices, id))
    {
        printf("ID-%d khong hop le\n", id);
        return;
    }
    int n, output[MAX_PATH_LENGTH];
    double max = 0, d;
    n = outdegree(G, id, output);
    if (n == 0)
        printf("-1\n");
    else
    {
        for (int i = 0; i < n; ++i)
        {
            d = getEdgeValue(G, id, output[i]);
            if (d > max)
                max = d; 
        }
        printf("%.1lf\n", max);
        for (int i = 0; i < n; ++i)
            if (getEdgeValue(G, id, output[i]) == max)
            printf("%d %s\n", output[i], getVertex(G, output[i]));
    }
}

void quanHeBacCau(Graph G)
{
    int length, path[MAX_PATH_LENGTH];
    int id1, id2;
    printf("Nhap ID1 = "); scanf("%d", &id1);
    if (!jrb_find_int(G.vertices, id1))
    {
        printf("ID-%d khong hop le\n", id1);
        return;
    }
    printf("Nhap ID2 = "); scanf("%d", &id2);
    if (!jrb_find_int(G.vertices, id2))
    {
        printf("ID-%d khong hop le\n", id2);
        return;
    }

    shortestPath(G, id1, id2, path, &length);
    printf("%d\n", length);
    if (getEdgeValue(G, id1, id2) != INFINITIVE_VALUE) // co canh truc tiep (length == 2)
        printf("-1\n");
    else if (shortestPath(G, id1, id2, path, &length) == INFINITIVE_VALUE) // Khong co duong di (length chua duoc cap phat gia tri (gia tri rac))
        printf("-1\n");
    else
        printf("1\n"); // Co quan he bac cau (lenght > 2)
}

void timBanChung(Graph G)
{
    int id1, id2;
    printf("Nhap ID1 = "); scanf("%d", &id1);
    if (!jrb_find_int(G.vertices, id1))
    {
        printf("ID-%d khong hop le\n", id1);
        return;
    }
    printf("Nhap ID2 = "); scanf("%d", &id2);
    if (!jrb_find_int(G.vertices, id2))
    {
        printf("ID-%d khong hop le\n", id2);
        return;
    }
    // if (id1 == id2)
        // return;

    int output1[MAX_PATH_LENGTH], output2[MAX_PATH_LENGTH];
    int n_friends = 0, friends[MAX_PATH_LENGTH];
    int n1, n2;
    n1 = outdegree(G, id1, output1);
    n2 = outdegree(G, id2, output2);

    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < n2; ++j)
            if (output1[i] == output2[j])
                friends[n_friends++] = output1[i];
    if (n_friends == 0)
        {printf("-1\n");return;}
    printf("%d\n", n_friends);
    for (int i = 0; i < n_friends; ++i)
        printf("%d %s\n", friends[i], getVertex(G, friends[i]));
}

int main()
{
    // Menu
    Graph G = createGraph();
    
    int select;
    while (1)    
    {
        puts("");
        puts("MENU: ");
        puts("1. In danh sach dinh");
        puts("2. Tim ban than thiet nhat");
        puts("3. Kiem tra quan he bac cau");
        puts("4. Tim ban chung");
        printf(">>> "); scanf("%d", &select);
        switch (select)
        {
        case 1:
            read_file(G);
            hienThiCacDinh(G);
            break;
        case 2:
            timBanThanThiet(G);
            break;
        case 3:
            quanHeBacCau(G);
            break;
        case 4:
            timBanChung(G);
            break;
        case 5:
            dropGraph(G);
            return 0;
        default:
            puts("Nhap sai!");
            break;
        }
    }
}