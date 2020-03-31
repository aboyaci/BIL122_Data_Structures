#ifndef __LINKED_LIST__
#define __LINKED_LIST__

struct list_node
{
	int data;
	int data2;
	int data3;
	struct list_node* next;
};

struct list_node* allocate_node();
int print_node(struct list_node* n);
int print_list(struct list_node* head);
int find_element(struct list_node* head, int what);


#endif /* __LINKED_LIST__ */