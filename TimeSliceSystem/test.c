#include <assert.h>
#include <stdlib.h>

#include "stdio.h"
#include "time.h"

#include "time_slice_system.h"
#include "func_collection.h"
#include "ctrl_handler.h"

time_slice_system* s = NULL;

void prepare_test();
void test_tasks();
void test_funcs();

int main() {
    printf("Run Tests...\n");
    prepare_test();
    test_tasks();
    test_funcs();
    printf("All tests were successful. No Errors occurred.\n");
    return 0;
}

void prepare_test() {
    // Initialize the time slice system
    task_node* t_1 = create_task(1);
    task_node* t_5 = create_task(5);
    task_node* t_10 = create_task(10);
    task_node* t_100 = create_task(100);
    
    add_func_to_task(t_100, &f_d);
    add_func_to_task(t_100, &f_e);

    add_func_to_task(t_5, &f_a);
    add_func_to_task(t_5, &f_b);

    add_func_to_task(t_1, &f_a);
    add_func_to_task(t_1, &f_a);
    add_func_to_task(t_1, &f_b);
    add_func_to_task(t_1, &f_c);

    add_func_to_task(t_10, &f_a);
    add_func_to_task(t_10, &f_c);
    add_func_to_task(t_10, &f_e);
    
    // create time slice system and register tasks
    s = create_time_slice_system();
    register_task(s, t_5);
    register_task(s, t_100);
    register_task(s, t_1);
    register_task(s, t_10);

    // print time slice system as debug information
    print_time_slice_system(s);
}

void test_tasks() {
    printf("-------> TEST: %s\n", __FUNCTION__);

    // Assert that the global reference to the time slice system is not NULL
    assert(s != NULL);

    // Assert that the time slice system has 4 registered tasks
    assert(s->task_count == 4);

    // Assert that the tasks are sorted in ascending order by their cycle time
    assert(s->task_list->next->cycle_time == 1);
    assert(s->task_list->next->next->cycle_time == 5);
    assert(s->task_list->next->next->next->cycle_time == 10);
    assert(s->task_list->next->next->next->next->cycle_time == 100);

    // Assert that each task has the expected number of functions
    assert(s->task_list->next->func_count == 4);
    assert(s->task_list->next->next->func_count == 2);
    assert(s->task_list->next->next->next->func_count == 3);
    assert(s->task_list->next->next->next->next->func_count == 2);

    printf("Test was successful. No Errors occurred.\n");
}

void test_funcs() {
    printf("-------> TEST: %s\n", __FUNCTION__);

    // Assert that the functions are added to the tasks in the correct order
    func_node* func;

    func = s->task_list->next->func_list->next;
    assert(func->func == &f_a);
    func = func->next;
    assert(func->func == &f_a);
    func = func->next;
    assert(func->func == &f_b);
    func = func->next;
    assert(func->func == &f_c);

    func = s->task_list->next->next->func_list->next;
    assert(func->func == &f_a);
    func = func->next;
    assert(func->func == &f_b);

    func = s->task_list->next->next->next->func_list->next;
    assert(func->func == &f_a);
    func = func->next;
    assert(func->func == &f_c);
    func = func->next;
    assert(func->func == &f_e);

    func = s->task_list->next->next->next->next->func_list->next;
    assert(func->func == &f_d);
    func = func->next;
    assert(func->func == &f_e);

    printf("Test was successful. No Errors occurred.\n");
}