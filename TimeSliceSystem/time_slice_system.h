#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "task.h"

// typedef for ease of use
typedef struct time_slice_system time_slice_system;

struct time_slice_system 
{
	task_node* task_list;
};

// create time slice system
time_slice_system* create_time_slice_system() 
{
	// create new time slice system
	time_slice_system* system = (time_slice_system*)malloc(sizeof(time_slice_system));
	if (!system)
		return NULL;
	// create head for task list
	system->task_list = create_task(0);
	return system;
}

// register task into time slice system by a sorted insert
// specification: multiple tasks with same cyle time are not allowed!
void register_task(time_slice_system* system, task_node* task)
{
	// 1, 5, 10, 20, 100
	// 1, 5, 10, 20, 50<100
	// find last task that fulfills sorting condition
	task_node* t = system->task_list;
	while (t->next != NULL) {
		if (task->cycle_time < t->next->cycle_time) 
		{
			break;
		}
		else if (task->cycle_time == t->next->cycle_time) 
		{
			printf("Warning: Multiple tasks with same cycle time. Registration aborted!\n");
			return;
		}
		t = t->next;
	}

	// add new task after found task
	task->next = t->next;
	t->next = task;
}

// print registered tasks of time slice system
void print_time_slice_system(time_slice_system* system) 
{
	// traverse over all tasks and print them
	task_node* t;
	for (t = system->task_list->next; t != NULL; t = t->next)
	{
		print_task(t);
	}
}