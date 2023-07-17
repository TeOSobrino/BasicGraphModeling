#ifndef MATRIX_H
#define MATRIX_H

#define NEUTRAL_ELEMENT 0 //elemento neutro para o peso do grafo

typedef int** Matrix;
typedef struct graph_ Graph_t;

/**
 * @brief cria uma matriz
 * 
 * @param rows linhas da matriz
 * @param columns colunas da matriz
 */
Matrix matrixCreate(int rows, int columns);

/**
 * @brief cria um grafo que é representado por uma matriz
 * e contém o número de linhas e colunas (vértices) e links (arestas)
 * 
 * @param rows linhas da matriz (vértices)
 * @param columns colunas da matriz (vértices)
 * @param links arestas do grafo
 */
Graph_t* graphCreate(int rows, int columns, int links);

/**
 * @brief adiciona uma aresta no grafo.
 * 
 * @param graph grafo sendo incrementado
 * @param row vértice sendo conectado
 * @param column outro vértice sendo conectado
 * @param weigh peso da aresta
 */
void graphAdd(Graph_t* graph, int row, int column, int weigh);

/**
 * @brief remove uma aresta do grafo
 * 
 * @param graph grafo cuja aresta esta sendo removida
 * @param row vértice da aresta
 * @param column outro vértice da aresta
 */
void graphRemove(Graph_t* graph, int row, int column);

/**
 * @brief constrói o grafo abrindo um arquivo e ge
 * 
 * @return Graph_t* 
 */
Graph_t* graphBuild();

void graphPrint(Graph_t* graph);

char graphParityCheck(Graph_t* graph);
char isBridge(Graph_t* graph, int vertex);
int nextVertex(Graph_t* graph, int vertex);

int* findPathWithFixedBeginning(Graph_t* graph, int beginning);
int* findEulerianPath(Graph_t* graph);
void eulerianPath();

void graphDestroy(Graph_t* graph);

#endif // !MATRIX_H