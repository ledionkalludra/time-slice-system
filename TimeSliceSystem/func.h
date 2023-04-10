#pragma once

#include "stdio.h"
#include "stdlib.h"

// typedef for ease of use
typedef struct func_node func_node;

// function pointer
// specification: only functions without return value and parameters are allowed
typedef void (*func_ptr)();

struct func_node
{
	func_ptr func;
	func_node* next;
};

// create func list
func_node* create_func()
{
	// create func node as head of the list
	func_node* head = (func_node*)malloc(sizeof(func_node));
	if (head == NULL)
		return NULL;
	head->func = NULL;
	head->next = NULL;
	return head;
}

// insert func at the end
func_node* append_func(func_node* head, func_ptr func)
{
	// stop if head is already NULL
	if (head == NULL)
		return NULL;

	// create new func node
	func_node* node = (func_node*)malloc(sizeof(func_node));
	if (node == NULL)
		return NULL;
	node->func = func;

	// find last node
	func_node* pivot = head;
	while (pivot->next != NULL) {
		pivot = pivot->next;
	}
	
	// add after last node
	node->next = pivot->next;
	pivot->next = node;
	return node;
}
