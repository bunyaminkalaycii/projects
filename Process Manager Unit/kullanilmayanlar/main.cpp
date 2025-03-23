#include <iostream>
#include "execution_functions.h"

using namespace std;

int main() {
    PROCESS_MANAGER pm;
    initialize_process_manager(&pm);

    INSERTION_QUEUE iq;
    initialize_execution_queue(&iq);

    FAILURE_STACK fs;
    initialize_failed_stack(&fs);

    printf("Reading initial_processes.txt...\n");
    read_process_file("initial_processes.txt", &pm);

    printf("Reading arriving_processes.txt...\n");
    read_insertion_file("arriving_processes.txt", &iq);

    printf("Starting execution loop...\n");
    execution_loop(&pm, &iq, &fs);

    printf("Execution loop completed. Results saved in execution_run.txt.\n");

    return 0;
}
