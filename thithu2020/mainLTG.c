#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
//#include"graph_jrb/graph_jrb.h"
#include"graph.h"
#define Max_Char 255
#define Max 100
#define true 1
#define false 0

void readfile_hp(Graph graph, char filename[])
{
  IS is = new_inputstruct(filename);

  if (is == NULL)
  {
    printf("ERROR\n");
    exit(0);
  }

  while (get_line(is) > 0)
  {
    char temp_id[Max_Char], temp_name[Max_Char] = "\0";

    for (int i = 2; i < strlen(is->fields[0]); i++)
    {
      temp_id[i-2] = is->fields[0][i];
    }
    
    for (int i = 1; i < is->NF; i++)
    {
      strcat(temp_name, is->fields[i]);
      strcat(temp_name, " ");
    }
    
    addVertex(graph, atoi(temp_id), temp_name);

    if (strcmp(is->fields[0], "0000") == 0)
    {
      break;
    }
  }

  while (get_line(is) > 0)
  {
    char temp_1[Max_Char], temp_2[Max_Char];

    for (int i = 2; i < strlen(is->fields[0]); i++)
    {
      temp_1[i-2] = is->fields[0][i];
    }

    for (int i = 2; i < strlen(is->fields[1]); i++)
    {
      temp_2[i-2] = is->fields[1][i];
    }

    addEdge(graph, atoi(temp_1), atoi(temp_2), 0, 0);
  }
}

void readfile_pass(Graph graph, char filename[])
{
  IS is = new_inputstruct(filename);

  if (is == NULL)
  {
    printf("ERROR\n");
    exit(0);
  }

  while (get_line(is) > 0)
  {
    char temp_1[Max_Char], temp_2[Max_Char];

    for (int i = 2; i < strlen(is->fields[0]); i++)
    {
      temp_1[i-2] = is->fields[0][i];
    }

    for (int i = 2; i < strlen(is->fields[1]); i++)
    {
      temp_2[i-2] = is->fields[1][i];
    }

    addVertex(graph, atoi(temp_1), is->fields[0]);
    addVertex(graph, atoi(temp_2), is->fields[1]);
  }
}

void check_hp(Graph graph_hp, Graph graph_pass, int check)
{
  JRB node;
  int bool = 0;

  jrb_traverse(node, graph_hp.vertices)
  {
    if (jval_i(node->key) == check)
    {
      bool = true;
      break;
    }
  }

  if (bool == false)
  {
    printf("Khong tim thay ma hoc phan\n");
  } else {
    int bool_2 = 0;

    jrb_traverse(node, graph_pass.vertices)
    {
      if (jval_i(node->key) == check)
      {
        bool_2 = true;
        break;
      }
    }

    if (bool_2 == true)
    {
      printf("Da hoan thanh hoc phan\n");
    } else {
      int output[Max];
      int check_indeg = indegree(graph_hp, check, output);
      int bool_3 = 0;

      jrb_traverse(node, graph_pass.vertices)
      {
        if (jval_i(node->key) == output[0])
        {
          bool_3 = true;
          break;
        }
      }

      if (bool_3 == true)
      {
        printf("Du dieu kien dang ky\n");
      } else printf("Khong du dieu kien dang ky\n");
    }
  }
}

int main()
{

  Graph graph_hp = createGraph(), graph_pass = createGraph();
  int menu, num_page;
  char check[Max_Char];
  readfile_hp(graph_hp, "../hocphan.txt");
  readfile_pass(graph_pass, "../passed.txt");

  printf("Nhap hoc phan can kiem tra: ");
  gets(check);

  char temp[Max_Char];

  for (int i = 2; i < strlen(check); i++)
  {
    temp[i-2] = check[i];
  }

  check_hp(graph_hp, graph_pass, atoi(temp));
  return 0;
}

