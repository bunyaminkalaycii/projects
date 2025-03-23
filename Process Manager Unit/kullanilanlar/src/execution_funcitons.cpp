#include <iostream>
#include "execution_functions.h"

void read_process_file(const char *filename, PROCESS_MANAGER *pm) {
    FILE *inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    char line[200];
    fgets(line, 200, inputFile); // Skip header

    while (fgets(line, 200, inputFile)) {
        int pid, priority, isHead;
        if (sscanf(line, "%d,%d,%d", &pid, &priority, &isHead) == 3) {
            PROCESS job;
            initialize_process(&job, pid, priority);

            PROCESS_QUEUE *targetQueue;
            if (priority == 1) {
                targetQueue = &pm->deque[pm->front];
            } else {
                targetQueue = &pm->deque[pm->rear];
            }

            enqueue(targetQueue, job);
            if (isHead) {
                PROCESS_QUEUE newQueue;
                initialize_process_queue(&newQueue);
                if (priority == 1) {
                    insert_front(pm, newQueue);
                } else {
                    insert_rear(pm, newQueue);
                }
            }
        }
    }

    fclose(inputFile);
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq) {
    FILE *inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    char line[200];
    fgets(line, 200, inputFile); // Skip header

    while (fgets(line, 200, inputFile)) {
        int iteration, pid, priority, isHead;
        if (sscanf(line, "%d,%d,%d,%d", &iteration, &pid, &priority, &isHead) == 4) {
            PROCESS job;
            initialize_process(&job, pid, priority);

            enqueue(&eq->queue[eq->rear], job);
            eq->queue[eq->rear].iteration = iteration;

            if (isHead) {
                PROCESS_QUEUE newQueue;
                initialize_process_queue(&newQueue);
                enqueue(eq, newQueue);
            }
        }
    }

    fclose(inputFile);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs) {
    FILE *outputFile = fopen("execution_run.txt", "w");
    if (!outputFile) {
        printf("Error: Could not create execution_run.txt\n");
        return;
    }

    int iteration = 0;
    PROCESS_QUEUE activeQueue;
    initialize_process_queue(&activeQueue);

    while (!isEmpty(pm) || !isEmpty(eq) || !isEmpty(&activeQueue)) {
        if (isEmpty(&activeQueue) && !isEmpty(pm)) {
            activeQueue = delete_front(pm);
        }

        if (!isEmpty(&activeQueue)) {
            PROCESS currentProcess = dequeue(&activeQueue);
            if (currentProcess.pid % 8 == 0) {
                fprintf(outputFile, "%d, f\n", currentProcess.pid);
                push(fs, activeQueue);
                initialize_process_queue(&activeQueue);
            } else {
                fprintf(outputFile, "%d, s\n", currentProcess.pid);
            }
        }

        if (!isEmpty(eq) && eq->queue[eq->front].iteration == iteration) {
            PROCESS_QUEUE arrivingQueue = dequeue(eq);
            if (arrivingQueue.priority == 1) {
                insert_front(pm, arrivingQueue);
            } else {
                insert_rear(pm, arrivingQueue);
            }
        }

        iteration++;
    }

    fclose(outputFile);
    printf("Execution completed and saved to execution_run.txt\n");
}