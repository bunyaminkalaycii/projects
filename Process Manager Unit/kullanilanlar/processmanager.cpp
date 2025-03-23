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
#define MAX_PROCESS 50
/*    PROCESS_QUEUE deque[MAX_PROCESS];
    int front;
    int rear;
    int size;    */
void initialize_process_manager(PROCESS_MANAGER *pm)
{
    
    pm->front = 3;
    pm->rear = 2;// _ _ _ 3 4 _ _ _
    pm->size = -2;
};

bool isFull(PROCESS_MANAGER *pm){
    if(pm->size==MAX_PROCESS)return 1;
    return 0;
};

bool isEmpty(PROCESS_MANAGER *pm){
    if(pm->size==0||pm->size==-2)return 1;
    return 0;
};

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq)
{
    if (pm->size != MAX_PROCESS)
    {
        pm->front = (pm->front + MAX_PROCESS -1) % MAX_PROCESS;
        pm->deque[pm->front] = pq;
        pm->size++;
    }
};

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if (pm->size != MAX_PROCESS)
    {
        pm->rear = (pm->rear + 1) % MAX_PROCESS;
        pm->deque[pm->rear] = pq;
        pm->size++;
    }
};

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm){
    if (pm->size != 0)
    {
        pm->front = (pm->front + 1) % MAX_PROCESS;
        pm->size--;
        return pm->deque[pm->front-1];
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
};

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm){
    if (pm->size != 0)
    {
        pm->rear = (pm->rear + MAX_PROCESS - 1) % MAX_PROCESS;
        pm->size--;
        return pm->deque[pm->rear+1];
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
};