#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <string.h>

#include "execution_functions.h"
#include "failure_stack.h"
#include "insertion_queue.h"
#include "process_manager.h"
#include "process_queue.h"
#include "type_process.h"

#define MAX_OPERATION 10
#define QUEUE_SIZE 5
// typedef struct {
//     PROCESS_QUEUE queue[MAX_OPERATION];
//     int front;
//     int rear;
//     int size;
// } INSERTION_QUEUE;

void initialize_execution_queue(INSERTION_QUEUE *iq){

    iq->front = 0;
    iq->rear = -1;// _ _ _ 3 4 _ _ _
    iq->size = -1;
}

bool isFull(INSERTION_QUEUE *iq){
    if(iq->size==MAX_OPERATION)return 1;
    return 0;
}

bool isEmpty(INSERTION_QUEUE *iq){
    if(iq->size==0||iq->size==-1)return 1;
    return 0;
}

PROCESS_QUEUE peek(INSERTION_QUEUE *iq){
    return iq->queue[iq->front];
}

void enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data){
    if (iq->size < MAX_OPERATION)
    {
        iq->rear = (iq->rear + 1) % MAX_OPERATION;
        iq->queue[iq->rear] = data;
        iq->size++;
    }

}

PROCESS_QUEUE dequeue(INSERTION_QUEUE *iq){
    if (iq->size > 0)
    {
        PROCESS_QUEUE tmp = iq->queue[iq->front];
        iq->front = (iq->front + 1) % MAX_OPERATION;
        iq->size--;
        return tmp;
    }else{
        PROCESS_QUEUE errorProcessQ;
        errorProcessQ.front = -1;
        errorProcessQ.rear = -1;
        errorProcessQ.size = -1;
        errorProcessQ.priority = -1;
        errorProcessQ.iteration = -1;

        for (int i = 0; i < QUEUE_SIZE; i++)
        {
            errorProcessQ.queue[i].pid = -1;
            errorProcessQ.queue[i].priority = -1;
        }

        return errorProcessQ;
    }
}
