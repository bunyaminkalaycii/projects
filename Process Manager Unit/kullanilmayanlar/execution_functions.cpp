#include "execution_functions.h"
#include <iostream>
using namespace std;

// Initial process file'dan Process Manager'ı doldurur
#include "execution_functions.h"
#include <stdio.h> // C standardı için

void read_process_file(const char *filename, PROCESS_MANAGER *pm) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int lineNumber = 0;

    PROCESS_QUEUE currentQueue;
    initialize_process_queue(&currentQueue);

    while (fgets(line, sizeof(line), file)) {
        if (lineNumber == 0) {
            // İlk satır önemsiz, atla
            lineNumber++;
            continue;
        }

        int pid, priority, isHead;
        sscanf(line, "%d, %d, %d", &pid, &priority, &isHead);

        PROCESS newProcess;
        initialize_process(&newProcess, pid, priority);

        if (isHead == 1) {
            // Yeni parent process, mevcut queue'yu ekle ve yeni bir queue başlat
            if (currentQueue.size > 0) {
                currentQueue.priority = priority;
                if (priority == 1) {
                    insert_front(pm, currentQueue); // High-priority
                    //cout<<"process_manager'da fronta pushlandı"<<endl;
                    
                } else {
                    insert_rear(pm, currentQueue); // Low-priority
                    //cout<<"process_manager'da rear'a pushlandı"<<endl;
                }
            }
            initialize_process_queue(&currentQueue); // Yeni queue'yu başlat
        }

        // Process'i mevcut queue'ya ekle
        enqueue(&currentQueue, newProcess);

        lineNumber++;
    }

    // Son queue'yu ekle
    if (currentQueue.size > 0) {
        PROCESS_QUEUE pq = currentQueue;
        if (pq.priority == 1) {
            insert_front(pm, pq);
        } else {
            insert_rear(pm, pq);
        }
    }

    fclose(file);
}


// Insertion file'dan Insertion Queue'yu doldurur
void read_insertion_file(const char *filename, INSERTION_QUEUE *iq) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int lineNumber = 0;
    PROCESS_QUEUE newQueue;
    while (fgets(line, sizeof(line), file)) {
        if (lineNumber == 0) {
            // İlk satır önemsiz, atla
            lineNumber++;
            continue;
        }

        int iteration, pid, priority, isHead;
        sscanf(line, "%d, %d, %d, %d", &iteration, &pid, &priority, &isHead);

        PROCESS newProcess;
        initialize_process(&newProcess, pid, priority);
        if (isHead == 1) {
            // Yeni parent process, mevcut queue'yu ekle ve yeni bir queue başlat
            if (newQueue.size > 0) {
                newQueue.priority = priority;
                newQueue.iteration = iteration;
                if (priority == 1) {
                    enqueue(&newQueue, newProcess);
                    enqueue(iq, newQueue);
                    //cout<<"process_manager'da fronta pushlandı"<<endl;
                    
                } else {
                    enqueue(&newQueue, newProcess);
                    // Low-priority
                    //cout<<"process_manager'da rear'a pushlandı"<<endl;
                }
            }
            initialize_process_queue(&newQueue); // Yeni queue'yu başlat
        }
        
        newQueue.priority = priority;
        

        

        

        // Yeni queue'yu ekle
        enqueue(iq, newQueue);

        lineNumber++;
    }

    fclose(file);
}

// Process Manager'dan process'leri sırayla çalıştırır
void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs) {
    int iteration = 0;

    FILE *ptr = fopen("execution_run.txt", "w");
    if (ptr == NULL) {
        printf("Error: Could not open execution_run.txt\n");
        return;
    }

    while (!isEmpty(pm) || !isEmpty(eq)) {
        // Process Manager'daki yüksek öncelikli queue'yu al
        if (!isEmpty(pm)) {
            PROCESS_QUEUE current_queue = delete_front(pm);
            bool failure_occurred = false;

            for (int i = 0; i < current_queue.size; i++) {
                int idx = (current_queue.front + i) % QUEUE_SIZE;
                PROCESS p = current_queue.queue[idx];

                // Başarı/Başarısızlık kontrolü
                if (p.pid % 8 == 0) {
                    fprintf(ptr, "%d, f\n", p.pid);
                    failure_occurred = true;
                } else if (!failure_occurred) {
                    fprintf(ptr, "%d, s\n", p.pid);
                }

                // Başarısızlık durumunda kalan process'leri Failure Stack'e aktar
                if (failure_occurred) {
                    PROCESS_QUEUE failed_queue;
                    initialize_process_queue(&failed_queue);

                    for (int j = i; j < current_queue.size; j++) {
                        int failed_idx = (current_queue.front + j) % QUEUE_SIZE;
                        enqueue(&failed_queue, current_queue.queue[failed_idx]);
                    }
                    push(fs, failed_queue);
                    break;
                }
            }
        }

        // Insertion Queue'dan Process Manager'a aktarım
        while (!isEmpty(eq)) {
            PROCESS_QUEUE incoming_queue = peek(eq);

            if (incoming_queue.iteration == iteration) {
                dequeue(eq); // Gelen queue'yu çıkar
                if (incoming_queue.priority == 1) {
                    insert_front(pm, incoming_queue); // High-priority
                } else {
                    insert_rear(pm, incoming_queue); // Low-priority
                }
            } else {
                break; // Iteration eşleşmiyorsa işlemi durdur
            }
        }

        iteration++;
    }

    fclose(ptr);
    printf("Execution complete. Results written to execution_run.txt\n");
}
