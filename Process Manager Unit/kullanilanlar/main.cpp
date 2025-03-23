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

int main()
{
    PROCESS_MANAGER pm;
    INSERTION_QUEUE iq;
    FAILURE_STACK fs;

    initialize_process_manager(&pm);
    initialize_execution_queue(&iq);
    initialize_failed_stack(&fs);

    read_process_file("../initial_processes.txt", &pm);
    read_insertion_file("../arriving_processes.txt", &iq);

    execution_loop(&pm, &iq, &fs);

    return 0;
}