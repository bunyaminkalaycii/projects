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
#define MAX_FAILED 10

// typedef struct {
//     PROCESS_QUEUE stack[MAX_FAILED];
//     int top;
// } FAILURE_STACK;

void initialize_failed_stack(FAILURE_STACK *fs)
{
    fs->top = -1;
}

bool isFull(FAILURE_STACK *fs)
{
    if (fs->top == MAX_FAILED - 1)
        return 1;
    return 0;
}

bool isEmpty(FAILURE_STACK *fs)
{
    if (fs->top == -1)
        return 1;
    return 0;
}

void push(FAILURE_STACK *fs, PROCESS_QUEUE data)
{
    if (!isFull(fs))
    {
        fs->top++;
        fs->stack[fs->top] = data;
    }
}

PROCESS_QUEUE pop(FAILURE_STACK *fs)
{
    if (!isEmpty(fs))
    {
        fs->top--;
        return fs->stack[fs->top+1];
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
