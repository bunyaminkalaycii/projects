#include "failure_stack.h"

void initialize_failed_stack(FAILURE_STACK *fs){
    fs->top = -1;
}

bool isFull(FAILURE_STACK *fs){
    return fs->top == MAX_FAILED - 1;
}

bool isEmpty(FAILURE_STACK *fs){
    return fs->top == -1;
}

void push(FAILURE_STACK *fs, PROCESS_QUEUE data){
    if (!isFull(fs)){
        fs->stack[++fs->top] = data;
    }
}

PROCESS_QUEUE pop(FAILURE_STACK *fs){
    if (!isEmpty(fs))
    {
        fs->top--;
        return fs->stack[fs->top+1];
    }else{
        PROCESS_QUEUE emptyQueue;
        emptyQueue.front = -99;
        emptyQueue.rear = -99;
        emptyQueue.size = -99;
        emptyQueue.priority = -99;
        emptyQueue.iteration = -99;

        for (int i = 0; i < QUEUE_SIZE; i++)
        {
            emptyQueue.queue[i].priority = -99;
            emptyQueue.queue[i].pid = -99;
        }

        return emptyQueue;
    }
}