#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "minheap.h"

Elem_t** heapCreate(int size){

    Elem_t** heap = malloc(sizeof(Elem_t*)*size);

    for(int i = 0; i < size; i++){
        heap[i] = malloc(sizeof(Elem_t));
        heap[i]->priority = -1;
        heap[i]->vertex = -1;
    }

    return heap;
}

char heapEmpty(Elem_t** heap){
    if(heap[0]->vertex == -1 || heap[0]->priority == -1) return 1;
    return 0;
}

Elem_t* heapRemoveMin(Elem_t** heap, int size){

    Elem_t* copy = malloc(sizeof(Elem_t));
    copy->priority = heap[0]->priority;
    copy->vertex = heap[0]->vertex;

    int count = 0;
    for(int i = 1; i < size && (heap[i]->vertex != -1); i++){
        heap[i-1]->vertex = heap[i]->vertex;
        count++;
    }
    heap[count]->vertex = -1;

    return copy;
}

void heapDirectInsert(Elem_t** heap, int size, int vertex, int* dists){
    Elem_t* inserted = malloc(sizeof(Elem_t));
    inserted->priority = dists[vertex];
    inserted->vertex = vertex;

    heapInsert(heap, size, inserted, dists);
}

void heapInsert(Elem_t** heap, int size, Elem_t* inserted, int* dists){

    for(int i = 0; i < size; i++){
        if(heap[i]->vertex == -1){
            free(heap[i]);
            heap[i] = inserted;
            dists[i] = inserted->priority;
            return;
        }

        if(dists[i] > inserted->priority){

            Elem_t* aux = malloc(sizeof(Elem_t));
            aux->priority = inserted->priority;
            aux->vertex = inserted->vertex;

            inserted->priority = dists[i];
            inserted->vertex = heap[i]->vertex;

            dists[i] = aux->priority;
            heap[i]->vertex = aux->vertex;

            dists[i] = inserted->priority;

            free(aux);
            heapInsert(heap, size, inserted, dists);
        }
    }
}

Elem_t** heapDecrease(Elem_t** heap, int vertex, int* dists){

    int pos = 0;
    int i = 0;
    while(pos == 0){
        if(heap[i]->vertex == vertex){
            pos = i;
            break;
        }
        i++;
    }

    int parent = (ceil((float)pos/2.0) - 1.0);
    Elem_t* aux = malloc(sizeof(Elem_t));

    while(parent >= 0 && dists[heap[parent]->vertex] > dists[vertex]){

        aux->vertex = vertex;
        heap[pos]->vertex = heap[parent]->vertex;
        heap[parent]->vertex = aux->vertex;

        pos = parent;
        parent = (ceil((float)pos/2.0) - 1.0);
    }

    free(aux);

    return heap;

}

void heapDestroy(Elem_t** heap, int size){

    for(int i = 0; i < size; i++){
        free(heap[i]);
    }
    free(heap);
}