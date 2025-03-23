#include "process_queue.h"

void initialize_process_queue(PROCESS_QUEUE *pq){
    pq->front = 0;
    pq->rear = -1;
    pq->size = 0;
    pq->priority = 0;
    pq->iteration = 0;
    for (int i = 0; i < QUEUE_SIZE; i++) {
        pq->queue[i].pid = 0;
        pq->queue[i].priority = 0;
    }
}

bool isFull(PROCESS_QUEUE *pq){
    return pq->size == QUEUE_SIZE;
}

bool isEmpty(PROCESS_QUEUE *pq){
    return pq->size == 0;
}

PROCESS peek(PROCESS_QUEUE *pq){
    if(!isEmpty(pq)){
        return pq->queue[pq->front];
    }
    else{
        PROCESS emptyProcess = {0, 0};
        return emptyProcess;
    }
}

void enqueue(PROCESS_QUEUE *pq, PROCESS data){
    if(!isFull(pq)){
        pq->rear = (pq->rear + 1) % QUEUE_SIZE;
        pq->queue[pq->rear] = data;
        pq->size++;
    }
}

PROCESS dequeue(PROCESS_QUEUE *pq){
    if(!isEmpty(pq)){
        PROCESS data = pq->queue[pq->front];
        pq->front = (pq->front + 1) % QUEUE_SIZE;
        pq->size--;
        return data;
    }
    else{
        PROCESS emptyProcess = {0, 0};
        return emptyProcess;
    }
}