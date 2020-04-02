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
int deallocate_node(struct list_node* n);
int print_node(struct list_node* n);
int print_list(struct list_node* head);
int print_list_recursive(struct list_node* n);
int print_list_reverse(struct list_node* n);
struct list_node* reverse_list(struct list_node* head, struct list_node* next);
struct list_node* find_element(struct list_node* head, int what);
int delete_node(struct list_node* head, int what);
int update_node(struct list_node* head, int what, int to);


#endif /* __LINKED_LIST__ */