#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "func.h"

// typedef for ease of use
typedef struct task_node task_node;

struct task_node
{
	size_t cycle_time;
	clock_t last_time;
	func_node* func_list;
	task_node* next;
};

// create task with cycle time
task_node* create_task(size_t cycle_time)
{
	// create new task node
	task_node* task = malloc(sizeof(task_node));
	if (!task)
		return NULL;
	// pass cycle time
	task->cycle_time = cycle_time;
	// set last time to zero
	task->last_time = 0;
	// create head of func
	task->func_list = create_func();
	task->next = NULL;
	return task;
}

// add a new function pointer to the task
void add_func_to_task(task_node* task, func_ptr func)
{
	func_node* node = append_func(task->func_list, func);
}

// print task and the list of its function pointers
void print_task(task_node* task)
{
	printf("%zds task: ", task->cycle_time);
	func_node* pivot = task->func_list->next;
	int i = 1;
	while (pivot != NULL)
	{
		// print rank in the list and pointer address of the function
		printf("%d->%d ", i, pivot->func);
		pivot = pivot->next;
		i++;
	}
	printf("\n");
}
