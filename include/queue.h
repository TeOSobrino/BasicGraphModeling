#ifndef QUEUE_H
#define QUEUE_H

typedef struct node_t QNode_t;
typedef struct queue_t Queue_t;

//cria uma fila
Queue_t* queueInit();
//cria um nó de fila
QNode_t* qNodeCreate(int node_value);
//retira o primeiro nó da fila
QNode_t* queuePop(Queue_t* queue);
//insere um nó no fim da fila
void queuePush(Queue_t* queue, QNode_t* node);
//da pop e retorna o inteiro presente no nó da fila
int queueGetInt(Queue_t* queue);
//insere um nó na fila a partir de seu valor inteiro
void queueInsertInt(Queue_t* queue, int node_val);
//verifica se a fila está vazia
int queueNotEmpty(Queue_t* queue);

//imprime a fila
void queuePrint(Queue_t* queue);

//destroi um nó de fila
void nodeDestroy(QNode_t* node);
//destroi a fila
void queueDestroy(Queue_t* queue);

#endif // !QUEUE_H