#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 1000000
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

int n, m;
Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);

void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);

int indegree(Graph graph, int v, int *output); //w->v
int outdegree(Graph graph, int v, int *output);  //v->w

double shortestPath(Graph graph, int s, int t, int *path, int *length);
void dropGraph(Graph graph);

docfile(FILE *f, Graph g)
{
    int id1, id2, time, i, j, id;
    float qh;
    char ss[5];
    char name[20];
    f = fopen("data.txt", "r");
    fscanf(f, "%d%d", &n, &m);
    //printf(" n = %d m = %d\n", n, m);
    //printf("%d %d\n",n,m);
    fgets(ss, 3, f);
    for (i = 1; i <= n; i++)
    {
        fscanf(f, "%d", &id);
        fscanf(f, "%s", &name);
        // printf("%d %s\n", id, name);
        addVertex(g, id, name);
        fgets(ss, 3, f);
    }
    //printf("%d %d %d\n",id1,id2,time);
    for (i = 1; i <= m; i++)
    {
        fscanf(f, "%d", &id1);
        fscanf(f, "%d", &id2);
        fscanf(f, "%f", &qh);
        // printf("%d %d %.1f\n", id1, id2, qh);
        addEdge(g, id1, id2, qh);
        addEdge(g, id2, id1, qh);
        fgets(ss, 3, f);
    }
    fclose(f);
}

void ingraph(Graph g, int x)
{
    int i, j;
    for (i = 1; i <= x; i++)
    {
        for (j = 1; j <= x; j++)
        {
            double kc = getEdgeValue(g, i, j);
            if (kc == INFINITIVE_VALUE)
                kc = 0;
            printf("%7.0f", kc);
        }
        printf("\n");
    }
}
void duongtruyen(Graph g, int w)
{
    int output[15];
    int res = outdegree(g, w, output); // duong truyen truc tiep tu w
    if (res == 0)
        printf("k co\n");
    else if (res != 0)
    {
        //printf("%d\n",res);
        for (int i = 0; i < res; i++)
        {
            printf("%4d", output[i]);
        }
    }
}
void dt(Graph g, int w)
{
    double kc;
    //getEdgeValue(g, int v1, int v2);
    int output[15];
    int res = outdegree(g, w, output); // duong truyen truc tiep tu w
    if (res == 0)
        printf("k co ban\n");
    else if (res != 0)
    {
        //printf("%d\n",res);
        float max = getEdgeValue(g, output[0], w);

        for (int i = 0; i < res; i++)
        {
            if (getEdgeValue(g, output[i], w) > max)
                max = getEdgeValue(g, output[i], w);
        }
        printf(" max = %.1f\n", max);
        for (int i = 0; i < res; i++)
        {
            if (getEdgeValue(g, output[i], w) == max)
            {
                printf(" %d  %s\n", i, getVertex(g, output[i]));
            }
        }
    }
}
int main(int argc, char *argv[])
{
    FILE *f;
    int key, i, j, x;
    int out[20];
    Graph ngua = createGraph();
    Graph bo = createGraph();
    Graph all = createGraph();
    docfile(f, all);

    //printf(" n= %d m=%d\n",n,m);
    do
    {
        printf("______MENU______\n");
        printf("1.In danh sach dinh\n");
        printf("2.Tim ban than thiet\n");
        printf("3.Kiem tra quan he bac cau\n");
        printf("4.Tim ban chung\n");
        printf("5.Duong di bo ngan nhat\n");
        printf("6.Thoat\n");
        do
        {
            printf("Nhap lua chon: ");
            scanf("%d", &key);
        } while (key < 1 || key > 6);
        switch (key)
        {
        case 6:
            break;
        case 1:
        {

            FILE *f1;
            int n1, m1, id;
            char ss[5];
            char name[20];
            f1 = fopen("data.txt", "r");
            fscanf(f1, "%d%d", &n1, &m1);
            //printf(" n = %d m = %d\n", n1, m1);
            //printf("%d %d\n",n,m);
            fgets(ss, 3, f1);
            for (i = 1; i <= n1; i++)
            {
                fscanf(f1, "%d", &id);
                fscanf(f1, "%s", &name);
                printf("%d %s\n", id, name);
                fgets(ss, 3, f1);
            }
            fclose(f1);
            break;
        }
        case 2:
        {
            int id;
            // duongtruyen(all, 1);
            printf("Nhap vao id : ");
            scanf("%d", &id);
            __fpurge(stdin);

            //printf("id = %d:\n", id);
            dt(all, id);
            printf("\n");

            break;
        }
        case 3:
        {
            int id1, id2;
            int sai = 1;
            int bd, kt, path[20], length;
            printf("Nhap vao id1 : ");
            scanf("%d", &id1);
            __fpurge(stdin);
            printf("Nhap vao id2 : ");
            scanf("%d", &id2);
            __fpurge(stdin);

            double dis = shortestPath(all, id1, id2, path, &length);
            if (dis == INFINITIVE_VALUE)
                sai = -1;
            if (dis != INFINITIVE_VALUE)
            {
                int output[15];
                int res = outdegree(all, id1, output);
                for (int i = 0; i < res; i++)
                {
                    if (output[i] == id2)
                    {
                        sai = -1;
                    }
                }
            }
            printf("%d\n", sai);
            break;
        }

        case 4:
        {
            int id1, id2;
            int output1[15];
            int output2[15];
            int sai = 1;
            int bd, kt, path[20], length;
            printf("Nhap vao id1 : ");
            scanf("%d", &id1);
            __fpurge(stdin);
            printf("Nhap vao id2 : ");
            scanf("%d", &id2);
            __fpurge(stdin);
            int output[15];
            int res1 = outdegree(all, id1, output1); // duong truyen truc tiep tu w
            int res2 = outdegree(all, id2, output2);
            for (int i = 0; i < res1; i++)
            {
                for (int j = 0; j < res2; j++)
                    if (output1[i] == output2[j])
                    {
                        printf(" %d  %s\n", output1[i], getVertex(all, output1[i]));
                    }
            }

            break;
        }

        case 5:
        {

            break;
        }
        }
    } while (key != 6);
    return 0;
}

void addVertex(Graph graph, int id, char *name)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL) // only add new vertex
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}

// Make connection between v1 and v2
void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    //  if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    // {
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
    }
    jrb_insert_int(tree, v2, new_jval_d(weight));
}

// Get weight from v1 to v2
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        return INFINITIVE_VALUE;
    }
    JRB tree = (JRB)jval_v(node->val);
    JRB node1 = jrb_find_int(tree, v2);
    if (node1 == NULL)
    {
        return INFINITIVE_VALUE;
    }
    return jval_d(node1->val);
}

// Liet ke nhung dinh {w} ma ton tai canh w-->v
int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

// Liet ke nhung dinh {w} ma ton tai canh v-->w
int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}
Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void dropGraph(Graph graph)
{
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

double shortestPath(Graph graph, int s, int t, int *path, int *length)
{
    // Khoi tao cac distance = 0
    double distance[1000], min;
    int previous[1000], u, visit[1000];

    for (int i = 0; i < 1000; i++)
    {
        distance[i] = INFINITIVE_VALUE;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;

    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));

    // Duyet Queue
    while (!dll_empty(queue))
    {
        min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue)
        {
            // Lay ra min{distance}
            u = jval_i(ptr->val);
            if (min > distance[u])
            {
                min = distance[u];
                node = ptr;
            }
        }
        u = jval_i(node->val);
        visit[u] = 1;
        dll_delete_node(node);
        if (u == t)
            break;

        int output[100];
        int n = outdegree(graph, u, output);

        // Cap nhap distance cua tat ca cac dinh ma lien ke voi dinh min
        for (int i = 0; i < n; i++)
        {
            int v = output[i];
            double w = getEdgeValue(graph, u, v);
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            if (visit[v] == 0)
            {
                dll_append(queue, new_jval_i(v));
            }
        }
    }

    // Truy vet lai de lay duong di tuw s ---> t va luu trong path[]
    double distance_s_t = distance[t];
    int count = 0;
    if (distance[t] != INFINITIVE_VALUE)
    {

        path[count++] = t;
        while (t != s)
        {
            t = previous[t];
            path[count++] = t;
        }
        *length = count;
    }
    return distance_s_t;
}
