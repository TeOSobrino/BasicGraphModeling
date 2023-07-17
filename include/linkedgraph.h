#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "minheap.h"

typedef struct graph_ Graph_t;
typedef struct link Link_t;

struct graph_{
    
    int vertex_num;
    int link_num;
    Link_t** list;
};

struct link{
    
    int val;
    int weight;
    char color;
    Link_t* next;
};


//cria um vértice
Link_t* nodeCreate(int val);

//cria um grafo
Graph_t* graphCreate(int vertex_num);
//cria e constrói um grafo a partir do stdin
Graph_t* graphInputBuild();

Graph_t* graphWeightedInputBuild();

Link_t* graphGetNode(Graph_t* g, int vertex1, int vertex2);

//insere um vértice na lista ligada
void nodeInsert(Link_t* node, Link_t* next);
//insere um vertice no grafo
void nodePositionInsert(Graph_t* graph, int pos, Link_t* inserted);
//insere um vértice a partir de um int num grafo não-orientado
void undirectedGraphInsert(Graph_t* graph, int pos1, int pos2);

void undirectedWeightedGraphInsert(Graph_t* graph, int pos1, int pos2, int weight);

//insere um vértice a partir de um int num grafo orientado
void directedGraphInsert(Graph_t* graph, int pos1, int pos2);

//marca um vértice como visitado
void markAsVisited(Graph_t* graph, int pos);
//marca o grafo todo como não visitado
void unvisitGraph(Graph_t* graph);

//realiza busca em largura
int* bfs(Graph_t* graph, int vertex);

//remove uma aresta do grafo
void graphRemove(Graph_t* graph, int pos1, int pos2);

//verifica se um vértice já foi visitado
char wasVisited(Graph_t* graph, int pos);

//imprime uma lista ligada
void listPrint(Link_t* node);

//imprime um grafo 
void graphPrint(Graph_t* graph);

//descaloca a memória usada pelo grafo
void graphDestroy(Graph_t* graph);

/**
 * @brief recursão para encontrar o número de componentes conexas num grafo usando
 * Tarjan, que por meio de uma DFS dá um identificador (int) para cada vértice
 * e determina qual o menor identificador atingível para cada vértice e com o uso
 * de uma pilha, que valida a presença daquele vértice na componente conexa (se
 * o vértice foi visitado na mesma recursão, ou se houve uma parada e reinício da
 * busca em profundidade, que implica que os vértices não são fortemente conectados).
 * 
 * @param graph grafo sendo analisado
 * @param curr_vertex vértice atual sendo visitado pela DFS
 * @param id identificador dado ao vértice pela DFS
 * @param find_time tempo de descoberta (número de chamadas recursivas)
 * @param sc_num número total de componenetes conexas do grafo
 * @param strong_comps vetor de componentes conexas
 * @param dfs_id vetor de identificadores da DFS para um vértice i
 * @param lowest_reachable_id vetor de menores id acessíveis para um vértice i
 * @param stack vetor de pilha, para validar a presença de um vértice naquela recursão
 */
void findStrongCompsRecursive(Graph_t* graph, int curr_vertex, int* id, int* find_time, 
    int* sc_num, int *strong_comps, int* dfs_id, int* lowest_reachable_id, int* stack);

/**
 * @brief encontra o número de componenetes conexas num grafo, por meio do algoritmo
 * de Tarjan.
 * 
 * @param graph grafo sendo analisado
 * @param strong_comps vetor de componenetes conexas
 * @return número de componenetes conexas
 */
int findStrongCompsTarjan(Graph_t* graph, int *strong_comps);

/**
 * @brief Algoritmo de Prim para encontrar a MST de um grafo conexo
 * 
 * @param graph grafo tendo a árvore gerada
 * @return soma dos pesos da árvore
 */
int primMST(Graph_t* graph);

/**
 * @brief calcula a menor distância entre um vértice e os outros no grafo
 * também gerando um vetor que armazena os pais de cada vértice 
 * 
 * @param graph grafo sendo analisado  
 * @param start vértice inicial (a partir do qual são medidas as distâncias)
 * @param parents vetor de pais de cada vértice (a partir de qual vértice 
 * segue o caminho mais curto)
 * @param dists armazena a distância entre o vértice inicial e o vértice dists[i]
 * @return vetor de distâncias
 */
void dijkstraShortestPath(Graph_t* graph, int start, int *parents, int *dists);

// funções auxiliares:

/**
 * @brief encontra o menor vértice na componente fortemente conexa para 
 * que a impressão dos vértices ocorra da forma especificada
 * 
 * @param arr pilha dos vértices 
 * @param stack_end tamanho da pilha
 * @param comp_head cabeça da componente
 * @return menor vértice pertencente a componenete
 */
int minVertexComp(int* arr, int stack_end, int comp_head);

/**
 * @brief função que ordena em O(V) usando counting sort as componentes 
 * fortemente conexas do grafos, para a impressão ocorrer como especificado.
 * O algoritmo de Tarjan garante que as componenetes serão encontradas em O(v),
 * assim não faz sentido ordenar com uma complexidade superior a esta, pois o
 * gargalo de execução não seria a parte "lógica" do programa.
 * 
 * Como o grafo tem V vértices, sabemos que o maior inteiro possível é V-1, 
 * assim o counting sort pode ser feito de forma simples com seu limite superior
 * 
 * @param strong_comps vetor das componentes conexas com cada elemento v[i]
 * sendo o menor vértice da componente que o vértice i faz parte, será ordenado
 * por esta função também
 * 
 * @param size tamanho do vetor 
 * @return 
 */
int* scPrintSort(int** strong_comps, int size);

#endif // !GRAPH_H