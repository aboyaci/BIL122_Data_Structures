#ifndef __23TREE_H__
#define __23TREE_H__

#define NODE2 0
#define NODE3 1

#define LEFT (-1)
#define RIGHT  1
#define MIDDLE 0

struct node
{
	int small_key;
	int big_key;
	struct node* left;
	struct node* middle;
	struct node* right;
	int type;
};

int LDR(struct node* n);
int DLR(struct node* n);
int LRD(struct node* n);
struct node* allocate_node();
int compare_key(struct node* n, int key);
struct node* find_proper_leaf(struct node* root, int data);
struct node* insert(struct node* root, int data);
struct node* propogate(struct node* n, struct node* root, struct node* new_node);
struct node* split(struct node* current_node, struct node* root, int data);
struct node* find_parent(struct node* root, int data);


#endif /* __23TREE_H__ */