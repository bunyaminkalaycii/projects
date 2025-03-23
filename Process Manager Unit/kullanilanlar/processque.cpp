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

#define QUEUE_SIZE 5

void initialize_process(PROCESS *p, int pid, int priority)
{
    int mypid=pid;
    int mypri=priority;
    p->pid = mypid;
    p->priority = mypri;
};

void initialize_process_queue(PROCESS_QUEUE *pq)
{
    pq->front = 0;
    pq->rear = -1;
    pq->size = 0;
    pq->priority = 0;
    pq->iteration = 0;
};

void enqueue(PROCESS_QUEUE *pq, PROCESS data)
{
    if (pq->size < QUEUE_SIZE)
    {
        pq->rear = (pq->rear + 1) % QUEUE_SIZE;
        pq->queue[pq->rear] = data;
        pq->size++;
    }
};

PROCESS dequeue(PROCESS_QUEUE *pq)
{
    if (pq->size > 0)
    {
        PROCESS tmp = pq->queue[pq->front];
        pq->front = (pq->front + 1) % QUEUE_SIZE;
        pq->size--;
        return tmp;
    }else{
        PROCESS errorProcess;
        errorProcess.pid = -1;
        errorProcess.priority = -1;
        return errorProcess;
    }
};

bool isFull(PROCESS_QUEUE *pq) {
    if(pq->size==QUEUE_SIZE)return 1;
    return 0;
};

bool isEmpty(PROCESS_QUEUE *pq){
    if(pq->size==0)return 1;
    return 0;
};

PROCESS peek(PROCESS_QUEUE *pq){
    return pq->queue[pq->front];
};
