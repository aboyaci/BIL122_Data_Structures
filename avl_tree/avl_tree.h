#ifndef __AVLTREE_H__
#define __AVLTREE_H__

struct node
{
	int data;
	struct node* left;
	struct node* right;
};


int LDR(struct node* n);
int DLR(struct node* n);
int LRD(struct node* n);
struct node* allocate_node();
struct node* insert(struct node* root, int data);
struct node* balance(struct node* n);
struct node* rr_rotation(struct node* parent);
struct node* ll_rotation(struct node* parent);
struct node* lr_rotation(struct node* parent);
struct node* rl_rotation(struct node* parent);
int diff(struct node* n);
int height(struct node* n);

#endif /* __AVLTREE_H__ */