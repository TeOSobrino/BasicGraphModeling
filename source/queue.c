#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

struct node_t{

    int node;
    QNode_t* next_node;
};

struct queue_t{
    int node_num;
    QNode_t* top;
    QNode_t* bottom;
};

QNode_t* qNodeCreate(int node_value){

    QNode_t* node = malloc(sizeof(QNode_t));

    node->next_node = NULL;
    node->node = node_value;

    return node;
}

Queue_t* queueInit(){
    Queue_t* q = malloc(sizeof(Queue_t));

    q->node_num = 0;
    q->top = NULL;

    return q;
}

QNode_t* queuePop(Queue_t* queue){

    QNode_t* node;
    node = queue->top;

    if(queue->top != NULL){
        queue->top = node->next_node;
        queue->node_num -= 1;
    }

    return node;
}

int queueGetInt(Queue_t* queue){

    QNode_t* node = queuePop(queue);
    int n = node->node;
    free(node);
    
    return n;
}

void queueInsertInt(Queue_t* queue, int node_val){

    QNode_t* node = qNodeCreate(node_val);
    queuePush(queue, node);
}

void queuePush(Queue_t* queue, QNode_t* node){
    
    if(queue->node_num != 0){
        
        queue->bottom->next_node = node;
        queue->bottom = node;
    }

    else{
        queue->top = node;
        queue->bottom = node;
    }

    queue->node_num += 1;
}

int queueNotEmpty(Queue_t* queue){

    return queue->node_num;
}

void queuePrint(Queue_t* queue){
    QNode_t* node = queue->top;

    while(node != NULL){

        printf("%d ", node->node);
        node = node->next_node;
    }

    printf("\n");
}

void queueDestroy(Queue_t* queue){
    QNode_t* node = queuePop(queue);
    
    if(node != NULL){
        nodeDestroy(node);
        queueDestroy(queue);
    }   
    else{
        free(queue);
        return;
    }
}

void nodeDestroy(QNode_t* node){
    free(node);
}