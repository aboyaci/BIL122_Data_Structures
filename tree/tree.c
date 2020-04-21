#include "stdio.h"
#include "tree.h"



/* in order traversal */
int LDR(struct node* n)
{
	if(n == NULL)
		return 0;

	LDR(n->left);
	printf("%d\n", n->data);
	LDR(n->right);

	return 1;
}

/* pre order traversal */
int DLR(struct node* n)
{
	if(n == NULL)
		return 0;

	printf("%d\n", n->data);
	DLR(n->left);
	DLR(n->right);

	return 1;
}

/* post order traversal */
int LRD(struct node* n)
{
	if(n == NULL)
		return 0;

	LRD(n->left);
	LRD(n->right);
	printf("%d\n", n->data);

	return 1;
}

struct node* allocate_node();
int insert(int data);


int main(int argc, char const *argv[])
{
	//struct node* root = allocate_node();
	//root->data = 1;

	/* code */
	return 0;
}