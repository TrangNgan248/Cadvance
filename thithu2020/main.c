#include <stdio.h>
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void docfile(FILE *f, Graph g)
{ 
    f = fopen("hocphan.txt", "r");
    char ID[10], name[50];
    char hp1[10], hp2[10];
    char c;
    int count = 0;
    while(c != EOF){
        c = fscanf(f, "%s", ID);
        if(strcmp(c, '0000')==0){
            printf("ok");
            break;

        }
        count ++;
    }
    printf("%d", count);
}

int main(){
FILE *f;
    Graph g = createGraph();
    docfile(f, g);
    /*JRB iter;
    jrb_traverse(iter, g.vertices){
        printf("%d %s", jval_i(iter->key), jval_s(iter->val));
    }*/
    int choice;
    /*while (1)
    {
        puts("");
        puts("MENU: ");
        puts("1. In danh sach dinh");
        puts("2. Thoat");
        printf(">>> ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            
            break;
        case 2:
            dropGraph(g);
            return 0;
        default:
            puts("Nhap sai!");
            break;
        }
    }*/
}