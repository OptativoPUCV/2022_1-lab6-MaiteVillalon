#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){  

  

  //filas
  for ( int i = 0 ; i < 9 ; i++)
    {
      int arr[10] = {0}; 
      for (int j = 0 ; j < 9 ; j ++ )
        {
          int d = n->sudo[i][j];
          if (d != 0)
          {
            if (arr[d] == 0)
            {
              arr[d] = 1;
              
            }
            else return 0;
          }
        }
    }

  //columnas
    for ( int i = 0 ; i < 9 ; i++)
    {
      int arr[10] = {0}; 
      for (int j = 0 ; j < 9 ; j ++ )
        {
          int d = n->sudo[j][i];
          if (d != 0)
          {
            if (arr[d] == 0)
            {
              arr[d] = 1;
            }
            else return 0;
          }
        }
    }

  //submatrices 

  for (int k = 0 ; k < 3 ; k++)
  {
    int arr[10] = {0};
    for(int p=0;p<9;p++)
    {
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      //printf("%d ",n->sudo[i][j]);
      //if(p%3 == 2) printf("\n");

      int d = n->sudo[j][i];
      if (d != 0)
      {
        if (arr[d] == 0)
        {
          arr[d] = 1;
        }
        else return 0;
      }
    }
  }

  
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i,j;
   for(i=0;i<9;i++)
  {
  int numero = 1;
   for(j=0;j<9;j++)
   {
      if(n->sudo[i][j] == 0)
      {
        for(numero = 1 ; numero < 10 ; numero++)
        {
          n->sudo[i][j] = numero;
          if(is_valid(n))
          {
            Node *adj_n = copy(n);
            pushBack(list, adj_n);
          }
        }
        n->sudo[i][j] = 0;
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n)
{  
  for (int i = 0 ; i < 9 ; i++)
    {
      for (int j = 0; j < 9 ; j++)
        {
          int d = n->sudo[i][j];
          if (d == 0 ) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* S=createStack();
  *cont = 1;
  push(S,initial);
  
  while ((get_size(S)) != 0)
  {
    Node* n = top(S);
    pop(S);
    *cont = *cont - 1;

    
     //visitar nodo
    if (is_final(n) == 1) return n;
    
    List* adj=get_adj_nodes(n);
    Node * aux= first(adj);
    while(aux)
    {
      push(S,aux);
      aux=next(adj);
      *cont = *cont+1;
    }
    free (n);
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/