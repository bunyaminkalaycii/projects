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

void operate(PROCESS_MANAGER *pm, PROCESS *p, int ishead)
{
    if (p->priority == 1)
    {
        enqueue(&pm->deque[pm->front], *p);
        if (ishead)
        {
            PROCESS_QUEUE newq;
            initialize_process_queue(&newq);
            insert_front(pm, newq);
        }
    }
    else
    {
        enqueue(&pm->deque[pm->rear], *p);
        if (ishead)
        {
            PROCESS_QUEUE newq;
            initialize_process_queue(&newq);
            insert_rear(pm, newq);
        }
    }
}

void op_in(INSERTION_QUEUE *eq, PROCESS *p, int iter, int ishead)
{

    enqueue(&eq->queue[eq->rear], *p);
    eq->queue[eq->rear].priority=p->priority;
    eq->queue[eq->rear].iteration = iter;
    if (ishead)
    {
        PROCESS_QUEUE newq;
        initialize_process_queue(&newq);
        enqueue(eq, newq);
    }
}

void read_process_file(const char *filename, PROCESS_MANAGER *pm)
{
    FILE *fptr = fopen(filename, "r");
    char buff[150] = "";

    fgets(buff, 150, fptr);
    int pid = 0;
    int pri = 0;
    int head = 1;

    PROCESS_QUEUE newq;
    initialize_process_queue(&newq);
    insert_front(pm, newq);

    PROCESS_QUEUE newwq;
    initialize_process_queue(&newwq);
    insert_rear(pm, newwq);

    while (fgets(buff, 50, fptr) != NULL)
    {
        sscanf(buff, "%d,%d,%d", &pid, &pri, &head);
        PROCESS newp;
        initialize_process(&newp, pid, pri);
        operate(pm, &newp, head);
    }
    pm->front+=1;
    pm->rear-=1;

    fclose(fptr);
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq)
{
    FILE *fptr = fopen(filename, "r");

    char buff[150] = "";
    fgets(buff, 150, fptr);
    int iter = 0;
    int pid = 0;
    int pri = 0;
    int head = 1;

    PROCESS_QUEUE newq;
    initialize_process_queue(&newq);
    enqueue(eq, newq);

    while (fgets(buff, 50, fptr) != NULL)
    {
        sscanf(buff, "%d,%d,%d,%d", &iter, &pid, &pri, &head);
        PROCESS newp;
        initialize_process(&newp, pid, pri);
        op_in(eq, &newp, iter, head);
    }
    eq->rear=eq->rear-1;

    fclose(fptr);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs)
{
    FILE *fptr = fopen("execution_run.txt", "w");
    

    /*
    151, s
    150, s
    131, s
    132, s
    130, s
    211, s
    212, s
    210, s
    120, f
    140, s
    168, f
    200, f
    220, s
    */
    int iter = 0;
    PROCESS_QUEUE tobe;
    initialize_process_queue(&tobe);

    while (true)
    {
        if (isEmpty(pm) && isEmpty(eq)) break;

        if (isEmpty(&tobe)){
            tobe = delete_front(pm);
        }
        PROCESS sil=dequeue(&tobe);
        if(sil.pid%8!=0)fprintf(fptr,"%d, s\n",sil.pid);
        else{
            fprintf(fptr,"%d, f\n",sil.pid);
            tobe.front-=1;
            tobe.size++;
            push(fs,tobe);

            while(!isEmpty(&tobe)){
                dequeue(&tobe);
            }
        }
        if(eq->queue[eq->front].iteration==iter){
            PROCESS_QUEUE newq= dequeue(eq);
            if(newq.priority==1){
                insert_front(pm,newq);
            }else {
                insert_rear(pm,newq);
            }
        }

        iter++;
    }
    fclose(fptr);
}

