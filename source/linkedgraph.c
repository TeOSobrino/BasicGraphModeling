#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "linkedgraph.h"
#include "queue.h"
#include "minheap.h"

#define min(a, b) (a) < (b) ? (a) : (b)

Link_t* nodeCreate(int val){

    Link_t* node = malloc(sizeof(Link_t));
    node->val = val;
    node->color = 0;
    node->weight = 0;
    node->next = NULL;

    return node;
}

Graph_t* graphCreate(int vertex_num){
    
    Graph_t* graph = malloc(sizeof(Graph_t));
    Link_t** adj = malloc(vertex_num*sizeof(Link_t*));
    
    for(int i = 0; i < vertex_num; i++){
        adj[i] = nodeCreate(i);
    }
    graph->list = adj;
    graph->vertex_num = vertex_num;
    graph->link_num = 0;

    return graph;
}

void nodeInsert(Link_t* node, Link_t* next){

    if(node->next == NULL) node->next = next;
}

void nodePositionInsert(Graph_t* graph, int pos, Link_t* inserted){

    Link_t* node = graph->list[pos];
    while(node->next != NULL){
        node = node->next;
    }
    nodeInsert(node, inserted);
}

void undirectedGraphInsert(Graph_t* graph, int pos1, int pos2){
    Link_t* node1 = nodeCreate(pos1);
    Link_t* node2 = nodeCreate(pos2);

    nodePositionInsert(graph, pos1, node2);
    nodePositionInsert(graph, pos2, node1);
}

void undirectedWeightedGraphInsert(Graph_t* graph, int pos1, int pos2, int weight){
    Link_t* node1 = nodeCreate(pos1);
    Link_t* node2 = nodeCreate(pos2);
    node1->weight = weight;
    node2->weight = weight;

    nodePositionInsert(graph, pos1, node2);
    nodePositionInsert(graph, pos2, node1);
}

void directedGraphInsert(Graph_t* graph, int pos1, int pos2){
    
    Link_t* node1 = nodeCreate(pos2);
    nodePositionInsert(graph, pos1, node1);
}

Graph_t* graphInputBuild(){
    int vertex_num; 
    int link_num;

    scanf(" %d", &vertex_num);
    scanf(" %d", &link_num);
    
    Graph_t* graph = graphCreate(vertex_num);

    for(int i = 0; i < link_num; i++){
        int vertex1, vertex2;
        scanf(" %d %d", &vertex1, &vertex2);

        directedGraphInsert(graph, vertex1, vertex2);
    }

    return graph;
}

Graph_t* graphWeightedInputBuild(){
    int vertex_num; 
    int link_num;

    scanf(" %d", &vertex_num);
    scanf(" %d", &link_num);
    
    Graph_t* graph = graphCreate(vertex_num);

    for(int i = 0; i < link_num; i++){
        int vertex1, vertex2, weight;
        scanf(" %d %d %d", &vertex1, &vertex2, &weight);

        undirectedWeightedGraphInsert(graph, vertex1, vertex2, weight);
        
    }

    return graph;
}

Link_t* graphGetNode(Graph_t* g, int vertex1, int vertex2){

    Link_t* aux = g->list[vertex1];

    while(aux != NULL && aux->val != vertex2){
        aux = aux->next;
    }
    return aux;
}

//para marcar como visitado apenas consideramos o nó cabeça
void markAsVisited(Graph_t* graph, int pos){
    graph->list[pos]->color = 1;
}

void unvisitGraph(Graph_t* graph){
    
    int size = graph->vertex_num;
    for(int i = 0; i < size; i++){
        graph->list[i]->color = 0;
    }
}

char wasVisited(Graph_t* graph, int pos){
    if(graph->list[pos]->color == 0) return 0;
    return 1;
}

int* bfs(Graph_t* graph, int vertex){

    int size = graph->vertex_num;
    int* parent_array = malloc(size*sizeof(int));
    for(int i = 0; i < size; i++){
        parent_array[i] = -1;
    }
    Queue_t* queue = queueInit();

    markAsVisited(graph, vertex);
    queueInsertInt(queue, vertex);
    parent_array[vertex] = vertex;
    
    while(queueNotEmpty(queue)){
        
        int vertex_val = queueGetInt(queue);
        for(Link_t* a = graph->list[vertex_val]; a != NULL; a = a->next){
            if(a->color == 0 && parent_array[a->val] == -1){
            
                markAsVisited(graph, a->val);
                queueInsertInt(queue, a->val);
                parent_array[a->val] = vertex_val;
            }
        }
    }
    queueDestroy(queue);

    return parent_array;
}

void graphRemove(Graph_t* graph, int pos1, int pos2){

    Link_t* l1 = graph->list[pos1];
    Link_t* aux = l1->next;
    
    while(aux != NULL && aux->val != pos2){
        aux = aux->next;
        l1 = l1->next;
    }
    if(aux != NULL){
        l1->next = aux->next; //remoção de aux
        free(aux);

    }

    Link_t* l2 = graph->list[pos2];
    aux = l2->next;
    while(aux != NULL && aux->val != pos1){
        aux = aux->next;
        l2 = l2->next;
    }
    if( aux != NULL){    
        l2->next = aux->next;
        free(aux);
    }
}

void listPrint(Link_t* node){
    
    if(node == NULL){
        printf("|-\n");
        return;
    }
    printf("(%d, %d, %d) ->", node->val, node->color, node->weight);
    listPrint(node->next);
}

void graphPrint(Graph_t* graph){

    int vertex_num = graph->vertex_num;
    for(int i = 0; i < vertex_num; i++){
        printf("Graph %d:", i);
        listPrint(graph->list[i]);
    }
    printf("\n");
}

void recursiveGraphDestroy(Link_t* node){

    if(node == NULL){  
        return;
    }
    recursiveGraphDestroy(node->next);
    free(node);
}

void graphDestroy(Graph_t* graph){

    for(int i = 0; i < graph->vertex_num; i++){
        recursiveGraphDestroy(graph->list[i]);
    }
    free(graph->list);
    free(graph);
}

void findStrongCompsRecursive(Graph_t* graph, int curr_vertex, int* id, int* find_time, 
    int* sc_num, int *strong_comps, int* dfs_id, int* lowest_reachable_id, int* stack){
    
    dfs_id[curr_vertex] = (*id);
    *id += 1; //o vértice visitado recebe um id segundo a ordem de visitação da DFS

    stack[(*find_time)] = curr_vertex; //o vértice visitado é adicionado na pilha
    *find_time += 1;
    lowest_reachable_id[curr_vertex] = dfs_id[curr_vertex]; //o menor id acessível, por hora, é o próprio id do vértice
    
    for (Link_t* a = graph->list[curr_vertex]; a != NULL; a = a->next){
        
        int w = a->val;
        if (dfs_id[w] == -1) { //o vértice a é não visitado, iremos visitá-lo e calcular o menor id acessível
            
            findStrongCompsRecursive(graph, w, id, find_time, sc_num, 
                strong_comps, dfs_id, lowest_reachable_id, stack); //calcula lowest_reachable_id[w]
            
            lowest_reachable_id[curr_vertex] = min(lowest_reachable_id[curr_vertex], lowest_reachable_id[w]);
            //o menor id acessível para curr_vertex é o mínimo entre ele e seu(s) filhos na árvore DFS 
        }
        else if (dfs_id[w] < dfs_id[curr_vertex] && strong_comps[w] == -1) { //vértice a já visitado, e presente na pilha
            lowest_reachable_id[curr_vertex] = min(lowest_reachable_id[curr_vertex], dfs_id[w]);
        } 
    }

    if (lowest_reachable_id[curr_vertex] == dfs_id[curr_vertex]) { //curr_vertex é a raiz de uma componente fortemente 
    //conexa e todos seus vértices foram visitados
        int u; 
        int base_vertex = minVertexComp(stack, (*find_time), curr_vertex);
        do{ 
            (*find_time) -= 1;
            u = stack[(*find_time)]; //desempilhamos os vértices
            
            strong_comps[u] =  base_vertex;

        } while (u != curr_vertex); 
        (*sc_num)+=1;
    }
}

int findStrongCompsTarjan(Graph_t* graph, int *strong_comps){

    int* dfs_id = malloc(graph->vertex_num*sizeof(int));
    int* lowest_reachable_id = malloc(graph->vertex_num*sizeof(int));
    int* stack = malloc(graph->vertex_num*sizeof(int));
    int find_time, id, sc_num;

    for (int curr_vertex = 0; curr_vertex < graph->vertex_num; ++curr_vertex){
        dfs_id[curr_vertex] = strong_comps[curr_vertex] = -1;
    }

    find_time = id = sc_num = 0;

    for (int curr_vertex = 0; curr_vertex < graph->vertex_num; ++curr_vertex){
        if (dfs_id[curr_vertex] == -1)
            findStrongCompsRecursive(graph, curr_vertex, &id, &find_time, &sc_num, 
                strong_comps, dfs_id, lowest_reachable_id, stack);
    }

    free(dfs_id);
    free(lowest_reachable_id);
    free(stack);

    return sc_num;
}

int primMST(Graph_t* graph){

    int size = graph->vertex_num;
    int* dists = malloc(sizeof(int)*size);
    bool* mature = malloc(sizeof(bool)*size);

    for (int v = 0; v < size ; ++v){
        dists[v] = INT_MAX;
        mature[v] = false;
    }
   
    dists[0] = 0;
    Elem_t** heap = heapCreate(size);
    for (int v = 0; v < size; ++v){
        heapDirectInsert(heap, size, v, dists);
    }
   
    while(!heapEmpty(heap)){
        
        Elem_t* min = heapRemoveMin(heap, size);
        int curr_vertex = min->vertex;
        if (dists[curr_vertex] == INT_MAX) break;

        //analisamos a lista de adjacências para o vértice removido da heap
        for (Link_t* a = graph->list[curr_vertex]; a != NULL; a = a->next){
            
            if (mature[a->val] || a->weight == 0){
                continue;
            } 
            if(a->weight < dists[a->val]){
                
                dists[a->val] = a->weight;
                heap = heapDecrease(heap, a->val, dists);
            }
        }
        mature[curr_vertex] = true;
        free(min);
    }

    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += dists[i];
    }

    heapDestroy(heap, size);
    free(mature);
    free(dists);
    
    return sum;
}

void dijkstraShortestPath(Graph_t* graph, int start, int *parents, int *dists){

    int size = graph->vertex_num;
    bool mature[size];
    for (int v = 0; v < size ; ++v)
        parents[v] = -1, mature[v] = false, dists[v] = INT_MAX;
   
    parents[start] = start, dists[start] = 0;
    Elem_t** heap = heapCreate(size);
    for (int v = 0; v < size; ++v){
        heapDirectInsert(heap, size, v, dists);
    }
   
    while(!heapEmpty(heap)){
        
        Elem_t* min = heapRemoveMin(heap, size);
        int curr_vertex = min->vertex;
        if (dists[curr_vertex] == INT_MAX) break;

        //analisamos a lista de adjacências para o vértice removido da heap
        for (Link_t* a = graph->list[curr_vertex]; a != NULL; a = a->next){
            //se a lista de adjacências do vértice analisado já foi interiamente analisada
            //esse vértice é maduro, assim vamos para o próximo vértice da lista
            if (mature[a->val]){
                continue;
            }
            //caso a distância até o vértice atual + analisado seja < distância presente no vetor
            //de distâncias lista, atualizamos o pai, a distância e a minheap 
            if (dists[curr_vertex] + a->weight < dists[a->val]){
                dists[a->val] = dists[curr_vertex] + a->weight;
                heapDecrease(heap, a->val, dists);
                parents[a->val] = curr_vertex;
            }
        }
        mature[curr_vertex] = true;
        free(min);
    }

    heapDestroy(heap, size);
}


// funções auxiliares

int minVertexComp(int* arr, int stack_end, int comp_head){

    int min = arr[stack_end-1];

    for(int i = stack_end-1; arr[i] != comp_head; i--){
        if(arr[i] < min) min = arr[i];
    }
    if(comp_head < min) min = comp_head;

    return min;
}

int* scPrintSort(int** strong_comps, int size){

    int* ordered_vertexes = malloc(size*sizeof(int));
    int count_arr[size];
    int* ordered_comps = malloc(size*sizeof(int));

    for(int i = 0; i < size; i++){
        ordered_vertexes[i] = i;
        count_arr[i] = 0;
    }

    for(int i = 0; i < size; i++){

        count_arr[(*strong_comps)[i]] += 1;
    }

    for(int i = 0; i < size-1; i++){

        count_arr[i+1] += count_arr[i];
    }

    for(int i = size-1; i >= 0; i--){

        ordered_comps[(count_arr[(*strong_comps)[i]])-1] = (*strong_comps)[i];
        ordered_vertexes[count_arr[(*strong_comps)[i]]-1] = i;
        count_arr[(*strong_comps)[i]] -= 1;
    }

    free(*strong_comps);
    (*strong_comps) = ordered_comps;
    
    return ordered_vertexes;
}