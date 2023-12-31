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
  int i,j,num;
  for(i=0;i<9;i++){
    int arregloFila[10] = {0};
    for(j=0;j<9;j++){
      num= n->sudo[i][j];
      if(num != 0){
        if(arregloFila[num]==1){
          return 0;
        }else{
          arregloFila[num]= 1;
        }
      }
    }
  }

  for(j=0;j<9;j++){
    int arregloCol[10]={0};
    for(i=0;i<9;i++){
      num= n->sudo[i][j];
      if(num != 0){
        if(arregloCol[num] == 1){
          return 0;
        }else{
          arregloCol[num]= 1;
        }
      }
    }
  }
  
  for(int k = 0; k<9; k++){
    int subMatriz[10] = {0};
    for(int p=0;p<9;p++){
      int a=3*(k/3) + (p/3) ;
      int b=3*(k%3) + (p%3) ;
      num = n->sudo[a][b];
      if(num != 0){
        if(subMatriz[num] == 1){
          return 0;
        }else{
          subMatriz[num] = 1;
        }
      }
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){
  List* list=createList();
  for(int i=0; i<9;i++){
    for(int j=0; j<9;j++){
      if(n->sudo[i][j]==0){
        for(int k=1;k<=9;k++){
          Node* copialist= copy(n);
          copialist->sudo[i][j]=k;
          if(is_valid(copialist)){
            pushBack(list,copialist);
          }
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int i=0; i<9;i++){
    for(int j=0; j<9;j++){
      if(n->sudo[i][j] == 0){
          return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  List* stack= createList();
  pushFront(stack,initial);

  while(is_empty(stack) == 0){
    Node* actual = front(stack);
    popFront(stack);
    (*cont)++;
    if(is_final(actual)){
      clean(stack);
      return actual;
    }
    List* adj_nodes = get_adj_nodes(actual);
    Node* copia;
    while((copia = front(adj_nodes)) != NULL){
      popFront(adj_nodes);
      pushFront(stack,copia);
    }
    free(actual);
    clean(adj_nodes);
    free(adj_nodes);
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