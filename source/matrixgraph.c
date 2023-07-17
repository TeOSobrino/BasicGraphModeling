#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "queue.h"
#include "minheap.h"
#include"matrixgraph.h"

#define min(a, b) (a) < (b) ? (a) : (b)

struct graph_{

    Matrix matrix;
    int rows;
    int columns;
    int links;
};

Matrix matrixCreate(int rows, int columns){

    Matrix m = malloc(rows*sizeof(int*));

    for(int i = 0; i < rows; i++){

        m[i] = malloc(columns*sizeof(int));
    }

    for(int i = 0; i < rows; i++){

        for(int j = 0; j < columns; j++){

            m[i][j] = NEUTRAL_ELEMENT;
        }
    }

    return m;
}

Graph_t* graphCreate(int rows, int columns, int links){

    Matrix matrix = matrixCreate(rows, columns);

    Graph_t* graph = malloc(sizeof(Graph_t));

    graph->matrix = matrix;
    graph->rows = rows;
    graph->columns = columns;
    graph->links = links;

    return graph;
}

void graphAdd(Graph_t* graph, int row, int column, int weight){

    graph->matrix[row][column] =  weight;
    graph->matrix[column][row] =  weight;
}

void graphRemove(Graph_t* graph, int row, int column){

    graph->matrix[row][column] =  NEUTRAL_ELEMENT;
    graph->matrix[column][row] =  NEUTRAL_ELEMENT;
}

Graph_t* graphBuild(){

    char file_name[30];
    int checker;
    checker = scanf("%s", file_name);
    if(checker == 0){
        printf("Falha ao ler o nome do arquivo.\n");
        exit(1);
    }

    FILE* file = fopen(file_name, "r");
    if(file == NULL){
        printf("Arquivo inexistente.\n");
        exit(1);
    }

    int vertex_number, link_number;
    checker = fscanf(file, "%d %d", &vertex_number, &link_number);
    if(checker == 0){
        printf("Formato do arquivo diferente do esperado.\n");
        exit(1);
    }
    
    Graph_t* graph = graphCreate(vertex_number, vertex_number, link_number);

    int link1, link2;
    for(int i = 0; i < link_number; i++){

        checker = fscanf(file, "%d %d", &link1, &link2);
        if(checker == 0){
            printf("Não foi possível ler o arquivo.\n");
            exit(1);
        }

        graphAdd(graph, link1, link2, 1);
    }
    fclose(file);

    return graph;
}

void printPath(int* path, int size){

    printf("Sim\n");
    for(int i = 0; i < size; i++){
        printf("%d ", path[i]);
    }
    printf("\n");
}

void graphPrint(Graph_t* graph){

    for(int i = 0; i < graph->rows; i++){
        for(int j = 0; j < graph->columns; j++){

            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }

}

char graphParityCheck(Graph_t* graph){

    int acc;
    for(int i = 0; i < graph->rows; i++){
        
        acc = 0;
        for(int j = 0; j < graph->columns; j++){

            if(graph->matrix[i][j] != NEUTRAL_ELEMENT) acc++;
        }
        if(acc%2 != 0){
            return 0;
        }
    }

    return 1; 
}

char isBridge(Graph_t* graph, int vertex){

    int acc = 0;

    for(int i = 0; i < graph->columns; i++){

        if(graph->matrix[vertex][i] != NEUTRAL_ELEMENT) acc++;
        
        if(acc > 1) return 0;
    }

    return 1;
}

int nextVertex(Graph_t* graph, int vertex){

    int first_vertex = -1;

    for(int i = 0; i < graph->columns; i++){

        if(graph->matrix[vertex][i] != NEUTRAL_ELEMENT){

            if(first_vertex == -1) first_vertex = i; 

            if(!isBridge(graph, i)){

                return i;
            }
        }
    }

    return first_vertex;
}

int* findPathWithFixedBeginning(Graph_t* graph, int beginning){

    int curr_vertex = 0;
    int next_vertex = beginning;
    int* path = malloc((graph->links+1)*sizeof(int));
    path[0] = beginning;

    for(int pathsize = 1; pathsize <= graph->links; pathsize++){
        path[pathsize] = -1;
    }
    
    for(int i = 0; i < graph->links; i++){

        curr_vertex = next_vertex;
        next_vertex = nextVertex(graph, next_vertex);
        
        if(next_vertex == -1 && path[graph->links+1] == -1){
            free(path);
            return NULL;
        }

        path[i+1] = next_vertex;
        graphRemove(graph, curr_vertex, next_vertex);
    }

    return path;
}

int* findEulerianPath(Graph_t* graph){

    int* path = NULL;

    path = findPathWithFixedBeginning(graph, 0);

    return path;
}

void eulerianPath(){

    Graph_t* graph = graphBuild();
    
    if(!graphParityCheck(graph)){
        printf("Não\n");
        
        return NULL;
    }

    int* path = findEulerianPath(graph);

    printPath(path, (graph->links)+1);
    free(path);
    
    graphDestroy(graph);
}

void matrixDestroy(Matrix matrix, int rows){

    for(int i = 0; i < rows; i++){

        free(matrix[i]);
    }

    free(matrix);
}

void graphDestroy(Graph_t* graph){

    matrixDestroy(graph->matrix, graph->rows);

    free(graph);
}