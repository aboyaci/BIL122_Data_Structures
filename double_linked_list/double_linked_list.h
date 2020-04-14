#ifndef __LINKED_LIST__
#define __LINKED_LIST__

struct double_list_node
{
	struct double_list_node* prev;
	int data;
	struct double_list_node* next;
};

struct double_list_node* allocate_node();
int deallocate_node(struct double_list_node* n);
int print_node(struct double_list_node* n);
int print_list(struct double_list_node* head);
int print_list_recursive(struct double_list_node* n);
int print_list_reverse(struct double_list_node* n);
struct double_list_node* reverse_list(struct double_list_node* head, struct double_list_node* next);
struct double_list_node* find_element(struct double_list_node* head, int what);
int delete_node(struct double_list_node* head, int what);
int update_node(struct double_list_node* head, int what, int to);


#endif /* __LINKED_LIST__ */