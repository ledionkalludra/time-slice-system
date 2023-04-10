#include "stdio.h"
#include "time.h"

#include "time_slice_system.h"
#include "func_collection.h"
#include "ctrl_handler.h"

// global reference to time slice system
time_slice_system* s = NULL;

// declarations
void header();
void init();
void run();
void step(time_t);
void footer();

// start of the program
int main()
{
    header();
    init();
    run();
    footer();

    return 0;
}

// print project meta information
void header() 
{
    printf("-----------------\n");
    printf("Time Slice System\n");
    printf("Ledion Kalludra  \n");
    printf("-----------------\n");
}

// init project by configuring tasks and functions
void init()
{
    printf("#1: Init\n");

    // register signal handler
    set_ctrl_handler();

    // create tasks with their appropriate cycle times
    task_node* t_1 = create_task(1);
    task_node* t_5 = create_task(5);
    task_node* t_10 = create_task(10);
    task_node* t_100 = create_task(100);
    
    // add functions to the tasks
    // specification: 
    // - it is allowed to have the same function added multiple times to a task
    // - a function has to be of type func_ptr which is void and no parameters
    // - in the same order the functions were added, they will also be executed
    // - order of adding tasks is independend because tasks will be executed sorted (ascending) by cycle time
    add_func_to_task(t_1, &f_a);
    add_func_to_task(t_1, &f_a);
    add_func_to_task(t_1, &f_b);
    add_func_to_task(t_1, &f_c);

    add_func_to_task(t_5, &f_a);
    add_func_to_task(t_5, &f_b);

    add_func_to_task(t_10, &f_a);
    add_func_to_task(t_10, &f_c);
    add_func_to_task(t_10, &f_e);

    add_func_to_task(t_100, &f_d);
    add_func_to_task(t_100, &f_e);
    
    // create time slice system and register tasks
    s = create_time_slice_system();
    // hint: tasks are automatically inserted sorted by cycle time
    register_task(s, t_5);
    register_task(s, t_100);
    register_task(s, t_1);
    register_task(s, t_10);

    // print time slice system as debug information
    print_time_slice_system(s);
}

// run loop and trigger a step every 1s
void run()
{
    time_t start_time, end_time;
    time_t elapsed_time;
    time_t last_time = 0;

    printf("#2: Run\n");
    time(&start_time);
    
    while (g_running)
    {
        // calculate elapsed time as delta of current time and start time
        time(&end_time);
        elapsed_time = end_time - start_time;

        // a second has passed if elapsed time has changed
        // if step function takes longer than 1s, step will be triggered with delay
        if (elapsed_time != last_time) 
        {
            // save timestamp of current step
            last_time = elapsed_time;

            // perform step
            step(elapsed_time);
        }
    }
}

// every whole second a step will be executed
void step(time_t t) 
{
    task_node* task;
    func_node* func;
    
    printf("Step %zus:\n", t);

    // traverse over all tasks
    for (task = s->task_list->next; task != NULL; task = task->next)
    {
        // task will only be triggered every cycle_time s
        if (t % task->cycle_time == 0) 
        {
            // traverse over all functions
            for (func = task->func_list->next; func != NULL; func = func->next) 
            {
                // call function
                if (func->func != NULL)
                    func->func();
                else 
                    printf("Warning: Function is NULL (Task: %zus).", task->cycle_time);
            }
        }
    }
}

void footer() 
{
    printf("-----------------\n");
    printf("Program shutdown \n");
    printf("-----------------\n");
}
