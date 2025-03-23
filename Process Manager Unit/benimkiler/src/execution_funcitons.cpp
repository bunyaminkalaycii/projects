#include <iostream>
#include "execution_functions.h"

void read_process_file(const char *filename, PROCESS_MANAGER *pm)
{
    FILE *filePointer = fopen(filename, "r");
    char buffer[200] = "";

    fgets(buffer, 200, filePointer);
    int processID = 0;
    int priority = 0;
    int isHead = 1;

    PROCESS_QUEUE initialQueue;
    initialize_process_queue(&initialQueue);
    insert_front(pm, initialQueue);

    PROCESS_QUEUE secondaryQueue;
    initialize_process_queue(&secondaryQueue);
    insert_rear(pm, secondaryQueue);

    while (fgets(buffer, 50, filePointer) != NULL)
    {
        sscanf(buffer, "%d,%d,%d", &processID, &priority, &isHead);
        PROCESS task;
        initialize_process(&task, processID, priority);
        if (task.priority == 1)
        {
            enqueue(&pm->deque[pm->front], task);
            if (isHead)
            {
                PROCESS_QUEUE newQueue;
                initialize_process_queue(&newQueue);
                insert_front(pm, newQueue);
            }
        }
        else
        {
            enqueue(&pm->deque[pm->rear], task);
            if (isHead)
            {
                PROCESS_QUEUE newQueue;
                initialize_process_queue(&newQueue);
                insert_rear(pm, newQueue);
            }
        }
    }
    pm->front++;
    pm->rear--;

    fclose(filePointer);
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq)
{
    FILE *filePointer = fopen(filename, "r");

    char buffer[200] = "";
    fgets(buffer, 200, filePointer);
    int iteration = 0;
    int processID = 0;
    int priority = 0;
    int isHead = 1;

    PROCESS_QUEUE placeholderQueue;
    initialize_process_queue(&placeholderQueue);
    enqueue(eq, placeholderQueue);

    while (fgets(buffer, 50, filePointer) != NULL)
    {
        sscanf(buffer, "%d,%d,%d,%d", &iteration, &processID, &priority, &isHead);
        PROCESS task;
        initialize_process(&task, processID, priority);
        enqueue(&eq->queue[eq->rear], task);
        eq->queue[eq->rear].priority = task.priority;
        eq->queue[eq->rear].iteration = iteration;
        if (isHead)
        {
            PROCESS_QUEUE newQueue;
            initialize_process_queue(&newQueue);
            enqueue(eq, newQueue);
        }
    }
    eq->rear--;

    fclose(filePointer);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs)
{
    pm->size--; // To erase dummy queue (header) which made it easy to add front or end of Process Manager.
    pm->size--; // To erase dummy queue (tailer) which made it easy to add front or end of Process Manager.
    eq->size--; // To erase dummy queue (header) which made it easy to take from Insertion Queue.
    FILE *outputFile = fopen("execution_run.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error: Could not open execution_run.txt\n");
        return;
    }

    int iteration = 0;
    PROCESS_QUEUE currentQueue;
    initialize_process_queue(&currentQueue);
    while (!isEmpty(pm) || !isEmpty(eq) || !isEmpty(&currentQueue))
    {

        printf("Iteration %d\n", iteration);
        printf("PM Size: %d, Front: %d, Rear: %d\n", pm->size, pm->front, pm->rear);
        printf("EQ Size: %d, Front: %d, Rear: %d\n", eq->size, eq->front, eq->rear);
        printf("Current Queue Size: %d, Front: %d, Rear: %d\n", currentQueue.size, currentQueue.front, currentQueue.rear);

        if (isEmpty(&currentQueue))
        {
            if (!isEmpty(pm))
            {
                currentQueue = delete_front(pm);
                printf("Dequeued queue size: %d\n", currentQueue.size);
            }
            else
            {
                initialize_process_queue(&currentQueue);
            }
        }

        if (!isEmpty(&currentQueue))
        {
            PROCESS activeProcess = dequeue(&currentQueue);
            printf("Processing PID: %d\n", activeProcess.pid);

            if (activeProcess.pid % 8 != 0)
            {
                fprintf(outputFile, "%d, s\n", activeProcess.pid);
                printf("PID %d succeeded.\n", activeProcess.pid);
            }
            else
            {
                fprintf(outputFile, "%d, f\n", activeProcess.pid);
                printf("PID %d failed.\n", activeProcess.pid);

                
                if (!isEmpty(&currentQueue))
                {
                    push(fs, currentQueue);
                    initialize_process_queue(&currentQueue);
                }
            }
        }

        
        if (!isEmpty(eq) && eq->queue[eq->front].iteration == iteration)
        {
            printf("Dequeuing from EQ...\n");
            PROCESS_QUEUE arrivingQueue = dequeue(eq);
            printf("Dequeued queue priority: %d\n", arrivingQueue.priority);

            if (arrivingQueue.priority == 1)
            {
                insert_front(pm, arrivingQueue);
            }
            else
            {
                insert_rear(pm, arrivingQueue);
            }
        }

        iteration++;
    }

    fclose(outputFile);
    printf("Execution complete. Results written to execution_run.txt\n");
}
