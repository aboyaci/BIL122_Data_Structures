#include <stdlib.h>
#include <stdio.h>

#include "double_linked_list.h"


/*
	Allocate a node
*/
struct double_list_node* allocate_node()
{
	struct double_list_node* n = malloc(sizeof(struct double_list_node));
	n->next = NULL;
	n->prev = NULL;

	return n;
}

int deallocate_node(struct double_list_node* n)
{
	free(n);

	return 0;
}

/* print a list node */
int print_node(struct double_list_node* n)
{
	printf("\tprev: %p", n->prev);
	printf("\tdata: %d ", n->data);
	printf("\tnext: %p\n", n->next);

	return 0;
}

/*
	Traverse and print the list
*/
int print_list(struct double_list_node* head)
{
	struct double_list_node* current = head;

	while(current)
	{
		print_node(current);
		current = current->next;
	}

	return 0;
}

/*
	Print the list but recursively
*/
int print_list_recursive(struct double_list_node* n)
{
	if (!n) return 0;

	print_node(n);
	print_list_recursive(n->next);

	return 1;
}

/*
	Print the list but in reverse order
*/
int print_list_reverse(struct double_list_node* head)
{
	struct double_list_node* current = head;

	// go to the end of the data
	while(current->next)
	{
		current = current->next;
	}

	// travere backwards
	while(current)
	{
		print_node(current);
		current = current->prev;
	}
		
	return 1;
}

/*
	Find an element
*/
struct double_list_node* find_element(struct double_list_node* head, int what)
{
	struct double_list_node* current = head;

	while(current)
	{
		if (current->data == what)
		{
			return current; /* Found */
		}
		current = current->next;
	}

	return NULL; /* Not found :( */
}

/*
	Delete en element
*/
int delete_node(struct double_list_node* head, int what)
{
	struct double_list_node* to_be_deleted = NULL;

	to_be_deleted = find_element(head, what);

	if(to_be_deleted)
	{
		struct double_list_node* pred = to_be_deleted->prev;
		struct double_list_node* succ = to_be_deleted->next;

		//n1 <-> n2 <-> n3 <-> n4

		/* HOME WORK! */
		/* complete th rest! */
	}


	return 0;
}

/*
	Update en element
*/
int update_node(struct double_list_node* head, int what, int to)
{
	struct double_list_node* n = find_element(head, what);

	if (n)
	{
		n->data = to;
		return 1;
	}

	return 0;
}

/*
	Main function
*/
int main()
{
	struct double_list_node* head = NULL;
	struct double_list_node* new_node = NULL;
	struct double_list_node* current_node = NULL;

	current_node = allocate_node();
	current_node->data = 1;

	head = current_node;

	for(int i=2; i<10; i++)
	{
		new_node = allocate_node();
		new_node->data = i;
		new_node->prev = current_node;
		current_node->next = new_node;
		current_node = new_node;
	}

	printf("Here is the linked list!:\n");
	print_list(head);

	if(find_element(head, 2))
	{
		printf("I have found 2 in this list!\n");
	}

	if(update_node(head, 1, 111))
	{
		printf("I have updated 1 to 111 in this list!\n");
	}

	if(delete_node(head, 2))
	{
		printf("I have deletes 2 in this list!\n");
	}

	printf("Here is the linked list after delete and update:\n");
	print_list(head);

	printf("Here is the linked list printed in reversed!:\n");
	print_list_reverse(head);

	return 0;
}