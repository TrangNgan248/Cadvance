#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);

double shortestPath(Graph graph, int s, int t, int *path, int *length);
void dropGraph(Graph graph);

docfile(FILE *f, Graph g, Graph g1, Graph g2){
    int id1, id2, time, i;
    f = fopen("data.txt", "r");
    fscanf(f, "%d   %d\n", &n, &m);
    //printf("%d %d", n,m);
    for(i =1; i<=m; i++){
        fscanf(f,"%d    %d  %d\n", &id1, &id2, &time);
        if(time<50){
            addVertex(g, id1, "a");
            addVertex(g, id2, "a");
            addVertex(g1, id1, "a");
            addVertex(g1, id2, "a");
            addEdge(g, id1, id2, time);
            addEdge(g, id2, id1, time);
            addEdge(g1, id1, id2, time);
            addEdge(g1, id2, id1, time);
        }
        if(time>=50){
            addVertex(g, id1, "a");
            addVertex(g, id2, "a");
            addVertex(g2, id1, "a");
            addVertex(g2, id2, "a");
            addEdge(g, id1, id2, time);
            addEdge(g, id2, id1, time);
            addEdge(g2, id1, id2, time);
            addEdge(g2, id2, id1, time);
        }
    }
    fclose(f);
}

void inGraph(Graph g, int x){
    for(int i=1; i<=x; i++){
        for(int j=1; j<=x; j++){
            int kc = getEdgeValue(g,i,j);
            if(kc == INFINITIVE_VALUE){
                kc =0;
            }
            printf("%7d", kc);
        }
         printf("\n");
    }
}

void danhSachKe(Graph g, int x){
    for(int i=1; i<=x; i++){
        int output[15];
        int res = outdegree(g, i, output);
        printf("%d: ", i);
        if (res == 0){
            printf("Ko co\n");
        }else{
            for(int j=0; j<res; j++){
                printf("%4d", output[j]);
            }
            printf("\n");
        }
    }
}

void chiDiBo(Graph g, int x){
    for(int i=1; i<=x; i++){
        int output[15];
        int count =0;
        int res = indegree(g, i, output);
        if(res != 0){
            for(int j=0; j<res; j++){
                int kc= getEdgeValue(g, i, output[j]);
                if(kc<50){
                    count++;
                }
                //printf("%d\n", count);
            }
            if(count == 0){
                printf("%d\n", i);
            }
        }
    }
}

void nhieuDuongNhat(Graph g, int x){
    int output[15];
    int a[15];
    int max=0;
    for(int i=1; i<=x; i++){
        a[i] = indegree(g, i, output);
        if(a[i]>=max){
            max = a[i];
        }
    }
    for(int i=1; i<=x; i++){
        a[i] = indegree(g, i, output);
        if(a[i]==max){
            printf("%d ", i);
        }
    }
    printf("\n");
}

void timDuongNganNhat (Graph g, int bd, int kt){
    int path[15];
    int length;
    int kc = shortestPath(g,bd,kt,path,&length);
    if(kc == INFINITIVE_VALUE){
        printf("ROUTE NOT FOUND\n");
    }
    else{
        for(int i=length-1; i>=0; i--){
            printf("%d ", path[i]);
        }
        printf("\n");
    }
}

void timDuongDiBoNganNhat(Graph g2, int bd, int kt){
    int path[15];
    int length;
    int kc = shortestPath(g2,bd,kt,path,&length);
    if(kc==INFINITIVE_VALUE){
        printf("ROUTE NOT FOUND\n");
    }
    else{
        for(int i=length-1; i>=0; i--){
            printf("%d ", path[i]);
        }
        printf("\n");
    }
}

int main(){
    FILE *f;
    Graph g= createGraph();
    Graph g1= createGraph();
    Graph g2= createGraph();
    /*JRB iter;
    jrb_traverse(iter, g.vertices){
        printf("%d %s", jval_i(iter->key), jval_s(iter->val));
    }*/
    int choice;
    docfile (f, g,g1,g2);
    do{
        printf("______MENU______\n");
        printf("1.In ra ma trận kề của đồ thị.\n");
        printf("2. In ra danh sách kề của mỗi thành trì.\n");
        printf("31. Danh sách các thành trì chỉ có thể đi đến nó bằng cách đi bộ.\n");
        printf("32. Danh sách các thành trì có nhiều đường đi nối từ các thành trì khác nhất\n");
        printf("4. Tìm đường đi ngắn nhất.\n");
        printf("5. Tìm đường đi bộ ngắn nhất.\n");
        printf("6. Thoát.\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                {
                inGraph(g,n);
                break;
                }
            case 2:
                { 
                danhSachKe(g, n);
                break;
                }
            case 31:
                { 
                chiDiBo(g, n);
                break;
                }
            case 32:
                {
                nhieuDuongNhat(g,n);
                break;
                }
            case 4:
                {
                int s, t;
                printf("Nhap điểm bắt đầu : ");
                scanf("%d", &s);
                __fpurge(stdin);
                printf("Nhap điểm kết thúc : ");
                scanf("%d", &t);
                __fpurge(stdin);
                timDuongNganNhat(g, s, t); 
                break;
                }
            case 5:
                {
                int s, t;
                printf("Nhap điểm bắt đầu : ");
                scanf("%d", &s);
                __fpurge(stdin);
                printf("Nhap điểm kết thúc : ");
                scanf("%d", &t);
                __fpurge(stdin);
                timDuongDiBoNganNhat(g2,s,t);   
                break;
                }
            case 6:
                {
                    dropGraph(g);
                    dropGraph(g1);
                    dropGraph(g2);
                    break;
                }
            default:
                printf("Nhap sai!");
                break;
        }
    }while(choice!=6);
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
