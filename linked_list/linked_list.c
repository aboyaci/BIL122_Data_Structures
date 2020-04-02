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

int deallocate_node(struct list_node* n)
{
	free(n);

	return 0;
}

/* print a list node */
int print_node(struct list_node* n)
{
	printf("\tdata: %d ", n->data);
	printf("\tnext: %p\n", n->next);

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
	Print the list but recursively
*/
int print_list_recursive(struct list_node* n)
{
	if (!n) return 0;

	print_node(n);
	print_list_recursive(n->next);

	return 1;
}

/*
	Print the list but in reverse order
*/
int print_list_reverse(struct list_node* n)
{
	if (!n) return 0;
	
	print_list_reverse(n->next);
	print_node(n);
	
	return 1;
}

struct list_node* reverse_list(struct list_node* head, struct list_node* next)
{

	if (!head) return head; // for safety
	
	if (head->next == NULL) // check if this is the last element
	{
		head->next = next;
		return head;
	}
	struct list_node* new_head = reverse_list(head->next, head);
	head->next = next;

	return new_head;
}

/*
	Find an element
*/
struct list_node* find_element(struct list_node* head, int what)
{
	struct list_node* current = head;

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
int delete_node(struct list_node* head, int what)
{
	struct list_node* current = head;
	struct list_node* to_be_deleted = NULL;

	while(current)
	{
		if (current->next != NULL
			&& current->next->data == what)
		{
			to_be_deleted = current->next;
			current->next = to_be_deleted->next;

			deallocate_node(to_be_deleted);

			return 1; /* deleted */
		}
		current = current->next;
	}

	return 0;
}

/*
	Update en element
*/
int update_node(struct list_node* head, int what, int to)
{
	struct list_node* n = find_element(head, what);

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

	printf("Here is the linked list reversed!:\n");
	struct list_node* l = reverse_list(head, NULL);
	print_list(l);

	return 0;
}