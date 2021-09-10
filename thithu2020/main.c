#include <stdio.h>
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int p = 0, pass[10];

void docfile(FILE *f, FILE *f1, Graph g)
{
    f = fopen("hocphan.txt", "r");
    char ID[10], name[50], fullname[50];
    char hp1[10], hp2[10], hp[10];
    char a[] = "0000";
    int count = 0, c, id1, id2;
    while (c != EOF)
    {
        c = fscanf(f, "%s", ID);
        if (strcmp(ID, a) == 0)
        {
            break;
        }
        fgets(name, 100, f);
        count++;
        //printf("%s %s\n", ID, name);
        addVertex(g, count, ID);
    }
    //printf("%d", count);

    JRB iter;
    for (;;)
    {
        c = fscanf(f, "%s %s\n", hp1, hp2);
        if (c == EOF)
        {
            break;
        }
        //printf("%s %s\n", hp1, hp2);

        jrb_traverse(iter, g.vertices)
        {
            if (strcmp(jval_s(iter->val), hp1) == 0)
            {
                id1 = jval_i(iter->key);
            }
        }
        jrb_traverse(iter, g.vertices)
        {
            if (strcmp(jval_s(iter->val), hp2) == 0)
            {
                id2 = jval_i(iter->key);
            }
        }
        //printf("%d %d\n", id1, id2);
        addEdge(g, id1, id2, 1);
    }
    fclose(f);

    f1 = fopen("passed.txt", "r");
    for (;;)
    {
        c = fscanf(f, "%s", hp);
        if (c == EOF)
        {
            break;
        }
        jrb_traverse(iter, g.vertices)
        {
            if (strcmp(jval_s(iter->val), hp) == 0)
            {
                id1 = jval_i(iter->key);
            }
        }
        pass[p] = id1;
        p++;
    }
}

void inDSHocPhan(Graph g)
{
    JRB iter;
    jrb_traverse(iter, g.vertices)
    {
        printf("%d %s\n", jval_i(iter->key), jval_s(iter->val));
    }
}

int main()
{
    FILE *f, *f1;
    Graph g = createGraph();
    docfile(f, f1, g);
    char hocphan[10];
    int id;

    int choice;
    while (1)
    {
        puts("");
        puts("MENU: ");
        puts("1. Dang ki hoc phan");
        puts("2. Thoat");
        printf(">>> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inDSHocPhan(g);
            printf("Nhap hoc phan muon dang ki: ");
            //fgets(hocphan, 100, stdin);
            scanf("%s", hocphan);

            JRB iter;
            int tontai = 0, dangki = 0;
            jrb_traverse(iter, g.vertices)
            {
                if (strcmp(jval_s(iter->val), hocphan) == 0)
                {
                    id = jval_i(iter->key);
                    tontai = 1;
                }
            }
            if (tontai == 0)
            {
                printf("Không tồn tại mã học phần này!");
            }
            else
            {
                for (int i = 0; i < p; i++)
                {
                    if (id == pass[i])
                    {
                        printf("Đã hoàn thành học phần");
                        break;
                    }
                    if(id != pass[i])
                    {
                        int output[10];
                        int res = indegree(g, id, output);
                        if(res ==0){
                            printf("Đủ điềù kiện đăng ký học phần");
                        }
                        else{
                        for (int j = 0; j < res; j++)
                        {
                            if (pass[i] != output[j])
                            {
                                dangki++;
                            }
                        }
                        }
                    }
                }
                if (dangki == 0)
                {
                    printf("Đủ điều kiện đăng kí");
                }
                else if(dangki == -1)
                {
                    printf("Học phần đã hoàn thành");
                }else {
                    printf("Không đăng ký được");
                }
            }
            break;
        case 2:
            dropGraph(g);
            return 0;
        default:
            puts("Nhap sai!");
            break;
        }
    }
}