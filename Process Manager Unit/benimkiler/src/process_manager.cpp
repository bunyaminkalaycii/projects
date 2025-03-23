#include "process_manager.h"

void initialize_process_manager(PROCESS_MANAGER *pm){
    pm->front = 0;
    pm->rear = -1;
    pm->size = 0;
}

bool isFull(PROCESS_MANAGER *pm){
    return pm->size == MAX_PROCESS;
}

bool isEmpty(PROCESS_MANAGER *pm){
    return pm->size == 0;
}

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){ //High priority ekleme
    if(!isFull(pm)){
        pm->front = (pm->front -1 + MAX_PROCESS) % MAX_PROCESS;
        pm->deque[pm->front] = pq;
        pm->size++;
    }
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq){
    if(!isFull(pm)){
        pm->rear = (pm->rear + 1) % MAX_PROCESS;
        pm->deque[pm->rear] = pq;
        pm->size++;
    }
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm){
    if(!isEmpty(pm)){
        PROCESS_QUEUE data = pm->deque[pm->front];
        pm->front = (pm->front + 1) % MAX_PROCESS;
        pm->size--;
        return data;
    }
    else {
        PROCESS_QUEUE emptyQueue;
        initialize_process_queue(&emptyQueue);
        return emptyQueue;
    }
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm){
    if(!isEmpty(pm)){
        PROCESS_QUEUE data = pm->deque[pm->rear];
        pm->rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
        pm->size--;
        return data;
    }
    else {
        PROCESS_QUEUE emptyQueue;
        initialize_process_queue(&emptyQueue);
        return emptyQueue;
    }
}