#ifndef HEAP_H
#define HEAP_H

typedef struct elem_{
    int vertex;
    int priority;
} Elem_t;

/**
 * @brief Cria uma minheap (vetor de elementos)
 * 
 * @param size tamanho da heap
 * @return heap alocada
 */
Elem_t** heapCreate(int size);

/**
 * @brief verifica se a heap está vazia
 * 
 * @param heap 
 * @return 1 caso esteja vazia, 0 c.c. 
 */
char heapEmpty(Elem_t** heap);

/**
 * @brief retira o menor elemento da heap (primeiro elemento)
 * 
 * @param heap heap a ter o valor removido
 * @param size tamanho da heap
 * @return elemento retirado da heap
 */
Elem_t* heapRemoveMin(Elem_t** heap, int size);

/**
 * @brief insere um inteiro na minheap 
 * 
 * @param heap heap sendo modificada
 * @param size tamanho da heap
 * @param vertex inteiro sendo inserido
 * @param dists vetor de prioridades da minheap 
 */
void heapDirectInsert(Elem_t** heap, int size, int vertex, int* dists);

//insere um elemento na heap
void heapInsert(Elem_t** heap, int size, Elem_t* inserted, int* dists);

/**
 * @brief mantém as propriedades da heap após a modificação da prioridade de uma 
 * chave da heap
 * 
 * @param heap min heap
 * @param vertex inteiro na heap cuja prioridade mudou
 * @param dists vetor de prioridades
 */
Elem_t** heapDecrease(Elem_t** heap, int vertex, int* dists);

//desaloca a heap
void heapDestroy(Elem_t** heap, int size);


#endif //!HEAP_H