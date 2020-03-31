#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"


/*
	Allocate a node
*/
struct list_node* allocate_node()
{
	struct list_node* n = malloc(sizeof(struct list_node));
	n->next = NULL;

	return n;
}

/* print a list node */
int print_node(struct list_node* n)
{
	printf("data: %d ", n->data);
	printf("next: %p\n", n->next);

	return 0;
}

/*
	Traverse and print the list
*/
int print_list(struct list_node* head)
{
	struct list_node* current = head;

	while(current)
	{
		print_node(current);
		current = current->next;
	}

	return 0;
}

/*
	Find an element
*/
int find_element(struct list_node* head, int what)
{
	struct list_node* current = head;

	while(current)
	{
		if (current->data == what)
		{
			return 1; /* Found */
		}
		current = current->next;
	}

	return 0; /* Not found :( */
}

int main()
{
	struct list_node* head = NULL;
	struct list_node* new_node = NULL;
	struct list_node* current_node = NULL;

	current_node = allocate_node();
	current_node->data = 1;

	head = current_node;

	for(int i=2; i<10; i++)
	{
		new_node = allocate_node();
		new_node->data = i;
		current_node->next = new_node;
		current_node = new_node;
	}

	print_list(head);

	if(find_element(head, 2))
	{
		printf("I have found 2 in this list!\n");
	}

	return 0;
}